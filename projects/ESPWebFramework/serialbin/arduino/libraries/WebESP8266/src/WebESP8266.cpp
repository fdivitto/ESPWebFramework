/*
WebESP8266.cpp
Binary Bidirectional Protocol for ESP8266

Created by Fabrizio Di Vittorio (fdivitto2013@gmail.com)
Copyright (c) 2015 Fabrizio Di Vittorio.
All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at
https://github.com/fdivitto/ESPWebFramework
*/

// 
// Includes
// 
#include <Arduino.h>
#include "WebESP8266.h"

#include <avr/pgmspace.h>


// Protocol version
static uint8_t const  PROTOCOL_VERSION     = 1;

// Timings, etc...
static uint32_t const INTRA_MSG_TIMEOUT    = 200;
static uint32_t const WAIT_MSG_TIMEOUT     = 2000;
static uint32_t const PUTACK_TIMEOUT       = 200;
static uint32_t const GETACK_TIMEOUT       = 2000;
static uint32_t const ACKMSG_QUEUE_LENGTH  = 2;
static uint32_t const MAX_RESEND_COUNT     = 3;	
static uint32_t const MAX_DATA_SIZE        = 512;

// Commands
static uint8_t const CMD_ACK                 = 0;
static uint8_t const CMD_READY               = 1;
static uint8_t const CMD_IOCONF              = 2;
static uint8_t const CMD_IOSET               = 3;
static uint8_t const CMD_IOGET               = 4;
static uint8_t const CMD_IOASET              = 5;
static uint8_t const CMD_IOAGET              = 6;
static uint8_t const CMD_GETHTTPHANDLEDPAGES = 7;
static uint8_t const CMD_HTTPREQUEST         = 8;

// CMD_HTTPREQUEST - method
static uint8_t const HTTPSENDMETHOD_UNSUPPORTED = 0;
static uint8_t const HTTPSENDMETHOD_GET         = 1;
static uint8_t const HTTPSENDMETHOD_POST        = 2;
static uint8_t const HTTPSENDMETHOD_HEAD        = 3;


// Strings
static char const STR_BINPRORDY[] PROGMEM  = "BINPRORDY";


// calculates time difference in milliseconds, taking into consideration the time overflow
// note: time1 must be less than time2 (time1 < time2)
inline uint32_t millisDiff(uint32_t time1, uint32_t time2)
{
    if (time1 > time2)
        // overflow
        return 0xFFFFFFFF - time1 + time2;
    else
        return time2 - time1;
}


#if (WEBESP8266_DEBUG == 1)
// For debug purposes only
// MemoryFree library based on code posted here:
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1213583720/15
// Extended by Matthew Murdoch to include walking of the free list.

extern "C"
{
    extern unsigned int __heap_start;
    extern void *__brkval;
    extern struct __freelist *__flp;
}

struct __freelist
{
  size_t sz;
  struct __freelist *nx;
};


class MemoryDebug
{
public:

    static int freeMemory()
    {
      int free_memory;
      if ((int)__brkval == 0)
      {
        free_memory = ((int)&free_memory) - ((int)&__heap_start);
      }
      else
      {
        free_memory = ((int)&free_memory) - ((int)__brkval);
        free_memory += freeListSize();
      }
      return free_memory;
    }
    
private:
       
    static int freeListSize()
    {
      struct __freelist* current;
      int total = 0;
      for (current = __flp; current; current = current->nx)
      {
        total += 2; /* Add two bytes for the memory block's header  */
        total += (int) current->sz;
      }

      return total;
    }    
};


#endif


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// SoftTimeOut

class SoftTimeOut
{
    public:
        SoftTimeOut(uint32_t time)
            : m_timeOut(time), m_startTime(millis())
        {
        }

        operator bool()
        {
            return millisDiff(m_startTime, millis()) > m_timeOut;
        }
        
        void reset(uint32_t time)
        {
            m_timeOut   = time;
            m_startTime = millis();				
        }

    private:
        uint32_t m_timeOut;
        uint32_t m_startTime;
};	



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// HTTPFields

// data contains a set of key/value zero terminated strings:
//   keyA\0valueA\0keyB\0valueB\0....
HTTPFields::HTTPFields(char const* data, uint8_t itemsCount) 
    : m_data(data), m_itemsCount(itemsCount)
{
}


HTTPFields::HTTPFields()
    : m_data(NULL), m_itemsCount(0)
{
}
    

