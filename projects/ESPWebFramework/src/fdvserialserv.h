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

#ifndef _FDVSERIALSRV_H_
#define _FDVSERIALSRV_H_

#include "fdv.h"


namespace fdv
{
	
	
	enum SerialService
	{
		SerialService_None = 0,
		SerialService_Console,
		SerialService_BinaryProtocol,		
	};
	
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	// SerialConsole
	
#if (FDV_INCLUDE_SERIALCONSOLE == 1)
	
	class SerialConsole : public Task
	{
        
    public:
    
		SerialConsole()
			: Task(false, 300)
		{
		}

		// destructor must be called outside This task
		~SerialConsole()
		{
			terminate();
		}
        
    private:
		
        static uint32_t const MAX_PARAMETERS = 6;	// including command name
        
		void exec();		
		void separateParameters();				
		void routeCommand();
        bool hasParameter(uint32_t paramIndex, char const* str);
		
        
    public:
    
		void cmd_help();
		void cmd_reboot();		
		void cmd_restore();		
		void cmd_free();		
        void cmd_ifconfig();
        void cmd_iwconfig();
		void cmd_iwlist();
        void cmd_date();        
        void cmd_ntpdate();
		void cmd_nslookup();        
        void cmd_uptime();
        void cmd_ping();
        void cmd_router();
        void cmd_ls();
        void cmd_rm();
        void cmd_cat();
		void cmd_test();		        
		
