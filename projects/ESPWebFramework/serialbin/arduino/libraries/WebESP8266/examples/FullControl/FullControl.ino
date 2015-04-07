/*
  WebESP8266 full control example

  Set ESP8266 UART speed to 9600 using web interface.
  
  This example code is in the public domain.

 */

#include <WebESP8266.h>
#include <SoftwareSerial.h>


// 10 = RX
// 11 = TX
SoftwareSerial softSerial(10, 11);

// the WebESP8266 communication object
WebESP8266 webESP; 

void setup()
{
  // setup software serial baud rate
  softSerial.begin(9600);
  
  // setup hardware serial baud rate (debug only)
  Serial.begin(9600);
  
  Serial.println("begin..");
  
  // setup WebESP8266 stream object (in this case it is a soft serial)
  webESP.begin(softSerial);
  
  Serial.println("loop..");
}


void loop()
{
  webESP.yield();
  if (webESP.isReady())
  {
    Serial.println("ready!");
    Serial.print("plat="); Serial.println(webESP.getPlatform());
    while(1);
  }
}

