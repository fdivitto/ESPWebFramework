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


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPResponse

MTD_FLASHMEM HTTPResponse::HTTPResponse(HTTPHandler *httpHandler, char const *status, char const *content)
    : m_httpHandler(httpHandler), m_status(status), m_headersFlushed(false) {
  // content (if present, otherwise use addContent())
  if (content)
    addContent(content);
}

HTTPHandler::Request &MTD_FLASHMEM HTTPResponse::getRequest() {
  return m_httpHandler->getRequest(); 
}

// accept RAM or Flash strings
void MTD_FLASHMEM HTTPResponse::addHeader(char const *key, char const *value) {
  m_headers.add(key, value); 
}

// accept RAM or Flash data
void MTD_FLASHMEM HTTPResponse::addContent(void const *data, uint32_t length, bool freeOnDestroy) {
  m_content.addChunk((char *)data, length, freeOnDestroy);
}

// accept RAM or Flash strings
// WARN: data is not copied! Just a pointer is stored
// can be called many times
void MTD_FLASHMEM HTTPResponse::addContent(char const *str, bool freeOnDestroy) {
  addContent(str, f_strlen(str), freeOnDestroy);
}

// can be called many times
// WARN: src content is not copied! Just data pointers are stored
void MTD_FLASHMEM HTTPResponse::addContent(LinkedCharChunks *src) {
  m_content.addChunks(src); 
}

void MTD_FLASHMEM HTTPResponse::flushHeaders(uint32_t contentLength) {
  if (!m_headersFlushed) {
    // status line
    m_httpHandler->getSocket()->writeFmt(FSTR("HTTP/1.1 %s\r\n"), m_status);

    // HTTPResponse headers
    addHeader(FSTR("Connection"), FSTR("close"));

    // user headers
    for (uint32_t i = 0; i != m_headers.getItemsCount(); ++i) {
      Fields::Item *item = m_headers[i];
      m_httpHandler->getSocket()->writeFmt(FSTR("%s: %s\r\n"), APtr<char>(t_strdup(item->key)).get(),
                                           APtr<char>(t_strdup(item->value)).get());
    }

    // content length header
    m_httpHandler->getSocket()->writeFmt(FSTR("%s: %d\r\n\r\n"), STR_Content_Length, contentLength);

    m_headersFlushed = true;
  }
}