	private:
		Serial*                 m_serial;
		LinkedCharChunks        m_receivedChunks;
		uint32_t                m_paramsCount;
		CharChunksIterator      m_params[MAX_PARAMETERS];
        DateTime                m_bootTime; // actually SerialConsole uptime!
	};
	
#endif	// FDV_INCLUDE_SERIALCONSOLE



#if (FDV_INCLUDE_SERIALBINARY == 1)

	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	// SerialBinary
	//
	// This binary protocol is bidirectional and equivalent on both sides, there no masters and no slaves. Each part can initiate communication.
	// Data is enclosed in messages. A message contains an id, a command and optional parameters.
	// Receiver replies to commands with an ACK message, which can include optional parameters.
	// Sender must wait up to 2000ms for an ACK message. In case no ACK is received it must resend the message with the same ID for 3 times.
	// Receiver must ignore a message with the same ID of the previous one.
	// Each part should begin sending (or receive) a CMD_READY message before other messages.
	// All values are little-endian
	// Each part should handle the case when it expects an ACK but a command arrives. In this case receiver should process the command before, and then wait again for the ACK.
	// Each part must have the same protocol version.
	//
	// Example 1. How switch Arduino LED (pin13) on/off. Arduino with "FullControl" example sketch.
	// SerialBinary* sb = ConfigurationManager::getSerialBinary();	
	// while (true)
	// {
	//   if (!sb->isReady() && sb->checkReady())
	//   {
	//     // Link just established. Set pin 13 as Output.
	//     sb->send_CMD_IOCONF(13, SerialBinary::PIN_CONF_OUTPUT);
	//   }
	//   if (sb->isReady())
	//   {
	//     sb->send_CMD_IOSET(13, true);
	//     Task::delay(500);
	//     sb->send_CMD_IOSET(13, false);
	//     Task::delay(500);
	//   }
	// }
	//
	//
	// Message structure:
	//   1 uint8_t  : Incremental ID. Each part maintain an incremental ID, which identifies a message. Replies include the same ID.
	//   1 uint8_t  : Command
	//   1 uint16_t : Data size.  This is 0x0000 if there isn't data. 
    //   for n times [
	//     1 uint8_t  : Optional command parameters (See CMD Parameters below)
    //   ]
	//
	// Commands:
	//
	//   CMD_ACK
	//     Description:
	//       Acknowledge of a message
	//     Parameters:
	//       1 uint8_t : ID of acknowledged message (different than this ACK message ID!)
	//       ? uint8_t : Optional ACK parameters (See ACK Parameters below)
    //
	//   CMD_READY
	//     Description:
	//        Communicates this device is ready
	//     CMD Parameters:
	//       1  uint8_t : Protocol version
	//       1  uint8_t : Platform (see PLATFORM_XXX values)
	//       10 uint8_t : Magic string "BINPRORDY\x00"
	//     ACK Parameters:
	//       1  uint8_t : Protocol version
	//       1  uint8_t : Platform (see PLATFORM_XXX values)
	//       10 uint8_t : Magic string "BINPRORDY\x00"
	//
	//   CMD_IOCONF
	//     Description:
	//       Configure input/output pins
	//     CMD Parameters:
	//       1  uint8_t : Pin identifier (see PIN_IDENTIFIER_XX values)
	//       1  uint8_t : Flags (see PIN_CONF_XXX values)
	//     ACK Parameters:
	//       none
	//
	//   CMD_IOSET
	//     Description:
	//       Set output state of digital pin (low/high)
	//     CMD Parameters:
	//       1  uint8_t : Pin identifier (see PIN_IDENTIFIER_XX values)
	//       1  uint8_t : Output state (0 = low, 1 = high)
	//     ACK Parameters:
	//        none
	//
	//   CMD_IOGET
	//     Description:
	//       Get input state of digital pin (low/high)
	//     CMD Parameters:
	//       1  uint8_t : Pin identifier (see PIN_IDENTIFIER_XX values)
	//     ACK Parameters:
	//       1  uint8_t : Input state (0 = low, 1 = high)  
	//
	//   CMD_IOASET
	//     Description:
	//       Set output state of analog pin (0..1023, as PWM output)
	//     CMD Parameters:
	//       1  uint8_t  : Pin identifier (see PIN_IDENTIFIER_XX values)
	//       1  uint16_t : Output state (0..1023)
	//     ACK Parameters:
	//        none
	//
	//   CMD_IOAGET
	//     Description:
	//       Get input state of analog pin (0..1023)
	//     CMD Parameters:
	//       1  uint8_t  : Pin identifier (see PIN_IDENTIFIER_XX values)
	//     ACK Parameters:
	//       1  uint16_t : Input state (0..1023)
    //
    //   CMD_GETHTTPHANDLEDPAGES
    //     Description:
    //       Requests for the list of HTTP handled pages
    //     CMD Parameters:
    //       none
    //     ACK Parameters:
    //       1 uint8_t : Number of pages in the list (max 255)
    //       for n times [
    //         ? char : Page (zero terminated string)
    //       ]
    //
    //   CMD_HTTPREQUEST
    //     Description:
    //       Request a page
    //       The ACK may be composed by a standard message plus a content of unknown size terminated by 0x00.
    //     CMD Parameters:
    //       1 uint8_t : Method (see HTTPSENDMETHOD_xxx constants)
    //       1 uint8_t : Page index (registered using CMD_GETHTTPHANDLEDPAGES)
    //       ? char    : Page (zero terminated string) (i.e. "/", "/data")
    //       1 uint8_t : Number of headers fields
    //       for n times [
    //         ? char : Header field key (zero terminated string)
    //         ? char : Header field value (zero terminated string)
    //       ]    
    //       1 uint8_t : Number of query fields (/page?field1=xx&field2=yy, has two fields "field1" and "field2")
    //       for n times [
    //         ? char : Query field key (zero terminated string)
    //         ? char : Query field value (zero terminated string)
    //       ]
    //       1 uint8_t : Number of form fields
    //       for n times [
    //         ? char : Form field key (zero terminated string)
    //         ? char : Form field value (zero terminated string)
    //       ]
    //     ACK Parameters:
    //       1 uint8_t : Status (see HTTPSTATUS_xxx constants)
    //       1 uint8_t : Number of headers fields
    //       for n times [
    //         ? char : Header field key (zero terminated string)
    //         ? char : Header field value (zero terminated string)
    //       ]
    //       1 uint8_t  : Content type header (see HTTPCONTENTTYPE_xxx constants)
    //       1 uint8_t  : Content delivery mode
    //                       0 = Embedded in the ACK message: will follow a content length field plus 
    //                           actual content data.
    //                       1 = Not embedded in the ACK, known size: will follow a content length field. 
    //                           Actual data will follow but not embedded in the ACK message.
    //                       2 = Not embedded in the ACK, unknown size: will follow only actual content
    //                           data with a terminating 0x00.
    //       [1 uint16_t] : Optional content length 
    //       for n or unknown times [
    //         ? uint8_t  : Content. May or not may be embedded in the ACK message
    //       ]
    //
    //   CMD_STREAMSTART
    //     Description:
    //       This is a special message that prefix a free stream of data (used for example by the ACK of CMD_HTTPREQUEST)
    //     Parameters:
    //       none
    //     ACK Parameters:
    //       none
    
	
	class SerialBinary
	{