void HTTPFields::reset(char const* data, uint8_t itemsCount)
{
    m_data       = data;
    m_itemsCount = itemsCount;
}

    
uint8_t HTTPFields::itemsCount() const
{
    return m_itemsCount;
}


// note: doesn't validate index
char const* HTTPFields::getkey(uint8_t index) const
{
    char const* key = m_data;
    for (uint8_t i = 0; i != index; ++i)
        key = strchrnul(strchrnul(key, 0) + 1, 0) + 1;
    return key;
}


// get value at specified index
char const* HTTPFields::operator[](uint8_t index) const
{
    char const* value = strchrnul(m_data, 0) + 1;
    for (uint8_t i = 0; i != index; ++i)
        value = strchrnul(strchrnul(value, 0) + 1, 0) + 1;
    return value;
}


// get value for specified key or NULL if not found
char const* HTTPFields::operator[](char const* key) const
{
    char const* curkey = m_data;
    for (uint8_t i = 0; i != m_itemsCount; ++i)
    {
        if (strcmp(curkey, key) == 0)
            return strchrnul(curkey, 0) + 1;
        curkey = strchrnul(strchrnul(curkey, 0) + 1, 0) + 1;
    }
    return NULL;
}


// ret. required size (in bytes) to contain all fields (included ending zeroes)
uint16_t HTTPFields::calcBufferSize() const
{
    char const* key = m_data;
    for (uint8_t i = 0; i != m_itemsCount; ++i)
        key = strchrnul(strchrnul(key, 0) + 1, 0) + 1;
    return key - m_data;
}




///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// HTTPResponse

HTTPResponse::HTTPResponse()
    : m_contentItems(NULL), 
      m_headerItems(NULL), 
      m_status(HTTPSTATUS_200),
      m_contentType(HTTPCONTENTTYPE_TEXTHTML)
{
}


template <typename T>
void freelist(T* item)
{
    while (item)
    {
        if (item->storage == HTTPResponse::HeapToFree)
            free((void*)item->data);
        T* nitem = item->next;
        delete item;
        item = nitem;
    }
}

HTTPResponse::~HTTPResponse()
{
    freelist(m_contentItems);
    freelist(m_headerItems);
}


// one of HTTPResponse::HTTPSTATUS_xxx constants
void HTTPResponse::setStatus(uint8_t status)
{
    m_status = status;
}


uint8_t HTTPResponse::getStatus()
{
    return m_status;
}


// This is an alternative way to add Contenty-Type header instead of using addHeader() methods.
// User can still add content-type using addHeader methods calling setContentType(HTTPResponse::HTTPCONTENTTYPE_UNSPECIFIED).
// one of HTTPResponse::HTTPCONTENTTYPE_xxx constants
void HTTPResponse::setContentType(uint8_t contentType)
{
    m_contentType = contentType;
}


uint8_t HTTPResponse::getContentType()
{
    return m_contentType;
}


template <typename T>
T* getLast(T* item)
{
    while (item->next)
        item = item->next;
    return item;
}


void HTTPResponse::addHeaderItem(HeaderItem* item)
{
    if (!m_headerItems)
        m_headerItems = item;
    else
        getLast(m_headerItems)->next = item;
}


void HTTPResponse::addHeader(PGM_P key, char const* value, bool copy)
{
    addHeaderItem( new HeaderItem(NULL, 
                                  copy? HTTPResponse::HeapToFree : HTTPResponse::Heap, 
                                  key, 
                                  copy? strdup(value) : value) 
                 );
}


void HTTPResponse::addHeader_P(PGM_P key, PGM_P value)
{
    addHeaderItem( new HeaderItem(NULL, HTTPResponse::Flash, key, value) );
}


void HTTPResponse::addContentItem(ContentItem* item)
{
    if (!m_contentItems)
        m_contentItems = item;
    else
        getLast(m_contentItems)->next = item;
}


void HTTPResponse::addContent(char const* string, bool copy)
{
    addContentItem( new ContentItem(NULL,
                                    copy? HTTPResponse::HeapToFree : HTTPResponse::Heap,
                                    copy? strdup(string) : string,
                                    strlen(string) + 1)
                  );
}


void HTTPResponse::addContentFmt_P(char const* fmt, ...)
{
    va_list args;
    
    va_start(args, fmt);
    int sz = vsnprintf_P(NULL, 0, fmt, args) + 1;
    va_end(args);
    
    char buf[sz];
    
    va_start(args, fmt);
    vsnprintf_P(buf, sz , fmt, args);
    va_end(args);
    
    addContent(buf, true);
}


