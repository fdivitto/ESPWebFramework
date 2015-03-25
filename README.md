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
  
Switch ESP8266 to programming mode. Make sure you set right COM port into Makefile (default is COM7), then run:
```
make flash
```

####Here is some screenshots:

WiFi configuration:
![ss1](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/ss1.jpg)

WiFi configuration - access points scan:
![ss2](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/ss2.jpg)

Network configuration:
![ss3](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/ss3.jpg)

Web server, UART and services configuration:
![ss4](https://github.com/fdivitto/ESPWebFramework/raw/master/projects/ESPWebFramework/docs/images/ss4.jpg)