		static uint8_t const  PROTOCOL_VERSION     = 1;
	
		static uint32_t const INTRA_MSG_TIMEOUT    = 200;
		static uint32_t const WAIT_MSG_TIMEOUT     = 2000;
		static uint32_t const PUTACK_TIMEOUT       = 200;
		static uint32_t const GETACK_TIMEOUT       = 2000;
		static uint32_t const ACKMSG_QUEUE_LENGTH  = 2;
		static uint32_t const MAX_RESEND_COUNT     = 3;
		
		// commands
		static uint8_t const CMD_ACK                 = 0;
		static uint8_t const CMD_READY               = 1;
		static uint8_t const CMD_IOCONF              = 2;
		static uint8_t const CMD_IOSET               = 3;
		static uint8_t const CMD_IOGET               = 4;
		static uint8_t const CMD_IOASET              = 5;
		static uint8_t const CMD_IOAGET              = 6;
        static uint8_t const CMD_GETHTTPHANDLEDPAGES = 7;
        static uint8_t const CMD_HTTPREQUEST         = 8;
        static uint8_t const CMD_STREAMSTART         = 9;
		
        // CMD_HTTPREQUEST - method
        static uint8_t const HTTPSENDMETHOD_UNSUPPORTED = 0;
        static uint8_t const HTTPSENDMETHOD_GET         = 1;
        static uint8_t const HTTPSENDMETHOD_POST        = 2;
        static uint8_t const HTTPSENDMETHOD_HEAD        = 3;
        
        // CMD_HTTPREQUEST - status
        static uint8_t const HTTPSTATUS_200 = 0;    // 200 OK
        static uint8_t const HTTPSTATUS_301 = 1;    // 301 Moved Permanently
        static uint8_t const HTTPSTATUS_302 = 2;    // 302 Found
        static uint8_t const HTTPSTATUS_400 = 3;    // 400 Bad Request
        static uint8_t const HTTPSTATUS_401 = 4;    // 401 Unauthorized
        static uint8_t const HTTPSTATUS_403 = 5;    // 403 Forbidden
        static uint8_t const HTTPSTATUS_404 = 6;    // 404 Not Found

        // CMD_HTTPREQUEST - preset content types
        static uint8_t const HTTPCONTENTTYPE_UNSPECIFIED   = 0;  // header not added. User can still add content-type using addHeader methods.
        static uint8_t const HTTPCONTENTTYPE_TEXTHTML      = 1;  // text/html (DEFAULT)
        static uint8_t const HTTPCONTENTTYPE_TEXTHTML_UTF8 = 2;  // text/html; charset=utf-8
        static uint8_t const HTTPCONTENTTYPE_APPJSON       = 3;  // application/json
        static uint8_t const HTTPCONTENTTYPE_TEXTPLAIN     = 4;  // text/plain
        static uint8_t const HTTPCONTENTTYPE_TEXTXML       = 5;  // text/xml
        
        
        
	public:
		