void HTTPResponse::addContent_P(PGM_P string)
{
    addContentItem( new ContentItem(NULL, HTTPResponse::Flash, string, strlen_P(string) + 1) );
}


// not memory checked!
void* memdup(void const* src, uint32_t len)
{
    void* dst = malloc(len);
    memcpy(dst, src, len);
    return dst;
}


void HTTPResponse::addContent(void const* data, uint16_t length, bool copy)
{
    addContentItem( new ContentItem(NULL,
                                    copy? HTTPResponse::HeapToFree : HTTPResponse::Heap,
                                    copy? memdup(data, length) : data,
                                    length)
                  );
}


void HTTPResponse::addContent_P(PGM_P data, uint16_t length)
{
    addContentItem( new ContentItem(NULL, HTTPResponse::Flash, data, length) );
}


void HTTPResponse::addContent(uint32_t value)
{
    char str[12];
    addContent(ultoa(value, str, 10), true);    
}


void HTTPResponse::addContent(float value, int8_t width, uint8_t prec)
{
    char str[abs(width) + prec + 3];    // todo: verify buf size formula!
    addContent(dtostrf(value, width, prec, str), true);
}


uint8_t HTTPResponse::calcHeadersFieldsCount()
{
    uint8_t count = 0;
    for (HeaderItem* item = m_headerItems; item; item = item->next)
        ++count;
    return count;
}


uint16_t HTTPResponse::calcHeadersBufferSize()
{
    uint16_t len = 0;
    for (HeaderItem* item = m_headerItems; item; item = item->next)
        len += 2 + strlen_P(item->key) + (item->storage == HTTPResponse::Flash? strlen_P((PGM_P)item->data) : strlen((char const*)item->data));
    return len;
}


uint8_t* HTTPResponse::copyHeadersToBuffer(uint8_t* dest)
{
    for (HeaderItem* item = m_headerItems; item; item = item->next)
    {
        strcpy_P((char*)dest, item->key);
        dest += strlen_P(item->key) + 1;
        if (item->storage == HTTPResponse::Flash)
        {
            strcpy_P((char*)dest, (char*)item->data);
            dest += strlen_P((char*)item->data) + 1;
        }
        else
        {
            strcpy((char*)dest, (char*)item->data);
            dest += strlen((char*)item->data) + 1;
        }
    }
    return dest;
}


uint16_t HTTPResponse::calcContentBufferSize()
{
    uint16_t len = 0;
    for (ContentItem* item = m_contentItems; item; item = item->next)
        len += item->dataLength;
    return len;
}


uint8_t* HTTPResponse::copyContentToBuffer(uint8_t* dest)
{
    for (ContentItem* item = m_contentItems; item; item = item->next)
    {
        if (item->storage == HTTPResponse::Flash)
            memcpy_P(dest, item->data, item->dataLength);
        else
            memcpy(dest, item->data, item->dataLength);
        dest += item->dataLength;
    }
    return dest;
}



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Message

WebESP8266::Message::Message()
    : valid(false), ID(0), command(0), dataSize(0), data(NULL)
{
}


WebESP8266::Message::Message(uint8_t ID_, uint8_t command_, uint16_t dataSize_)
    : valid(true), ID(ID_), command(command_), dataSize(dataSize_), data(dataSize_? new uint8_t[dataSize_] : NULL)
{
}


WebESP8266::Message::Message(uint8_t ID_, uint8_t command_, uint8_t* data_, uint16_t dataSize_)
    : valid(true), ID(ID_), command(command_), data(data_), dataSize(dataSize_)
{
}


// warn: memory must be explicitly delete using freeData(). Don't create a destructor to free data!
void WebESP8266::Message::freeData()
{
    if (data != NULL)
    {
        delete[] data;
        data = NULL;
    }
}


    
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// WebESP8266


WebESP8266::WebESP8266()
	: _stream(NULL),
	  _recvID(255),
	  _sendID(0),
	  _isReady(false),
	  _platform(PLATFORM_BASELINE)
{
}


void WebESP8266::begin(Stream& stream)
{
	_stream = &stream;
	send_CMD_READY();
}


void WebESP8266::setupWebRoutes(WebRoute* webRoutes, uint8_t count)
{
    _webRoutes      = webRoutes;
    _webRoutesCount = count;
}


