@echo off
SET ESP8266SDK=%CD%\..\..\SDK\
PATH=%ESP8266SDK%xtensa-lx106-elf\bin;C:\MinGW\bin;C:\MinGW\msys\1.0\bin;%PATH%
%comspec%
