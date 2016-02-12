/*
# Created by Fabrizio Di Vittorio (fdivitto2013@gmail.com)
# Copyright (c) 2015/2016 Fabrizio Di Vittorio.
# All rights reserved.

# GNU GPL LICENSE
#
# This module is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; latest version thereof,
# available at: <http://www.gnu.org/licenses/gpl.txt>.
#
# This module is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this module; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*/

#include "fdv.h"

namespace fdv {


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// SerialBinary

#if (FDV_INCLUDE_SERIALBINARY == 1)

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// SerialBinary::Message

MTD_FLASHMEM SerialBinary::Message::Message() : valid(false), ID(0), command(0), dataSize(0), data(NULL) {  
}

MTD_FLASHMEM SerialBinary::Message::Message(uint8_t ID_, uint8_t command_, uint16_t dataSize_)
    : valid(true), ID(ID_), command(command_), dataSize(dataSize_), data(dataSize_ ? new uint8_t[dataSize_] : NULL) {      
}

MTD_FLASHMEM SerialBinary::Message::Message(uint8_t ID_, uint8_t command_, uint8_t *data_, uint16_t dataSize_)
    : valid(true), ID(ID_), command(command_), data(data_), dataSize(dataSize_) {
}

void MTD_FLASHMEM SerialBinary::Message::freeData() {
  if (data != NULL) {
    delete[] data;
    data = NULL;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

MTD_FLASHMEM SerialBinary::SerialBinary()
    : m_serial(HardwareSerial::getSerial(0)), m_recvID(255), m_sendID(0), m_recvACKQueue(ACKMSG_QUEUE_LENGTH),
      m_receiveTask(this, false, 256), m_isReady(false), m_platform(PLATFORM_BASELINE), m_HTTPRoutes(NULL) {
  checkReady();
}

MTD_FLASHMEM SerialBinary::~SerialBinary() {
  m_receiveTask.terminate();
  delete m_HTTPRoutes;
  // todo: free pending messages
}

bool MTD_FLASHMEM SerialBinary::isReady() {
  MutexLock lock(&m_mutex);
  return m_isReady;
}

bool MTD_FLASHMEM SerialBinary::checkReady() {
  if (!isReady())
    send_CMD_READY();
  return isReady();
}

uint8_t MTD_FLASHMEM SerialBinary::getPlatform() {
  checkReady();
  MutexLock lock(&m_mutex);
  return m_platform;
}

StringList *MTD_FLASHMEM SerialBinary::getHTTPRoutes() {
  MutexLock lock(&m_himutex);
  if (m_HTTPRoutes == NULL) // already requested?
  {
    // request handled pages
    m_HTTPRoutes = new StringList;
    if (!send_CMD_GETHTTPHANDLEDPAGES()) {
      // get a chance to retry
      delete m_HTTPRoutes;
      m_HTTPRoutes = NULL;
    }
  }
  return m_HTTPRoutes;
}

SerialBinary::Message MTD_FLASHMEM SerialBinary::receive() {
  Message msg;
  SoftTimeOut timeout(WAIT_MSG_TIMEOUT);
  while (!timeout) {
    // ID
    int16_t r = m_serial->read(INTRA_MSG_TIMEOUT);
    if (r < 0)
      continue;
    msg.ID = r;

    // Command
    r = m_serial->read(INTRA_MSG_TIMEOUT);
    if (r < 0)
      continue;
    msg.command = r;

    // Data Size Low
    r = m_serial->read(INTRA_MSG_TIMEOUT);
    if (r < 0)
      continue;
    msg.dataSize = r;

    // Data Size High
    r = m_serial->read(INTRA_MSG_TIMEOUT);
    if (r < 0)
      continue;
    msg.dataSize |= r << 8;

    // Data
    if (msg.dataSize > 0 && msg.dataSize < (Task::getFreeHeap() >> 1)) {
      msg.data = new uint8_t[msg.dataSize];
      if (m_serial->read(msg.data, msg.dataSize, INTRA_MSG_TIMEOUT) < msg.dataSize) {
        msg.freeData();
        continue;
      }
    }

    // check ID
    if (msg.ID == m_recvID) {
      msg.freeData();
      continue;
    }
    m_recvID = msg.ID;

    msg.valid = true;
    return msg;
  }
  return msg;
}

uint8_t MTD_FLASHMEM SerialBinary::getNextID() {
  MutexLock lock(&m_mutex);
  return ++m_sendID;
}

void MTD_FLASHMEM SerialBinary::send(Message const &msg) {
  MutexLock lock(&m_mutex);
  m_serial->write(msg.ID);
  m_serial->write(msg.command);
  m_serial->write(msg.dataSize & 0xFF);
  m_serial->write((msg.dataSize >> 8) & 0xFF);
  if (msg.dataSize > 0)
    m_serial->write(msg.data, msg.dataSize);
}

// send ACK without parameters
void MTD_FLASHMEM SerialBinary::sendNoParamsACK(uint8_t ackID) {
  uint8_t data[1] = {ackID};
  send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
}

SerialBinary::Message MTD_FLASHMEM SerialBinary::waitACK(uint8_t ackID) {
  Message msg;
  SoftTimeOut timeout(GETACK_TIMEOUT);
  while (!timeout) {
    if (m_recvACKQueue.receive(&msg, GETACK_TIMEOUT)) {
      uint8_t msgAckID = msg.data[0];
      if (msgAckID == ackID)
        return msg;
      msg.freeData(); // discard this ACK
    }
  }
  msg.valid = false;
  return msg;
}

bool MTD_FLASHMEM SerialBinary::waitNoParamsACK(uint8_t ackID) {
  Message msg = waitACK(ackID);
  if (msg.valid) {
    msg.freeData();
    return true;
  }
  return false;
}

void MTD_FLASHMEM SerialBinary::receiveTask() {
  while (true) {
    Message msg = receive();
    if (msg.valid) {
      if (msg.command == CMD_ACK)
        // if message is an ACK then put it into the ACK message queue, another task will handle it
        m_recvACKQueue.send(msg, PUTACK_TIMEOUT);
      else
        processMessage(&msg);
    }
  }
}

// must not process CMD_ACK messages
void MTD_FLASHMEM SerialBinary::processMessage(SerialBinary::Message *msg) {
  switch (msg->command) {
  case CMD_READY:
    handle_CMD_READY(msg);
    break;
  case CMD_IOCONF:
    handle_CMD_IOCONF(msg);
    break;
  case CMD_IOSET:
    handle_CMD_IOSET(msg);
    break;
  case CMD_IOGET:
    handle_CMD_IOGET(msg);
    break;
  case CMD_IOASET:
    handle_CMD_IOASET(msg);
    break;
  case CMD_STREAMSTART:
    handle_CMD_STREAMSTART(msg);
    break;
  }
  msg->freeData();
}

void MTD_FLASHMEM SerialBinary::handle_CMD_READY(Message *msg) {
  // process message
  m_mutex.lock();
  uint8_t protocolVersion = msg->data[0];
  m_platform = msg->data[1];
  char const *magicString = (char const *)msg->data + 2;
  m_isReady = (protocolVersion == PROTOCOL_VERSION && f_strcmp(magicString, STR_BINPRORDY) == 0);
  m_mutex.unlock();

  // send ACK with parameters
  uint8_t data[13] = {msg->ID, PROTOCOL_VERSION, PLATFORM_THIS};
  f_strcpy((char *)data + 3, STR_BINPRORDY);
  send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
}

void MTD_FLASHMEM SerialBinary::handle_CMD_STREAMSTART(Message *msg) {
  // send simple ACK
  sendNoParamsACK(msg->ID);
  // this is the main action of this message: suspend receive task.
  // The receive task (actually THIS task) must be activate manually when
  // all the stream has been received.
  m_receiveTask.suspend();
}

void MTD_FLASHMEM SerialBinary::handle_CMD_IOCONF(Message *msg) {
  // process message
  uint8_t pin = msg->data[0];
  uint8_t flags = msg->data[1];
  if (flags & PIN_CONF_OUTPUT)
    GPIOX(pin).modeOutput();
  else
    GPIOX(pin).modeInput();
  GPIOX(pin).enablePullUp(flags & PIN_CONF_PULLUP);

  // send simple ACK
  sendNoParamsACK(msg->ID);
}

void MTD_FLASHMEM SerialBinary::handle_CMD_IOSET(Message *msg) {
  // process message
  uint8_t pin = msg->data[0];
  uint8_t state = msg->data[1];
  GPIOX(pin).write(state);

  // send simple ACK
  sendNoParamsACK(msg->ID);
}

void MTD_FLASHMEM SerialBinary::handle_CMD_IOGET(Message *msg) {
  // process message
  uint8_t pin = msg->data[0];
  bool state = GPIOX(pin).read();

  // send ACK with parameters
  uint8_t data[2] = {msg->ID, state};
  send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
}

// not implemented
void MTD_FLASHMEM SerialBinary::handle_CMD_IOASET(Message *msg) {
  // process message
  // not implemented

  // send simple ACK
  sendNoParamsACK(msg->ID);
}

bool MTD_FLASHMEM SerialBinary::send_CMD_READY() {
  m_isReady = false;
  for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i) {
    // send message
    uint8_t data[12] = {PROTOCOL_VERSION, PLATFORM_THIS};
    f_strcpy((char *)data + 2, STR_BINPRORDY);
    uint8_t msgID = getNextID();
    send(Message(msgID, CMD_READY, data, sizeof(data)));

    // wait for ACK
    Message msg = waitACK(msgID);
    if (msg.valid) {
      MutexLock lock(&m_mutex);
      uint8_t protocolVersion = msg.data[1];
      m_platform = msg.data[2];
      char const *magicString = (char const *)msg.data + 3;
      m_isReady = (protocolVersion == PROTOCOL_VERSION && f_strcmp(magicString, STR_BINPRORDY) == 0);
      msg.freeData();
      return true;
    }
  }
  return false;
}

bool MTD_FLASHMEM SerialBinary::send_CMD_IOCONF(uint8_t pin, uint8_t flags) {
  if (checkReady()) {
    for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i) {
      // send message
      uint8_t data[2] = {pin, flags};
      uint8_t msgID = getNextID();
      send(Message(msgID, CMD_IOCONF, data, sizeof(data)));

      // wait for ACK
      if (waitNoParamsACK(msgID))
        return true;
    }
    m_isReady = false; // no more ready
  }
  return false;
}

bool MTD_FLASHMEM SerialBinary::send_CMD_IOSET(uint8_t pin, uint8_t state) {
  if (checkReady()) {
    for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i) {
      // send message
      uint8_t data[2] = {pin, state};
      uint8_t msgID = getNextID();
      send(Message(msgID, CMD_IOSET, data, sizeof(data)));

      // wait for ACK
      if (waitNoParamsACK(msgID))
        return true;
    }
    m_isReady = false; // no more ready
  }
  return false;
}