// should be called only after setStatus, addHeader and addContent
void MTD_FLASHMEM HTTPResponse::flush() {
  // headers
  flushHeaders(m_content.getItemsCount());

  // actual content
  if (m_content.getItemsCount() > 0) {
    CharChunksIterator iter = m_content.getIterator();
    CharChunkBase *chunk = iter.getCurrentChunk();
    while (chunk) {
      if (m_httpHandler->getSocket()->write((uint8_t const *)chunk->data, chunk->getItems()) < 0)
        break;
      chunk = iter.moveToNextChunk();
    }
    m_content.clear();
  }
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// ParameterReplacer

MTD_FLASHMEM ParameterReplacer::ParameterReplacer()
    : m_params(NULL), m_blockParams(NULL), m_strStart(NULL), m_strEnd(NULL) {
  m_results.add(new LinkedCharChunks);
}

MTD_FLASHMEM ParameterReplacer::~ParameterReplacer() {
  for (uint32_t i = 0; i != m_results.size(); ++i)
    delete m_results[i];
}

void MTD_FLASHMEM ParameterReplacer::start(char const *strStart, char const *strEnd, Params *params, BlockParams *blockParams) {
  m_params = params;
  m_blockParams = blockParams;
  m_strStart = strStart;
  m_strEnd = strEnd;
  processInput();
}

void MTD_FLASHMEM ParameterReplacer::processInput() {
  char const *curc = m_strStart;
  char const *start = curc;
  char const *curBlockKey = NULL;
  char const *curBlockKeyEnd = NULL;
  while (curc != m_strEnd) {
    char c0 = getChar(curc);
    if (c0 == '{') {
      char c1 = getChar(curc + 1);
      if (c1 == '{') {
        // found "{{"
        // push previous content
        m_results.last()->addChunk(start, curc - start, false);
        // process parameter tag
        start = curc = replaceTag(curc);
        continue;
      } else if (c1 == '%') {
        // found "{%"
        // push previous content
        if (curBlockKey && curBlockKeyEnd) {
          m_results.last()->addChunk(start, curc - start, false);
          m_blocks.add(curBlockKey, curBlockKeyEnd, m_results.last());
          m_results.add(new LinkedCharChunks);
        }
        // process block tag
        curBlockKey = extractTagStr(curc, &curBlockKeyEnd);
        start = curc = curBlockKeyEnd + 2; // bypass "%}"
        // if this is the first block tag then this is the template file name
        if (m_template.get() == NULL) {
          m_template.reset(f_strdup(curBlockKey, curBlockKeyEnd));
          curBlockKey = NULL;
          curBlockKeyEnd = NULL;
        }
        continue;
      }
    }
    ++curc;
  }
  m_results.last()->addChunk(start, m_strEnd - start, false);
  if (curBlockKey && curBlockKeyEnd) {
    m_blocks.add(curBlockKey, curBlockKeyEnd, m_results.last());
  }
}

char const *MTD_FLASHMEM ParameterReplacer::replaceTag(char const *curc) {
  char const *tagEnd;
  char const *tagStart = extractTagStr(curc, &tagEnd);
  if (getChar(tagStart) == '#') {
    // replace multiple parameters ('0param', '1param', ...)
    ++tagStart;
    uint32_t tagLen = tagEnd - tagStart;
    char tag[tagLen];
    f_memcpy(tag, tagStart, tagLen);
    tag[tagLen] = 0;
    for (uint32_t index = 0;; ++index) {
      char const *fulltagname = f_printf(FSTR("%d%s"), index, tag);
      Params::Item *item = m_params->getItem(fulltagname);
      if (item)
        m_results.last()->addChunks(&item->value); // push parameter content
      else
        break;
    }
  } else {
    // replace one parameter
    Params::Item *item = m_params->getItem(tagStart, tagEnd);
    if (item)
      m_results.last()->addChunks(&item->value); // push parameter content
    else if (m_blockParams) {
      BlockParams::Item *item = m_blockParams->getItem(tagStart, tagEnd);
      if (item)
        m_results.last()->addChunks(item->value); // push block parameter content
    }
  }
  return tagEnd + 2; // bypass "}}"
}

char const *MTD_FLASHMEM ParameterReplacer::extractTagStr(char const *curc, char const **tagEnd) {
  char const *tagStart = curc + 2; // by pass "{{" or "{%"
  *tagEnd = tagStart;
  while (*tagEnd < m_strEnd && getChar(*tagEnd) != '}' && getChar(*tagEnd) != '%')
    ++*tagEnd;
  return tagStart;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPTemplateResponse

MTD_FLASHMEM HTTPTemplateResponse::HTTPTemplateResponse(HTTPHandler *httpHandler, char const *filename)
    : HTTPResponse(httpHandler, NULL), m_filename(filename) {  
}

void MTD_FLASHMEM HTTPTemplateResponse::addParamStr(char const *key, char const *value) {
  LinkedCharChunks *linkedCharChunks = m_params.add(key);
  linkedCharChunks->addChunk(value);
}

void MTD_FLASHMEM HTTPTemplateResponse::addParamInt(char const *key, int32_t value) {
  char *valueStr = f_printf(FSTR("%d"), value);
  LinkedCharChunks *linkedCharChunks = m_params.add(key);
  linkedCharChunks->addChunk(valueStr, f_strlen(valueStr), true); // true = need to free
}

void MTD_FLASHMEM HTTPTemplateResponse::addParamFmt(char const *key, char const *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  uint16_t len = f_vsprintf(NULL, fmt, args);
  va_end(args);
  char *buf = new char[len + 1];
  va_start(args, fmt);
  f_vsprintf(buf, fmt, args);
  va_end(args);

  LinkedCharChunks *linkedCharChunks = m_params.add(key);
  linkedCharChunks->addChunk(buf, len, true); // true = need to free
}

LinkedCharChunks *MTD_FLASHMEM HTTPTemplateResponse::addParamCharChunks(char const *key) {
  return m_params.add(key); 
}

HTTPTemplateResponse::Params *MTD_FLASHMEM HTTPTemplateResponse::getParams() {
  return &m_params; 
}

void MTD_FLASHMEM HTTPTemplateResponse::flush() {
  // {{now}} predefined parameter : display date/time
  char datetimeStr[34];
  DateTime::now().format(datetimeStr, FSTR("%c"));
  addParamStr(STR_now, datetimeStr);

  // {{uptime}} predefined parameter : display uptime
  char uptimeStr[22];
  ConfigurationManager::getUpTimeStr(uptimeStr);
  addParamStr(STR_uptime, uptimeStr);

  processFileRequest();
  HTTPResponse::flush();
}

void MTD_FLASHMEM HTTPTemplateResponse::processFileRequest() {
  FlashFileSystem::Item file;
  if (m_filename && FlashFileSystem::find(m_filename, &file)) {
    // found
    setStatus(STR_200_OK);
    addHeader(STR_Content_Type, FSTR("text/html; charset=UTF-8"));

    // replace parameters
    m_replacer.start((char const *)file.data, (char const *)file.data + file.datalength, &m_params, NULL);

    // is this a specialized file (contains {%..%} blocks)?
    if (m_replacer.getBlocks()->getItemsCount() > 0 && m_replacer.getTemplateFilename() != NULL) {
      // this is a specialized file
      // load template file
      file.reset();
      if (FlashFileSystem::find(m_replacer.getTemplateFilename(), &file)) {
        // replace parameters and blocks of template file
        m_templateReplacer.start((char const *)file.data, (char const *)file.data + file.datalength, &m_params,
                                 m_replacer.getBlocks());
        // flush resulting content
        addContent(m_templateReplacer.getResult());
        return;
      }
    } else {
      // just flush this file (contains only {{...}} blocks)
      addContent(m_replacer.getResult());
      return;
    }
  }
  // not found
  setStatus(STR_404_Not_Found);
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// MultipartFormDataProcessor

class MultipartFormDataProcessor {
public:
  // Sequence is: WaitingForFirstBoundary -> {BoundaryFound -> DecodingHeaders -> (GettingValue | GettingFile)} ->
  // EndOfContent
  enum States { WaitingForFirstBoundary, BoundaryFound, DecodingHeaders, GettingValue, GettingFile, EndOfContent };

  static uint32_t const HEADERS_CHUNK_SIZE = 16;
  static uint32_t const FORM_CHUNK_SIZE = 16;

  char const *boundary;
  int32_t boundarylen;
  States state;
  int32_t substate;
  LinkedCharChunks *headers;
  HTTPHandler::Fields *formfields;
  LinkedCharChunks *valueStorage;
  CharChunksIterator nameBegin, nameEnd;
  FlashFile file;
  List<LinkedCharChunks>
      chunksFactory; // handles creation and destruction of "headers" and "valueStorage" multiple instances

  MultipartFormDataProcessor(char const *boundary_, HTTPHandler::Fields *formfields_);
  void push(char c);

private:
  void handle_WaitingForFirstBoundary(char c);
  void handle_BoundaryFound(char c);
  void handle_DecodingHeaders(char c);
  void handle_GettingFile_GettingValue(char c);
  bool extractParameter(char const *name, CharChunksIterator curpos, CharChunksIterator *nameBegin,
                        CharChunksIterator *begin, CharChunksIterator *end);
  CharChunksIterator getFilename(CharChunksIterator fullpathBegin, CharChunksIterator fullpathEnd);
};

MTD_FLASHMEM MultipartFormDataProcessor::MultipartFormDataProcessor(char const *boundary_,
                                                                    HTTPHandler::Fields *formfields_)
    : boundary(boundary_), boundarylen(f_strlen(boundary)), state(WaitingForFirstBoundary), substate(0),
      formfields(formfields_) {}

MTD_FLASHMEM bool MultipartFormDataProcessor::extractParameter(char const *name, CharChunksIterator curpos,
                                                               CharChunksIterator *nameBegin, CharChunksIterator *begin,
                                                               CharChunksIterator *end) {
  if (curpos != CharChunksIterator()) {
    *nameBegin = t_strstr(curpos, CharIterator(name));
    if (*nameBegin != CharChunksIterator()) {
      // bypass "name"
      CharChunksIterator it = *nameBegin + f_strlen(name);

      // bypass spaces and a quote
      bool hasQuote = false;
      for (; it != CharChunksIterator() && (isspace(*it) || *it == '"'); ++it)
        if (*it == '"')
          hasQuote = true;
      *begin = it;

      // look for spaces or a quote
      while (it != CharChunksIterator() && ((!hasQuote && !isspace(*it)) || (hasQuote && *it != '"')))
        ++it;
      *end = it;

      return true;
    }
  }
  return false;
}

// returns filename, bypassing the file path
CharChunksIterator MTD_FLASHMEM
    MultipartFormDataProcessor::getFilename(CharChunksIterator fullpathBegin, CharChunksIterator fullpathEnd) {
  CharChunksIterator filenameBegin = fullpathBegin;
  while (fullpathBegin != fullpathEnd) {
    if (*fullpathBegin == '\\' | *fullpathBegin == '/')
      filenameBegin = fullpathBegin + 1;
    ++fullpathBegin;
  }
  return filenameBegin;
}

void MTD_FLASHMEM MultipartFormDataProcessor::handle_WaitingForFirstBoundary(char c) {
  if (substate < 2) {
    // bypass first "--"
    ++substate;
  } else if (c == boundary[substate - 2]) {
    ++substate;
    if (substate - 2 == boundarylen) {
      // found initial boundary
      state = BoundaryFound;
      substate = 0;
    }
  } else {
    // reset boundary matching (this should not happen)
    substate = 0;
  }
}

void MTD_FLASHMEM MultipartFormDataProcessor::handle_BoundaryFound(char c) {
  static char const EOL[2] = {0x0D, 0x0A};
  static char const EOE[4] = {'-', '-', 0x0D, 0x0A}; // end of content (just after the ending boundary)
  if (c == EOL[substate]) {
    ++substate;
    if (substate == 2) {
      // found \r\n after boundary
      state = DecodingHeaders;
      substate = 0;
      headers = chunksFactory.add();
    }
  } else if (c == EOE[substate]) {
    ++substate;
    if (substate == 4) {
      // found "--\r\n" after boundary
      state = EndOfContent;
      substate = 0;
    }
  }
}

void MTD_FLASHMEM MultipartFormDataProcessor::handle_DecodingHeaders(char c) {
  static char const EOH[4] = {0x0D, 0x0A, 0x0D, 0x0A};
  if (c == EOH[substate]) {
    ++substate;
    if (substate == 2) {
      // useful if this is not an EOH to separate headers
      headers->append(0x0D, 1);
    } else if (substate == 4) {
      // end of headers
      headers->append(0, 1); // add string terminating zero

      // look for "name" parameter
      CharChunksIterator keyBegin;
      extractParameter(FSTR(" name="), headers->getIterator(), &keyBegin, &nameBegin, &nameEnd);

      // look for "filename" parameter
      CharChunksIterator filenameBegin, filenameEnd;

      if (extractParameter(FSTR(" filename="), headers->getIterator(), &keyBegin, &filenameBegin, &filenameEnd)) {
        //// this is a file
        // add "filename" to form fields
        filenameBegin = getFilename(filenameBegin,
                                    filenameEnd); // some browsers send a full path instead of a simple file name (IE)
        formfields->add(keyBegin + 1, keyBegin + 9, filenameBegin, filenameEnd);

        // extract Content-Type parameter
        CharChunksIterator contentTypeBegin, contentTypeEnd;
        if (extractParameter(FSTR("Content-Type:"), filenameEnd, &keyBegin, &contentTypeBegin, &contentTypeEnd)) {
          // add "Content-Type" to form fields
          formfields->add(keyBegin, keyBegin + 12, contentTypeBegin, contentTypeEnd);

          // create file
          file.create(APtr<char>(t_strdup(filenameBegin, filenameEnd)).get(),
                      APtr<char>(t_strdup(contentTypeBegin, contentTypeEnd)).get());

          state = GettingFile;
        } else {
          // missing content-type, cannot get as file!
          state = GettingValue;
        }
      } else {
        //// this is a normal field
        valueStorage = chunksFactory.add();
        state = GettingValue;
      }
      substate = 0;
    }
  } else {
    // add to headers buffer
    headers->append(c, HEADERS_CHUNK_SIZE);
    substate = 0;
  }
}

void MTD_FLASHMEM MultipartFormDataProcessor::handle_GettingFile_GettingValue(char c) {
  static char const BOB[4] = {0x0D, 0x0A, '-', '-'}; // begin of boundary (just before every boundary)
  if (substate < 4 && c == BOB[substate]) {
    ++substate;
  } else if (substate >= 4 && c == boundary[substate - 4]) {
    ++substate;
    if (substate - 4 == boundarylen) {
      // found boundary, end file or value
      if (state == GettingFile)
        file.close();
      else
        formfields->add(nameBegin, nameEnd, valueStorage->getIterator(), CharChunksIterator());
      state = BoundaryFound;
      substate = 0;
    }
  } else {
    if (substate > 0) {
      // first "substate" bytes seemed the BOB or Boundary, but they were not!
      int32_t cnt = substate;
      substate = 0;
      if (state == GettingFile)
        file.write(BOB, 1);
      else
        valueStorage->append(BOB[0], FORM_CHUNK_SIZE);
      for (int32_t i = 1; i != cnt; ++i)
        push(i < 4 ? BOB[i] : boundary[i - 4]);
      push(c);
    } else {
      if (state == GettingFile)
        file.write(&c, 1);
      else
        valueStorage->append(c, FORM_CHUNK_SIZE);
    }
  }
}

void MTD_FLASHMEM MultipartFormDataProcessor::push(char c) {
  switch (state) {
  case WaitingForFirstBoundary:
    handle_WaitingForFirstBoundary(c);
    break;
  case BoundaryFound:
    handle_BoundaryFound(c);
    break;
  case DecodingHeaders:
    handle_DecodingHeaders(c);
    break;
  case GettingFile:
  case GettingValue:
    handle_GettingFile_GettingValue(c);
    break;
  }
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPHandler

void MTD_FLASHMEM HTTPHandler::connectionHandler() {
  getSocket()->setTimeOut(TIMEOUT);
  while (getSocket()->isConnected()) {
    CharChunkBase *chunk = m_receivedData.addChunk(CHUNK_CAPACITY);
    int32_t bytesRecv = getSocket()->read(chunk->data, CHUNK_CAPACITY);
    if (bytesRecv <= 0)
      break;
    chunk->setItems(bytesRecv);
    if (processRequest())
      break;
  }
  m_receivedData.clear();
  m_request.query.clear();
  m_request.headers.clear();
  m_request.form.clear();
}

bool MTD_FLASHMEM HTTPHandler::processRequest() {
  // look for 0x0D 0x0A 0x0D 0x0A
  CharChunksIterator headerEnd =
      t_strstr(m_receivedData.getIterator(), CharChunksIterator(), CharIterator(FSTR("\x0D\x0A\x0D\x0A")));
  if (headerEnd.isValid()) {
    // move header end after CRLFCRLF
    headerEnd += 4;

    CharChunksIterator curc = m_receivedData.getIterator();

    // extract method (GET, POST, etc..)
    CharChunksIterator method = curc;
    while (curc != headerEnd && *curc != ' ')
      ++curc;
    *curc++ = 0; // ends method
    if (t_strcmp(method, CharIterator(FSTR("GET"))) == 0)
      m_request.method = Get;
    else if (t_strcmp(method, CharIterator(FSTR("POST"))) == 0)
      m_request.method = Post;
    else if (t_strcmp(method, CharIterator(FSTR("HEAD"))) == 0)
      m_request.method = Head;
    else
      m_request.method = Unsupported;

    // extract requested page and query parameters
    m_request.requestedPage = curc;
    while (curc != headerEnd) {
      if (*curc == '?') {
        *curc++ = 0; // ends requestedPage
        curc = extractURLEncodedFields(curc, headerEnd, &m_request.query);
        break;
      } else if (*curc == ' ') {
        *curc++ = 0; // ends requestedPage
        break;
      }
      ++curc;
    }

    // bypass HTTP version
    while (curc != headerEnd && *curc != 0x0D)
      ++curc;

    // extract headers
    curc = extractHeaders(curc, headerEnd, &m_request.headers);

    // get content length (may be NULL)
    char const *contentLengthStr = m_request.headers[STR_Content_Length];
    int32_t contentLength = contentLengthStr ? strtol(contentLengthStr, NULL, 10) : 0;

    if (m_request.method == Post) {
      // check content type (POST)
      char const *contentType = m_request.headers[STR_Content_Type];
      if (contentType && f_strstr(contentType, FSTR("multipart/form-data"))) {
        //// content type is multipart/form-data
        processMultipartFormData(headerEnd, contentLength, contentType);
      } else if (contentType == NULL ||
                 (contentType && f_strstr(contentType, FSTR("application/x-www-form-urlencoded")))) {
        //// content type is application/x-www-form-urlencoded
        processXWWWFormUrlEncoded(headerEnd, contentLength);
      }
    } else
      dispatch();

    return true;
  } else {
    // header is not complete
    return false;
  }
}

void MTD_FLASHMEM HTTPHandler::processMultipartFormData(CharChunksIterator headerEnd, int32_t contentLength,
                                                        char const *contentType) {
  char const *boundary = f_strstr(contentType, FSTR("boundary="));
  if (boundary) {
    // go to begin of boundary string
    boundary += 9;

    MultipartFormDataProcessor proc(boundary, &m_request.form);

    // consume already received data
    CharChunksIterator contentStart = headerEnd;
    while (contentStart != CharChunksIterator())
      proc.push(*contentStart++);

    // consume new data
    while (getSocket()->isConnected() && proc.state != MultipartFormDataProcessor::EndOfContent) {
      char c;
      int32_t bytesRecv = getSocket()->read(&c, 1);
      if (bytesRecv <= 0)
        break;
      proc.push(c);
    }

    // dispatch must be inside this block, to have MultipartFormDataProcessor content available
    dispatch();
  } else
    dispatch();
}

void MTD_FLASHMEM HTTPHandler::processXWWWFormUrlEncoded(CharChunksIterator headerEnd, int32_t contentLength) {
  // look for data (maybe POST data)
  if (contentLength > 0) {
    // download additional content
    int32_t missingBytes = headerEnd.getPosition() + contentLength - m_receivedData.getItemsCount();
    while (getSocket()->isConnected() && missingBytes > 0) {
      int32_t bytesToRead = (CHUNK_CAPACITY < missingBytes ? CHUNK_CAPACITY : missingBytes);
      CharChunkBase *chunk = m_receivedData.addChunk(bytesToRead);
      int32_t bytesRecv = getSocket()->read(chunk->data, bytesToRead);
      if (bytesRecv <= 0)
        break;
      chunk->setItems(bytesRecv);
      missingBytes -= chunk->getItems();
    }
    m_receivedData.append(0); // add additional terminating "0"

    CharChunksIterator contentStart = m_receivedData.getIterator(); // cannot use directly headerEnd because added data
    contentStart += headerEnd.getPosition();
    extractURLEncodedFields(contentStart, CharChunksIterator(), &m_request.form);
  }

  dispatch();
}

CharChunksIterator MTD_FLASHMEM
    HTTPHandler::extractURLEncodedFields(CharChunksIterator begin, CharChunksIterator end, Fields *fields) {
  fields->setUrlDecode(true);
  CharChunksIterator curc = begin;
  CharChunksIterator key = curc;
  CharChunksIterator value;
  while (curc != end) {
    if (*curc == '=') {
      *curc = 0; // ends key
      value = curc;
      ++value; // bypass '='
    } else if (*curc == '&' || *curc == ' ' || curc.isLast()) {
      bool endLoop = (*curc == ' ' || curc.isLast());
      *curc++ = 0; // zero-ends value
      if (key.isValid() && value.isValid()) {
        fields->add(key, value);            // store parameter
        key = value = CharChunksIterator(); // reset
      }
      if (endLoop)
        break;
      key = curc;
    } else
      ++curc;
  }
  return curc;
}

CharChunksIterator MTD_FLASHMEM
    HTTPHandler::extractHeaders(CharChunksIterator begin, CharChunksIterator end, Fields *fields) {
  CharChunksIterator curc = begin;
  CharChunksIterator key;
  CharChunksIterator value;
  while (curc != end) {
    if (*curc == 0x0D && key.isValid() && value.isValid()) // CR?
    {
      *curc = 0; // ends key
      // store header
      fields->add(key, value);
      key = value = CharChunksIterator(); // reset
    } else if (!isspace(*curc) && !key.isValid()) {
      // bookmark "key"
      key = curc;
    } else if (!value.isValid() && *curc == ':') {
      *curc++ = 0; // ends value
      // bypass spaces
      while (curc != end && isspace(*curc))
        ++curc;
      // bookmark value
      value = curc;
    }
    ++curc;
  }
  return curc;
}

void MTD_FLASHMEM HTTPHandler::dispatch() {
  for (uint32_t i = 0; i != m_routesCount; ++i) {
    if (f_strcmp(FSTR("*"), m_routes[i].page) == 0 ||
        t_strcmp(m_request.requestedPage, CharIterator(m_routes[i].page)) == 0) {
      (this->*m_routes[i].pageHandler)();
      return;
    }
  }
  // not found (routes should always have route "*" to handle 404 not found)
}

void MTD_FLASHMEM HTTPHandler::setRoutes(Route const *routes, uint32_t routesCount) {
  m_routes = routes;
  m_routesCount = routesCount;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPStaticFileResponse

void MTD_FLASHMEM HTTPStaticFileResponse::flush() {
  FlashFileSystem::Item file;
  if (FlashFileSystem::find(m_filename.get(), &file)) {
    // found
    setStatus(STR_200_OK);
    addHeader(STR_Content_Type, file.mimetype);
    addContent(file.data, file.datalength);
  } else {
    // not found
    setStatus(STR_404_Not_Found);
  }
  HTTPResponse::flush();
}

} // fdv namespace
