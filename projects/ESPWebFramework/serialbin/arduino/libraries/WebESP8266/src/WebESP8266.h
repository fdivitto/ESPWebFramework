/*
WebESP8266.h
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

#ifndef WebESP8266_h
#define WebESP8266_h

#include <inttypes.h>
#include <Stream.h>
#include <avr/pgmspace.h>



/******************************************************************************
* Definitions
******************************************************************************/


class HTTPFields
{
public:
    HTTPFields();
    HTTPFields(char const* data, uint8_t itemsCount);
    
    void reset(char const* data, uint8_t itemsCount);
    
    uint8_t itemsCount();
    char const* getkey(uint8_t index);
    char const* operator[](uint8_t index);
    char const* operator[](char const* key);
    
    uint16_t calcBufferSize();
    
private:
    char const* m_data;
    uint8_t     m_itemsCount;
};


struct HTTPRequest
{
    enum Method {Unsupported, Get, Post, Head};
    
    Method      method;
    uint8_t     pageIndex;
    char const* page;
    HTTPFields  headers;
    HTTPFields  query;
    HTTPFields  form;
};


class HTTPResponse
{
public:
    HTTPResponse();
    ~HTTPResponse();
    
    void setStatus(uint8_t status); // one if HTTPSTATUS_xxx constants
    uint8_t getStatus();
    
    void addHeader(PGM_P key, char const* value, bool copy = false);
    void addHeader_P(PGM_P key, PGM_P value);
    
    void addContent(char const* string, bool copy = false);
    void addContent_P(PGM_P string);
    void addContent(void const* data, uint16_t length, bool copy = false);
    void addContent_P(PGM_P data, uint16_t length);
    void addContent(uint32_t value);
    void addContent(float value, int8_t width, uint8_t prec);  // todo: evaluate impact on code size!!
    
    uint8_t calcHeadersFieldsCount();
    uint16_t calcHeadersBufferSize();
    uint8_t* copyHeadersToBuffer(uint8_t* dest);
    
    uint16_t calcContentBufferSize();    
    uint8_t* copyContentToBuffer(uint8_t* dest);
    
public:
    enum Storage {Heap, HeapToFree, Flash};

    struct ContentItem
    {
        ContentItem* next; // NULL = end of list
        Storage      storage;
        void const*  data;
        uint16_t     dataLength;
        ContentItem(ContentItem* next_, Storage storage_, void const* data_, uint16_t dataLength_)
            : next(next_), storage(storage_), data(data_), dataLength(dataLength_)
        {
        }
    };
    
    struct HeaderItem
    {
        HeaderItem* next; // NULL = end of list
        Storage     storage;
        PGM_P       key;
        void const* data;   // aka "value"
        HeaderItem(HeaderItem* next_, Storage storage_, PGM_P key_, void const* data_)
            : next(next_), storage(storage_), key(key_), data(data_)
        {
        }
    };
    
private:
    void addHeaderItem(HeaderItem* item);
    void addContentItem(ContentItem* item);

    ContentItem* m_contentItems;
    HeaderItem*  m_headerItems;
    uint8_t      m_status;
};


typedef void (*WebHandler)(HTTPRequest const& request, HTTPResponse& response);


struct WebRoute
{
    PGM_P      page;
    WebHandler handler;
};


class WebESP8266
{
	
public:

	// platforms
	static uint8_t const PLATFORM_BASELINE     = 0;	// use when platform specific features aren't used
	static uint8_t const PLATFORM_ESP8266      = 1;
	static uint8_t const PLATFORM_ATMEGA328    = 2;
	static uint8_t const PLATFORM_THIS         = PLATFORM_ATMEGA328;

	// pin configuration flags
	static uint8_t const PIN_CONF_OUTPUT       = 0b00000001;	// 0 = input / 1 = output
	static uint8_t const PIN_CONF_PULLUP       = 0b00000010;	// 0 = disabled / 1 = enabled (if supported)		