bool WebESP8266::isReady()
{
	return _isReady;
}


bool WebESP8266::checkReady()
{
	if (!isReady())
		send_CMD_READY();
	return isReady();
}


uint8_t WebESP8266::getPlatform()
{
	checkReady();
	return _platform;
}


void WebESP8266::yield()
{
	if (_stream->available() > 0)
	{
		Message msg = receive();
		if (msg.valid)
		{
			if (msg.command != CMD_ACK)
				processMessage(&msg);
		}
	}
}


// must not process CMD_ACK messages
void WebESP8266::processMessage(Message* msg)
{
	switch (msg->command)
	{
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
		case CMD_IOAGET:
			handle_CMD_IOAGET(msg);
			break;
        case CMD_GETHTTPHANDLEDPAGES:
            handle_CMD_GETHTTPHANDLEDPAGES(msg);
            break;
        case CMD_HTTPREQUEST:
            handle_CMD_HTTPREQUEST(msg);
            break;
	}			
	msg->freeData();
}


int WebESP8266::readByte(uint32_t timeOut)
{
	SoftTimeOut timeout(timeOut);
	while (!timeout)
		if (_stream->available() > 0)
			return _stream->read();
	return -1;
}


// note: timeout resets each time a byte is received
uint32_t WebESP8266::readBuffer(uint8_t* buffer, uint32_t size, uint32_t timeOut)
{
	for (uint32_t i = 0; i != size; ++i)
	{
		int b = readByte(timeOut);
		if (b < 0)
			return i;
		*buffer++ = b;
	}
	return size;
}


void WebESP8266::discardData(uint32_t size, uint32_t timeOut)
{
	for (uint32_t i = 0; i != size; ++i)
		if (readByte(timeOut) < 0)
			return;
}


WebESP8266::Message WebESP8266::receive()
{
	Message msg;
	SoftTimeOut timeout(WAIT_MSG_TIMEOUT);
	while (!timeout)
	{
		// ID
		int16_t r = readByte(INTRA_MSG_TIMEOUT);
		if (r < 0)
			continue;
		msg.ID = r;

		// Command
		r = readByte(INTRA_MSG_TIMEOUT);
		if (r < 0)
			continue;
		msg.command = r;

		// Data Size Low
		r = readByte(INTRA_MSG_TIMEOUT);
		if (r < 0)
			continue;
		msg.dataSize = r;

		// Data Size High
		r = readByte(INTRA_MSG_TIMEOUT);
		if (r < 0)
			continue;
		msg.dataSize |= r << 8;
        
		// Data
        if (msg.dataSize > MAX_DATA_SIZE)
        {
            discardData(msg.dataSize, INTRA_MSG_TIMEOUT);
            continue;
        }
        msg.data = new uint8_t[msg.dataSize];
        if (readBuffer(msg.data, msg.dataSize, INTRA_MSG_TIMEOUT) < msg.dataSize)
        {
            msg.freeData();
            continue;
        }
		
		// check ID
		if (msg.ID == _recvID)
		{
			msg.freeData();
			continue;
		}
		_recvID = msg.ID;
		
		msg.valid = true;
		return msg;
	}			
	return msg;
}


uint8_t WebESP8266::getNextID()
{
	return ++_sendID;
}


void WebESP8266::send(Message const& msg)
{
	_stream->write(msg.ID);
	_stream->write(msg.command);
	_stream->write(msg.dataSize & 0xFF);
	_stream->write((msg.dataSize >> 8) & 0xFF);
	if (msg.dataSize > 0)
		_stream->write(msg.data, msg.dataSize);
}


// send ACK without parameters
void WebESP8266::sendNoParamsACK(uint8_t ackID)
{
    uint8_t data[1] = {ackID};
    send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
}


WebESP8266::Message WebESP8266::waitACK(uint8_t ackID)
{
	Message msg;
	SoftTimeOut timeout(GETACK_TIMEOUT);
	while (!timeout)
	{
		msg = receive();
		if (msg.valid)
		{
            uint8_t msgAckID = msg.data[0];
            if (msgAckID == ackID)
                return msg;
            msg.freeData();	// discard this ACK
		}
	}
	msg.valid = false;
	return msg;
}


bool WebESP8266::waitNoParamsACK(uint8_t ackID)
{
	Message msg = waitACK(ackID);
	if (msg.valid)
	{
		msg.freeData();
		return true;
	}
	return false;
}		