bool MTD_FLASHMEM SerialBinary::send_CMD_IOGET(uint8_t pin, uint8_t *state) {
  if (checkReady()) {
    for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i) {
      // send message
      uint8_t data[1] = {pin};
      uint8_t msgID = getNextID();
      send(Message(msgID, CMD_IOGET, data, sizeof(data)));

      // wait for ACK
      Message msg = waitACK(msgID);
      if (msg.valid) {
        *state = msg.data[1];
        msg.freeData();
        return true;
      }
    }
    m_isReady = false; // no more ready
  }
  return false;
}

bool MTD_FLASHMEM SerialBinary::send_CMD_IOASET(uint8_t pin, uint16_t state) {
  if (checkReady()) {
    for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i) {
      // send message
      uint8_t data[3] = {pin, state & 0xFF, state >> 8};
      uint8_t msgID = getNextID();
      send(Message(msgID, CMD_IOASET, data, sizeof(data)));

      // wait for ACK
      if (waitNoParamsACK(msgID))
        return true;
    }
    m_isReady = false; // no more ready
  }
  return false;
}

bool MTD_FLASHMEM SerialBinary::send_CMD_IOAGET(uint8_t pin, uint16_t *state) {
  if (checkReady()) {
    for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i) {
      // send message
      uint8_t data[1] = {pin};
      uint8_t msgID = getNextID();
      send(Message(msgID, CMD_IOAGET, data, sizeof(data)));

      // wait for ACK
      Message msg = waitACK(msgID);
      if (msg.valid) {
        *state = msg.data[1] + (msg.data[2] << 8);
        msg.freeData();
        return true;
      }
    }
    m_isReady = false; // no more ready
  }
  return false;
}

