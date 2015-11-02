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


// You can try: "http://192.168.1.99/page0?key1=value1&key2=value2" 
// Where "192.168.1.99" is the address of ESP8266 and of course change it!
void handle_page0(HTTPRequest const& request, HTTPResponse& response)
{
  response.addContent_P(PSTR("<html><head></head><body>"));  
  response.addContent_P(PSTR("<h1>This is page ZERO from Arduino!</h1>"));

  response.addContent_P(PSTR("<h2>Query fields<h2>"));
  response.addContent_P(PSTR("<table style='width:100%' border='1'>"));
  for (uint8_t i = 0; i != request.query.itemsCount(); ++i)
    response.addContentFmt_P(PSTR("<tr><td>%s</td><td>%s</td></tr>"), request.query.getkey(i), request.query[i]);
  response.addContent_P(PSTR("</table>"));

  response.addContent_P(PSTR("</body></html>"));  
}


void handle_page1(HTTPRequest const& request, HTTPResponse& response)
{
  response.addContent_P(PSTR("This is page ONE from Arduino!"));
}


void handle_page2(HTTPRequest const& request, HTTPResponse& response)
{
  response.addContent_P(PSTR("This is page TWO from Arduino!"));
}