void WebESP8266::handle_CMD_READY(Message* msg)
{    
	// process message
    uint8_t protocolVersion = msg->data[0];
    _platform               = msg->data[1];
    char const* magicString = (char const*)msg->data + 2;
	_isReady  = (protocolVersion == PROTOCOL_VERSION && strcmp_P(magicString, STR_BINPRORDY) == 0);
    
	// send ACK with parameters
    uint8_t data[13] = {msg->ID, PROTOCOL_VERSION, PLATFORM_THIS};
    strcpy_P((char*)data + 3, STR_BINPRORDY);
    send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
}


void WebESP8266::handle_CMD_IOCONF(Message* msg)
{
	// process message
    uint8_t pin   = msg->data[0];
    uint8_t flags = msg->data[1];
	if (flags & PIN_CONF_OUTPUT)
		pinMode(pin, OUTPUT);
	else
		pinMode(pin, (flags & PIN_CONF_PULLUP)? INPUT_PULLUP : INPUT);
				
	// send simple ACK
	sendNoParamsACK(msg->ID);
}


void WebESP8266::handle_CMD_IOSET(Message* msg)
{
	// process message
    uint8_t pin   = msg->data[0];
    uint8_t state = msg->data[1];
	digitalWrite(pin, state);
	
	// send simple ACK
	sendNoParamsACK(msg->ID);
}


void WebESP8266::handle_CMD_IOGET(Message* msg)
{
	// process message
	uint8_t pin = msg->data[0];
	bool state = digitalRead(pin);
	
	// send ACK with parameters
    uint8_t data[2] = {msg->ID, state};
    send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
}


void WebESP8266::handle_CMD_IOASET(Message* msg)
{
	// process message
    uint8_t  pin = msg->data[0];
    uint16_t state = msg->data[1] + (msg->data[2] << 8);
	analogWrite(pin, state);
	
	// send simple ACK
	sendNoParamsACK(msg->ID);
}


void WebESP8266::handle_CMD_IOAGET(Message* msg)
{
	// process message
    uint8_t pin = msg->data[0];
	uint16_t state = analogRead(pin);
	
	// send ACK with parameters
    uint8_t data[3] = {msg->ID, state & 0xFF, state >> 8};
	send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
}		


void WebESP8266::handle_CMD_GETHTTPHANDLEDPAGES(Message* msg)
{
    // calc message size
    uint16_t msgSize = sizeof(uint8_t);    // uint8_t for items count
    for (uint8_t i = 0; i != _webRoutesCount; ++i)
        msgSize += strlen_P(_webRoutes[i].page) + 1;
    
    // send ACK with parameters
    uint8_t data[1 + msgSize];
    uint8_t* wpos = data;
    *wpos++ = msg->ID;
    *wpos++ = _webRoutesCount;
    for (uint8_t i = 0; i != _webRoutesCount; ++i)
    {        
        strcpy_P((char*)wpos, _webRoutes[i].page);
        wpos += strlen_P(_webRoutes[i].page) + 1;
    }
    send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
}


void WebESP8266::handle_CMD_HTTPREQUEST(Message* msg)
{
    //// decode message
    
    HTTPRequest request;
    
    uint8_t const* rpos = msg->data;
    
    // method (get, post...)
    request.method = (HTTPRequest::Method)*rpos++;
    
    // page index (as registered by handle_CMD_GETHTTPHANDLEDPAGES)
    request.pageIndex = *rpos++;
    
    // page (zero terminated string)
    request.page = (char const*)rpos;
    rpos += strlen(request.page) + 1;
    
    // headers count
    uint8_t headersCount = *rpos++;
    
    // headers key->value
    request.headers.reset((char const*)rpos, headersCount);
    rpos += request.headers.calcBufferSize();

    // query count
    uint8_t queryCount = *rpos++;
    
    // query key->value
    request.query.reset((char const*)rpos, queryCount);
    rpos += request.query.calcBufferSize();

    // form count
    uint8_t formCount = *rpos++;
    
    // form key->value
    request.form.reset((char const*)rpos, formCount);
    rpos += request.form.calcBufferSize();
    
    // call the handler and send ACK with parameters
    if (request.pageIndex < _webRoutesCount)
    {
        HTTPResponse response;
        _webRoutes[request.pageIndex].handler(request, response);
        uint16_t headersBufferSize = response.calcHeadersBufferSize();
        uint16_t contentBufferSize = response.calcContentBufferSize();
        uint16_t msgSize = 1 + 1 + 1 + 2 + headersBufferSize + contentBufferSize;   // +1 = status, +1 = headers fields count, +1 = content type, +2 = content length
        uint8_t data[1 + msgSize];    
        uint8_t* wpos = data;
        
        // ACK - ID
        *wpos++ = msg->ID;
        
        // status
        *wpos++ = response.getStatus();
        
        // header fields count
        *wpos++ = response.calcHeadersFieldsCount();
        
        // header fields
        wpos = response.copyHeadersToBuffer(wpos);

        // content-type header
        *wpos++ = response.getContentType();
            
        // content length
        *wpos++ = contentBufferSize & 0xFF;
        *wpos++ = contentBufferSize >> 8;
        response.copyContentToBuffer(wpos);
        
        // send ACK
        send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
    }    
    
}


