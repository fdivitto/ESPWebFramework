# ESPWebFramework
A Web Framework for ESP8266

####To flash compiled binaries
You need:
- Python

Download following files:

- [app.out-0x00000.bin](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/app.out-0x00000.bin)

- [app.out-0x40000.bin](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/app.out-0x40000.bin)

- [webcontent.bin](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/webcontent.bin)

- [esptool.py](https://github.com/fdivitto/ESPWebFramework/raw/master/SDK/esptool.py)

Now run (change COM7 if necessary):
```
   python esptool.py --port COM7 write_flash 0x40000 app.out-0x40000.bin 0x00000 app.out-0x00000.bin 0x17000 webcontent.bin
```

####First configuration
Default configuration creates an Open (without password and not encrypted) WiFi network named "ESPXXXXXXXXXXXX", where XXXXXXXXXXXX is the ESP MAC address. You should connect to this network, having the DHCP of your PC enabled.
Now open the page "http://192.168.4.1" and configure your device.


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

WiFi configuration:
![ss1](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/wificonf.jpg)

WiFi configuration - access points scan:
![ss2](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/wifiscan.jpg)

Network configuration (1/2):
![ss3](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/netconf1.jpg)

Network configuration (2/2):
![ss3](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/netconf2.jpg)

Web server, UART and services configuration:
![ss4](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/confserv.jpg)

Date and Time configuration:
![ss5](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/conftime.jpg)

GPIO configuration and control:
![ss6](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/confgpio.jpg)
