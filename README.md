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

####Wiki links:

https://github.com/fdivitto/ESPWebFramework/wiki/First-configuration
https://github.com/fdivitto/ESPWebFramework/wiki/GPIO-configuration-and-control-using-http-GETs
https://github.com/fdivitto/ESPWebFramework/wiki/How-build-from-scratch
https://github.com/fdivitto/ESPWebFramework/wiki/How-flash-compiled-binaries
https://github.com/fdivitto/ESPWebFramework/wiki/Some-screenshots