bool WebESP8266::send_CMD_READY()
{
	_isReady = false;
	for (uint8_t i = 0; i != MAX_RESEND_COUNT; ++i)
	{
		// send message        
        uint8_t data[12] = {PROTOCOL_VERSION, PLATFORM_THIS};
        strcpy_P((char*)data + 2, STR_BINPRORDY);
        uint8_t msgID = getNextID();
        send(Message(msgID, CMD_READY, data, sizeof(data)));            
		
		// wait for ACK
		Message msg = waitACK(msgID);
		if (msg.valid)
		{
            uint8_t protocolVersion = msg.data[1];
            _platform = msg.data[2];
            char const* magicString = (char const*)msg.data + 3;
			_isReady  = (protocolVersion == PROTOCOL_VERSION && strcmp_P(magicString, STR_BINPRORDY) == 0);
			msg.freeData();
			return true;
		}
	}
	return false;
}


bool WebESP8266::send_CMD_IOCONF(uint8_t pin, uint8_t flags)
{
	if (checkReady())
	{
		for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
		{
			// send message			
            uint8_t data[2] = {pin, flags};
            uint8_t msgID = getNextID();
			send(Message(msgID, CMD_IOCONF, data, sizeof(data)));
			
			// wait for ACK
			if (waitNoParamsACK(msgID))
				return true;
		}
		_isReady = false;	// no more ready
	}
	return false;
}


bool WebESP8266::send_CMD_IOSET(uint8_t pin, uint8_t state)
{
	if (checkReady())
	{
		for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
		{
			// send message            
            uint8_t data[2] = {pin, state};                
            uint8_t msgID = getNextID();
            send(Message(msgID, CMD_IOSET, data, sizeof(data)));
			
			// wait for ACK
			if (waitNoParamsACK(msgID))
				return true;
		}
		_isReady = false;	// no more ready
	}
	return false;
}


bool WebESP8266::send_CMD_IOGET(uint8_t pin, uint8_t* state)
{
	if (checkReady())
	{
		for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
		{
			// send message
            uint8_t data[1] = {pin};
            uint8_t msgID = getNextID();
            send(Message(msgID, CMD_IOGET, data, sizeof(data)));
			
			// wait for ACK
			Message msg = waitACK(msgID);
			if (msg.valid)
			{
                *state = msg.data[1];
                msg.freeData();
				return true;
			}
		}
		_isReady = false;	// no more ready
	}
	return false;
}


bool WebESP8266::send_CMD_IOASET(uint8_t pin, uint16_t state)
{
	if (checkReady())
	{
		for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
		{
			// send message
            uint8_t data[3] = {pin, state & 0xFF, state >> 8};
            uint8_t msgID = getNextID();
            send(Message(msgID, CMD_IOASET, data, sizeof(data)));
			
			// wait for ACK
			if (waitNoParamsACK(msgID))
				return true;
		}
		_isReady = false;	// no more ready
	}
	return false;
}


bool WebESP8266::send_CMD_IOAGET(uint8_t pin, uint16_t* state)
{
	if (checkReady())
	{
		for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
		{
			// send message
            uint8_t data[1] = {pin};
			uint8_t msgID = getNextID();
			send(Message(msgID, CMD_IOAGET, data, sizeof(data)));
			
			// wait for ACK
			Message msg = waitACK(msgID);
			if (msg.valid)
			{
                *state = msg.data[1] + (msg.data[2] << 8);
				msg.freeData();
				return true;
			}
		}
		_isReady = false;	// no more ready
	}
	return false;
}


