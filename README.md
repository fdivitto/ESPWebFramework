# ESPWebFramework
A C++ Web Framework for ESP8266

To compile requires:
- Windows 64 bit
- Python 2.7.9 ( https://www.python.org/downloads/ )
- MinGW ( http://sourceforge.net/projects/mingw/files/latest/download?source=files )

Install Python pyserial and slimmer (to reduce webcontent folder size):

- easy_install pyserial
- easy_install slimmer

Move to ESPWebFramework\projects\ESPWebFramework directory and double click on:

- console.cmd

Now run:

- make
  
Swith ESP8266 to programming mode. Make sure you set right COM port into Makefile (default is COM3), then run:

- make flash