	// pin identifiers - ESP8266
	static uint8_t const PIN_IDENTIFIER_ESP8266_GPIO0  = 0;
	static uint8_t const PIN_IDENTIFIER_ESP8266_GPIO2  = 2;
	static uint8_t const PIN_IDENTIFIER_ESP8266_GPIO4  = 4;
	static uint8_t const PIN_IDENTIFIER_ESP8266_GPIO5  = 5;
	static uint8_t const PIN_IDENTIFIER_ESP8266_GPIO12 = 12;
	static uint8_t const PIN_IDENTIFIER_ESP8266_GPIO13 = 13;
	static uint8_t const PIN_IDENTIFIER_ESP8266_GPIO14 = 14;
	static uint8_t const PIN_IDENTIFIER_ESP8266_GPIO15 = 15;
	static uint8_t const PIN_IDENTIFIER_ESP8266_GPIO16 = 16;

	// pin identifiers - ATmega328
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB0  = 0;	 // Arduino 8
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB1  = 1;	 // Arduino 9
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB2  = 2;	 // Arduino 10
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB3  = 3;	 // Arduino 11
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB4  = 4;	 // Arduino 12
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB5  = 5;	 // Arduino 13
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC0  = 8;	 // Arduino A0
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC1  = 9;	 // Arduino A1
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC2  = 10; // Arduino A2
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC3  = 11; // Arduino A3
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC4  = 12; // Arduino A4
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC5  = 13; // Arduino A5
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD0  = 16; // Arduino 0
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD1  = 17; // Arduino 1
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD2  = 18; // Arduino 2
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD3  = 19; // Arduino 3
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD4  = 20; // Arduino 4
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD5  = 21; // Arduino 5
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD6  = 22; // Arduino 6
	static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD7  = 23; // Arduino 7	   

    // CMD_HTTPREQUEST - status
    static uint8_t const HTTPSTATUS_200 = 0;    // 200 OK
    static uint8_t const HTTPSTATUS_301 = 1;    // 301 Moved Permanently
    static uint8_t const HTTPSTATUS_302 = 2;    // 302 Found
    static uint8_t const HTTPSTATUS_400 = 3;    // 400 Bad Request
    static uint8_t const HTTPSTATUS_401 = 4;    // 401 Unauthorized
    static uint8_t const HTTPSTATUS_403 = 5;    // 403 Forbidden
    static uint8_t const HTTPSTATUS_404 = 6;    // 404 Not Found

    
    // Types	
    
	struct Message
	{
		bool     valid;
		uint8_t  ID;
		uint8_t  command;
		uint16_t dataSize;
		uint8_t* data;
		
		Message();
		Message(uint8_t ID_, uint8_t command_, uint16_t dataSize_);        
		void freeData(); // warn: memory must be explicitly deleted using freeData(). Don't create a destructor to free data!
	};
    
    
	// Public Methods
    
	WebESP8266();
	void begin(Stream& stream);
    void setupWebRoutes(WebRoute* webRoutes, uint8_t count);
	bool isReady();
	bool checkReady();
	uint8_t getPlatform();
	void yield();
	
	bool send_CMD_READY();
	bool send_CMD_IOCONF(uint8_t pin, uint8_t flags);
	bool send_CMD_IOSET(uint8_t pin, uint8_t state);
	bool send_CMD_IOGET(uint8_t pin, uint8_t* state);
	bool send_CMD_IOASET(uint8_t pin, uint16_t state);
	bool send_CMD_IOAGET(uint8_t pin, uint16_t* state);
	    
private:

	// Private Methods
    
	Message receive();
	int readByte(uint32_t timeOut);
	uint32_t readBuffer(uint8_t* buffer, uint32_t size, uint32_t timeOut);
	void processMessage(Message* msg);
	uint8_t getNextID();
	void send(Message* msg);
	Message waitACK(uint8_t ackID);
	void sendNoParamsACK(uint8_t ackID);
	bool waitNoParamsACK(uint8_t ackID);
    
	void handle_CMD_READY(Message* msg);
	void handle_CMD_IOCONF(Message* msg);
	void handle_CMD_IOSET(Message* msg);
	void handle_CMD_IOGET(Message* msg);
	void handle_CMD_IOASET(Message* msg);
	void handle_CMD_IOAGET(Message* msg);
    void handle_CMD_GETHTTPHANDLEDPAGES(Message* msg);
    void handle_CMD_HTTPREQUEST(Message* msg);
	
private:

    // Private Fields
    
	Stream*   _stream;
	uint8_t   _recvID;
	uint8_t   _sendID;
	bool      _isReady;
	uint8_t   _platform;
    WebRoute* _webRoutes;
    uint8_t   _webRoutesCount;
};





#endif
