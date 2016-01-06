# ESPWebFramework
A Web Framework for ESP8266

####To flash compiled binaries
You need:
- Python

Download following files:

- [app.out-0x00000.bin](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/app.out-0x00000.bin)

- [app.out-0x11000.bin](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/app.out-0x11000.bin)

- [webcontent.bin](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/webcontent.bin)

- [esptool.py](https://github.com/fdivitto/ESPWebFramework/raw/master/SDK/esptool.py)

Now run (change COM7 if necessary):
```
   python esptool.py --port COM7 write_flash 0x11000 app.out-0x11000.bin 0x00000 app.out-0x00000.bin 0x6C000 webcontent.bin
```

####First configuration
Default configuration creates an Open (without password and not encrypted) WiFi network named "ESPXXXXXXXXXXXX", where XXXXXXXXXXXX is the ESP MAC address. You should connect to this network, having the DHCP of your PC enabled.
Now open the page "http://192.168.4.1" and configure your device.


####GPIO configuration and control using http gets examples

- configure GPIO2 as input
http://192.168.4.1/gpio?cmd=conf&gpio=2&mode=in

- read current value of GPIO2
http://192.168.4.1/gpio?cmd=get&gpio=2

- configure GPIO2 as output
http://192.168.4.1/gpio?cmd=conf&gpio=2&mode=out

- write 1 to GPIO2 (without storing current value into the flash)
http://192.168.4.1/gpio?cmd=set&gpio=2&val=1

- write 0 to GPIO2 (without storing current value into the flash)
http://192.168.4.1/gpio?cmd=set&gpio=2&val=0



####To build from scratch
You need:
- Windows 64 bit
- Python 2.7.9 ( https://www.python.org/downloads/ )
- MinGW ( http://sourceforge.net/projects/mingw/files/latest/download?source=files )

Install Python pyserial and slimmer (to reduce webcontent folder size):
```
easy_install pyserial
easy_install slimmer
```

Move to ESPWebFramework\projects\ESPWebFramework directory and double click on:
```
console.cmd
```

Now run:
```
make
```  
  
Switch ESP8266 to programming mode, then run ((change COM7 if necessary):
```
make flash PORT=COM7
```

####Here is some screenshots:

WiFi configuration (Client Mode):
![ss1](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/wificonf2.jpg)

WiFi configuration (Access Point):
![ss2](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/wificonf1.jpg)

Network configuration:
![ss3](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/netconf.jpg)

Web server, UART and services configuration:
![ss4](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/confserv.jpg)

Date and Time configuration:
![ss5](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/conftime.jpg)

GPIO configuration and control:
![ss6](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/confgpio.jpg)

Setup Wizard (first page):
![ss6](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/wizard.jpg)