bool MTD_FLASHMEM SerialBinary::send_CMD_GETHTTPHANDLEDPAGES() {
  m_HTTPRoutes->clear();
  if (checkReady()) {
    for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i) {
      // send message
      uint8_t msgID = getNextID();
      send(Message(msgID, CMD_GETHTTPHANDLEDPAGES, NULL, 0));

      // wait for ACK
      Message msg = waitACK(msgID);
      if (msg.valid) {
        uint8_t const *rpos = msg.data + 1;
        uint8_t itemsCount = *rpos++;
        for (uint8_t j = 0; j != itemsCount; ++j) {
          m_HTTPRoutes->add((char const *)rpos, StringList::Heap);
          rpos += strlen((char const *)rpos) + 1;
        }
        msg.freeData();
        return true;
      }
    }
    m_isReady = false; // no more ready
  }
  return false;
}

// wpos can be NULL (to just calculate total length)
// return copied bytes
uint32_t FUNC_FLASHMEM copyFields(HTTPHandler::Fields &fields, uint8_t **wpos) {
  uint32_t len = 0;
  for (uint32_t i = 0; i != fields.getItemsCount(); ++i) {
    uint32_t keylen = t_strlen(fields[i]->key) + 1;
    uint32_t vallen = t_strlen(fields[i]->value) + 1;
    len += keylen + vallen;
    if (wpos) {
      t_strcpy((char *)*wpos, fields[i]->key);
      *wpos += keylen;
      t_strcpy((char *)*wpos, fields[i]->value);
      *wpos += vallen;
    }
  }
  return len;
}

