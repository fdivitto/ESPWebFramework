@echo off  

SET ESP8266SDK=%CD%\..\..\SDK\
PATH=%ESP8266SDK%xtensa-lx106-elf\bin;C:\MinGW\bin;C:\MinGW\msys\1.0\bin;%PATH%

rm -f *.dump
rm -f *.hex

python ..\..\SDK\esptool.py --port COM7 read_flash 0x0000 0x80000 flash.dump
xxd flash.dump > flash.hex
