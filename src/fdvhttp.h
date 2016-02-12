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

#ifndef _FDVHTTP_H_
#define _FDVHTTP_H_

#include "fdv.h"


namespace fdv {


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPHandler

class HTTPHandler : public TCPConnectionHandler {

  static uint32_t const CHUNK_CAPACITY = 32;
  static uint32_t const TIMEOUT = 3000;

public:
  typedef IterDict<CharChunksIterator, CharChunksIterator> Fields;

  enum Method {
    Unsupported,
    Get,
    Post,
    Head,
  };

  struct Request {
    Method method;                    // ex: GET, POST, etc...
    CharChunksIterator requestedPage; // ex: "/", "/data"...
    Fields query;                     // parsed query as key->value dictionary
    Fields headers;                   // parsed headers as key->value dictionary
    Fields form;                      // parsed form fields as key->value dictionary
  };

  typedef void (HTTPHandler::*PageHandler)();

  struct Route {
    char const *page;
    PageHandler pageHandler;
  };

private:
  // implements TCPConnectionHandler
  void connectionHandler();

  bool processRequest();

  void processXWWWFormUrlEncoded(CharChunksIterator headerEnd, int32_t contentLength);
  void processMultipartFormData(CharChunksIterator headerEnd, int32_t contentLength, char const *contentType);

  CharChunksIterator extractURLEncodedFields(CharChunksIterator begin, CharChunksIterator end, Fields *fields);
  CharChunksIterator extractHeaders(CharChunksIterator begin, CharChunksIterator end, Fields *fields);

public:
  void setRoutes(Route const *routes, uint32_t routesCount);

  // valid only inside processRequest()
  Request &getRequest() { return m_request; }

  virtual void dispatch();

private:
  LinkedCharChunks m_receivedData;
  Route const *m_routes;
  uint32_t m_routesCount;
  Request m_request; // valid only inside processRequest()
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPResponse

class HTTPResponse {
public:
  typedef IterDict<CharIterator, CharIterator> Fields;

  HTTPResponse(HTTPHandler *httpHandler, char const *status, char const *content = NULL);

  HTTPHandler *getHttpHandler() { return m_httpHandler; }

  HTTPHandler::Request &getRequest();

  void setStatus(char const *status) { m_status = status; }

  // accept RAM or Flash strings
  void addHeader(char const *key, char const *value);

  // accept RAM or Flash data
  void addContent(void const *data, uint32_t length, bool freeOnDestroy = false);

  // accept RAM or Flash strings
  // can be called many times
  void addContent(char const *str, bool freeOnDestroy = false);

  // can be called many times
  // WARN: src content is not copied! Just data pointers are stored
  void addContent(LinkedCharChunks *src);

  // should be called only after setStatus, addHeader
  virtual void flushHeaders(uint32_t contentLength);

  // should be called only after setStatus, addHeader and addContent
  // If not already called, this calls also flushHeaders()
  virtual void flush();

private:
  HTTPHandler *m_httpHandler;
  char const *m_status;
  Fields m_headers;
  LinkedCharChunks m_content;
  bool m_headersFlushed;
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPStaticFileResponse

struct HTTPStaticFileResponse : public HTTPResponse {
  template <typename Iterator>
  HTTPStaticFileResponse(HTTPHandler *httpHandler, Iterator filename)
      : HTTPResponse(httpHandler, NULL) {
    if (*filename == '/')
      ++filename;
    m_filename.reset(t_strdup(filename));
  }

  virtual void flush();

private:
  APtr<char> m_filename;
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// ParameterReplacer
// If input contains {%..%} blocks only getBlocks() should be used
// If input contains only {{}} tags only getResult() should be used.

struct ParameterReplacer {
  typedef ObjectDict<LinkedCharChunks> Params;
  typedef ObjectDict<LinkedCharChunks *> BlockParams;

  ParameterReplacer();
  ~ParameterReplacer();

  void start(char const *strStart, char const *strEnd, Params *params, BlockParams *blockParams);

  LinkedCharChunks *getResult() { return m_results[0]; }

  ObjectDict<LinkedCharChunks *> *getBlocks() { return &m_blocks; }

  char const *getTemplateFilename() { return m_template.get(); }

private:
  void processInput();
  char const *replaceTag(char const *curc);
  char const *extractTagStr(char const *curc, char const **tagEnd);

private:
  Params *m_params;
  BlockParams *m_blockParams;
  char const *m_strStart;
  char const *m_strEnd;
  Vector<LinkedCharChunks *> m_results;
  ObjectDict<LinkedCharChunks *> m_blocks;
  APtr<char> m_template; // template file name (filled with the first {%...%} block)
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPTemplateResponse
//
// Parameters are tagged with:
//   {{parameter_name}}
// example:
//   {{something}}
// Parameters cannot stay in template file.
//
// Parameters can be indicized using # before the name. Example:
//   {{#param}}
// Now all parameters like 0param, 1param, 2param, etc.. will be replaced in palce of "#param".
//
// A template can only contain {{}} tags, which specify the blocks or parameters to replace. Example:
// Content of file "base.html":
//   <html>
//   <head> {{the_head}} </head>
//   <body> {{the_body}} </body>
//   </html>
//
// Specialized file can replace template blocks using {%block_name%}. Example:
// Content of file "home.html":
//   {%base.html%}                 <- first block specifies the tamplate filename
//   {%the_head%}                  <- start of "the_head" block
//   <title>Home Page</title>
//   {%the_body%}                  <- start of "the_body" block
//   <h1>Hello {{name}}</h1>       <- here the parameter "name" will be replaced with its actual value
//
// Specialized file must contain at least one {%%} tag, and may or may not contain {{}} tags (parameters).
// Parameter tags and block tags must have different names.
// The template file can contain parameters that will be replaced as they was in the specialized file.
//
// No further spaces are allowed inside {{}} and {%%} tags
// No syntax error checkings are done, so be careful!
// Only one level of inheritance is allowed (specialized file -> template file)

struct HTTPTemplateResponse : public HTTPResponse {
  typedef ObjectDict<LinkedCharChunks> Params;

  HTTPTemplateResponse(HTTPHandler *httpHandler, char const *filename);

  void setFilename(char const *filename) { m_filename = filename; }

  void addParamStr(char const *key, char const *value);
  void addParamInt(char const *key, int32_t value);
  void addParamFmt(char const *key, char const *fmt, ...);
  LinkedCharChunks *addParamCharChunks(char const *key);

  Params *getParams();

  virtual void flush();

private:
  void processFileRequest();

private:
  char const *m_filename;
  Params m_params;
  ParameterReplacer m_replacer;
  ParameterReplacer m_templateReplacer;
};


} // fdv namespace

#endif	// _FDVHTTP_H_