bool MTD_FLASHMEM SerialBinary::send_CMD_HTTPREQUEST(uint8_t pageIndex, HTTPHandler *handler) {
  MutexLock lock(&m_himutex);
  if (checkReady()) {
    for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i) {
      uint8_t msgID = getNextID();

      // calculate message payload length
      uint32_t msglen =
          5; // (1) method, (1) page index, (1) headers fields count, (1) query fields count, (1) form fields count
      msglen += t_strlen(handler->getRequest().requestedPage) + 1; // page len
      msglen += copyFields(handler->getRequest().headers, NULL);   // headers len
      msglen += copyFields(handler->getRequest().query, NULL);     // query len
      msglen += copyFields(handler->getRequest().form, NULL);      // form len

      //// prepare message
      Message msg(msgID, CMD_HTTPREQUEST, msglen);
      uint8_t *wpos = msg.data;

      // method
      *wpos++ = (uint8_t)handler->getRequest().method;

      // page index
      *wpos++ = pageIndex;

      // page (zero terminated string)
      t_strcpy((char *)wpos, handler->getRequest().requestedPage);
      wpos += t_strlen(handler->getRequest().requestedPage) + 1;

      // header fields
      *wpos++ = handler->getRequest().headers.getItemsCount();
      copyFields(handler->getRequest().headers, &wpos);

      // query fields
      *wpos++ = handler->getRequest().query.getItemsCount();
      copyFields(handler->getRequest().query, &wpos);

      // form fields
      *wpos++ = handler->getRequest().form.getItemsCount();
      copyFields(handler->getRequest().form, &wpos);

      // send message
      send(msg);
      msg.freeData();

      // wait for ACK
      msg = waitACK(msgID);
      if (msg.valid) {
        uint8_t const *rpos = msg.data + 1;

        // read status and initialize response object
        uint8_t status = *rpos++;
        char const *statusStr = STR_200_OK;
        switch (status) {
        case HTTPSTATUS_301:
          statusStr = STR_301_Moved_Permanently;
          break;
        case HTTPSTATUS_302:
          statusStr = STR_302_Found;
          break;
        case HTTPSTATUS_400:
          statusStr = STR_400_Bad_Request;
          break;
        case HTTPSTATUS_401:
          statusStr = STR_401_Unauthorized;
          break;
        case HTTPSTATUS_403:
          statusStr = STR_403_Forbidden;
          break;
        case HTTPSTATUS_404:
          statusStr = STR_404_Not_Found;
          break;
        }
        HTTPResponse response(handler, statusStr);

        // read and add additional headers
        uint8_t headersCount = *rpos++;
        for (uint8_t i = 0; i != headersCount; ++i) {
          char const *headerKey = (char const *)rpos;
          rpos += t_strlen(headerKey) + 1;
          char const *headerValue = (char const *)rpos;
          rpos += t_strlen(headerValue) + 1;
          response.addHeader(headerKey, headerValue);
        }

        // content-type header (if not unspecified)
        uint8_t contentType = *rpos++;
        switch (contentType) {
        case HTTPCONTENTTYPE_TEXTHTML:
          response.addHeader(STR_Content_Type, STR_TEXTHTML);
          break;
        case HTTPCONTENTTYPE_TEXTHTML_UTF8:
          response.addHeader(STR_Content_Type, STR_TEXTHTML_UTF8);
          break;
        case HTTPCONTENTTYPE_APPJSON:
          response.addHeader(STR_Content_Type, STR_APPJSON);
          break;
        case HTTPCONTENTTYPE_TEXTPLAIN:
          response.addHeader(STR_Content_Type, STR_TEXTPLAIN);
          break;
        case HTTPCONTENTTYPE_TEXTXML:
          response.addHeader(STR_Content_Type, STR_TEXTXML);
          break;
        }

        uint8_t contentMode = *rpos++;

        switch (contentMode) {
        case 0: {
          ///// Content embedded in the ACK message

          // Content length and content data
          uint16_t contentLen = *rpos + (*(rpos + 1) << 8);
          rpos += 2;
          response.addContent(rpos, contentLen);

          // flush headers and content
          response.flush();
          break;
        }

        case 1: {
          ///// Content not embedded in the ACK, known size

          // flush headers only
          uint16_t contentLen = *rpos + (*(rpos + 1) << 8);
          response.flushHeaders(contentLen);

          // wait for CMD_STREAMSTART
          SoftTimeOut timeout(WAIT_MSG_TIMEOUT);
          while (!timeout && !m_receiveTask.suspended())
            Task::delay(5);
          if (m_receiveTask.suspended()) {
            // receiver task correctly suspended, now process content stream
            MutexLock lock(&m_mutex);

            // get content from serial and put into the socket
            // todo: transfer using blocks instead of byte by byte
            for (uint16_t i = 0; i != contentLen; ++i) {
              int16_t r = m_serial->read(INTRA_MSG_TIMEOUT);
              if (r < 0)
                break;
              uint8_t b = r;
              handler->getSocket()->write(&b, 1);
            }
            m_receiveTask.resume();
          }
          break;
        }

        case 2: {
          ///// Content not embedded in the ACK, unknown size
          // wait for CMD_STREAMSTART
          SoftTimeOut timeout(WAIT_MSG_TIMEOUT);
          while (!timeout && !m_receiveTask.suspended())
            Task::delay(5);
          if (m_receiveTask.suspended()) {
            // receiver task correctly suspended, now process content stream
            MutexLock lock(&m_mutex);

            LinkedCharChunks chunks;
            while (true) {
              int16_t r = m_serial->read(INTRA_MSG_TIMEOUT);
              if (r <= 0) // -1 or 0x00 interrupt
                break;
              chunks.append((char)r, 32); // todo: increase?
            }
            m_receiveTask.resume();
            response.addContent(&chunks);
            response.flush();
          }
          break;
        }
        }

        msg.freeData();
        return true;
      }
    }
    m_isReady = false; // no more ready
  }
  return false;
}

#endif

} // end of "fdv" namespace
