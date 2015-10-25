/*
  WebESP8266 Web Server example
  This example demostrates how Arduino can handle HTTP requests from ESP8266

  Set ESP8266 UART speed to 9600 using web interface.
  
  This example code is in the public domain.

 */

#include <WebESP8266.h>
#include <SoftwareSerial.h>


// 10 = RX   -> to TX of ESP8266
// 11 = TX   -> to RX of ESP8266 (remember to shift levels from 5.0v to 3.3v!)
SoftwareSerial softSerial(10, 11);

// the WebESP8266 communication object
WebESP8266 webESP; 

const char page0[] PROGMEM = "/page0";
const char page1[] PROGMEM = "/page1";
const char page2[] PROGMEM = "/page2";

WebRoute webRoutes[] = {
    {page0, handle_page0},
    {page1, handle_page1},
    {page2, handle_page2},
  };


void setup()
{
  // debug
  //while(1);
  Serial.begin(9600);
  
  // setup software serial baud rate
  softSerial.begin(9600);
  
  // setup handled web pages
  webESP.setupWebRoutes(webRoutes, sizeof(webRoutes) / sizeof(WebRoute));
  
  // setup WebESP8266 stream object (in this case it is a soft serial)
  webESP.begin(softSerial);  
}


void loop()
{
  webESP.yield();
}


void handle_page0(HTTPRequest const& request, HTTPResponse& response)
{
  Serial.println("handle_page0");
  response.addContent_P(PSTR("Hello World-0!!"));
}


void handle_page1(HTTPRequest const& request, HTTPResponse& response)
{
  Serial.println("handle_page1");
  response.addContent_P(PSTR("Hello World-1!!"));
}


void handle_page2(HTTPRequest const& request, HTTPResponse& response)
{
  Serial.println("handle_page2");
  response.addContent_P(PSTR("Hello World-2!!"));
}

