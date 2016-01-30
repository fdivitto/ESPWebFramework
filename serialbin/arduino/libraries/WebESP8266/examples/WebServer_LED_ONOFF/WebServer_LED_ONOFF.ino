/*
  WebESP8266 Web Server example
  This example demostrates how Arduino can handle HTTP requests from ESP8266
  switching ON/OFF del LED (digital 13).
  
  Just open the page "http://xxx.xxx.xxx.xxx/led"

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

const char str_led[] PROGMEM = "/led";

WebRoute webRoutes[] = {
    {str_led, handle_led},
  };


void setup()
{
  pinMode(13, OUTPUT);
  
  // debug
  //while(1);
  //Serial.begin(9600);
  
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


void handle_led(HTTPRequest const& request, HTTPResponse& response)
{
  if (request.method == HTTPRequest::Post)
  {
    if (strcmp_P(request.form["led"], PSTR("ON")) == 0)
      digitalWrite(13, LOW);
    else
      digitalWrite(13, HIGH);
  }

  /// response ///
  
  response.addContent_P(PSTR("<html><head></head><body>"));  
  response.addContent_P(PSTR("<h1>LED On/Off</h1>"));

  response.addContent_P(PSTR("<form action='/led' method='post'>"));
  char const* ledStateStr = digitalRead(13)? "ON" : "OFF";
  response.addContentFmt_P(PSTR("<button type='submit' name='led' value='%s'>%s</button>"), ledStateStr, ledStateStr);
  response.addContent_P(PSTR("</form>"));

  response.addContent_P(PSTR("</body></html>"));  
}






