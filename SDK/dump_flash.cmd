@echo off  
PATH=C:\ESP8266\xtensa-lx106-elf\bin;C:\MinGW\bin;C:\MinGW\msys\1.0\bin;%PATH%

python esptool.py --port COM3 read_flash 0x0000 0x80000 flash.dump
xxd flash.dump > flash.hex