		// platforms		
		static uint8_t const PLATFORM_BASELINE     = 0;	// use when platform specific features aren't used
		static uint8_t const PLATFORM_ESP8266      = 1;
		static uint8_t const PLATFORM_ATMEGA328    = 2;		
		static uint8_t const PLATFORM_THIS         = PLATFORM_ESP8266;

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
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB0  = 8;	 // Arduino 8
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB1  = 9;	 // Arduino 9
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB2  = 10; // Arduino 10
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB3  = 11; // Arduino 11
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB4  = 12; // Arduino 12
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PB5  = 13; // Arduino 13
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC0  = 14; // Arduino A0
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC1  = 15; // Arduino A1
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC2  = 16; // Arduino A2
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC3  = 17; // Arduino A3
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC4  = 18; // Arduino A4
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PC5  = 19; // Arduino A5
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD0  = 0;  // Arduino 0
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD1  = 1;  // Arduino 1
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD2  = 2;  // Arduino 2
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD3  = 3;  // Arduino 3
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD4  = 4;  // Arduino 4
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD5  = 5;  // Arduino 5
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD6  = 6;  // Arduino 6
		static uint8_t const PIN_IDENTIFIER_ATMEGA328_PD7  = 7;  // Arduino 7
                
		
		struct Message
		{
			bool     valid;
			uint8_t  ID;
			uint8_t  command;
			uint16_t dataSize;
			uint8_t* data;
			
			Message();
			Message(uint8_t ID_, uint8_t command_, uint16_t dataSize_);
            Message(uint8_t ID_, uint8_t command_, uint8_t* data_, uint16_t dataSize_);
			void MTD_FLASHMEM freeData(); // warn: memory must be explicitly deleted using freeData(). Don't create a destructor to free data!
		};	

		
	public:
	
		SerialBinary();        		
		~SerialBinary();	

        // high level interface
		bool isReady();		
		bool checkReady();				
		uint8_t getPlatform();
        StringList* getHTTPRoutes();
								
        // low level interface
		bool send_CMD_READY();		
		bool send_CMD_IOCONF(uint8_t pin, uint8_t flags);
		bool send_CMD_IOSET(uint8_t pin, uint8_t state);
		bool send_CMD_IOGET(uint8_t pin, uint8_t* state);
		bool send_CMD_IOASET(uint8_t pin, uint16_t state);
		bool send_CMD_IOAGET(uint8_t pin, uint16_t* state);
        bool send_CMD_GETHTTPHANDLEDPAGES();
        bool send_CMD_HTTPREQUEST(uint8_t pageIndex, HTTPHandler* handler);
		
	private:
						
		Message receive();
		uint8_t getNextID();		
		void send(Message const& msg);		
		void sendNoParamsACK(uint8_t ackID);				
		Message waitACK(uint8_t ackID);		
		bool waitNoParamsACK(uint8_t ackID);
		void receiveTask();						
		void processMessage(Message* msg);		
		
		void handle_CMD_READY(Message* msg);		
		void handle_CMD_IOCONF(Message* msg);		
		void handle_CMD_IOSET(Message* msg);		
		void handle_CMD_IOGET(Message* msg);
		void handle_CMD_IOASET(Message* msg);
		void handle_CMD_IOAGET(Message* msg);
        void handle_CMD_STREAMSTART(Message* msg);

     private:
    
		Serial*                                              m_serial;
		uint8_t                                              m_recvID;		
		uint8_t                                              m_sendID;
		Queue<Message>                                       m_recvACKQueue;
		MethodTask<SerialBinary, &SerialBinary::receiveTask> m_receiveTask;
		Mutex                                                m_mutex;    // low level mutex
        Mutex                                                m_himutex;  // high level mutex
		bool                                                 m_isReady;
		uint8_t                                              m_platform;
        StringList*                                          m_HTTPRoutes;
	};

#endif // FDV_INCLUDE_SERIALBINARY
	
}

#endif

