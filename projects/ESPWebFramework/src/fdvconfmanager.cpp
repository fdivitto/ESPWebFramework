/*
# Created by Fabrizio Di Vittorio (fdivitto2013@gmail.com)
# Copyright (c) 2015 Fabrizio Di Vittorio.
# All rights reserved.

# GNU GPL LICENSE
#
# This module is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; latest version thereof,
# available at: <http://www.gnu.org/licenses/gpl.txt>.
#
# This module is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this module; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*/




#include "fdv.h"





namespace fdv
{

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// ConfigurationManager


#if (FDV_INCLUDE_SERIALCONSOLE == 1)
    SerialConsole* ConfigurationManager::s_serialConsole = NULL;
#endif

#if (FDV_INCLUDE_SERIALBINARY == 1)
    SerialBinary*  ConfigurationManager::s_serialBinary  = NULL;
#endif

	
    
    // can be re-applied
    void STC_FLASHMEM ConfigurationManager::applyUARTServices()
    {            
        // UART and serial services
        uint32_t baudRate;
        bool enableSystemOutput;
        SerialService serialService;
        getUARTParams(&baudRate, &enableSystemOutput, &serialService);
        HardwareSerial::getSerial(0)->reconfig(baudRate);
        if (!enableSystemOutput)
            DisableStdOut();
#if (FDV_INCLUDE_SERIALCONSOLE == 1)
        if (s_serialConsole)
        {
            delete s_serialConsole;
            s_serialConsole = NULL;
        }
#endif
#if (FDV_INCLUDE_SERIALBINARY == 1)
        if (s_serialBinary)
        {
            delete s_serialBinary;
            s_serialBinary = NULL;
        }
#endif
        switch (serialService)
        {
#if (FDV_INCLUDE_SERIALCONSOLE == 1)
            case SerialService_Console:
                s_serialConsole = new SerialConsole;
                break;
#endif
#if (FDV_INCLUDE_SERIALBINARY == 1)
            case SerialService_BinaryProtocol:
                s_serialBinary = new SerialBinary;
                break;
#endif
        }            
    }
    
    
    // can be re-applied
    void STC_FLASHMEM ConfigurationManager::applyWiFi()
    {
        // WiFi Mode
        WiFi::setMode(getWiFiMode());
                                    
        if (getWiFiMode() == WiFi::AccessPoint || getWiFiMode() == WiFi::ClientAndAccessPoint)
        {
            // Access point parameters
            char const* SSID;
            char const* securityKey;
            uint8_t channel;
            WiFi::SecurityProtocol securityProtocol;
            bool hiddenSSID;
            getAccessPointParams(&SSID, &securityKey, &channel, &securityProtocol, &hiddenSSID);
            WiFi::configureAccessPoint(SSID, securityKey, channel, securityProtocol, hiddenSSID);
        }
        
        if (getWiFiMode() == WiFi::Client || getWiFiMode() == WiFi::ClientAndAccessPoint)
        {			
            // Client parameters
            char const* SSID;
            char const* securityKey;
            getClientParams(&SSID, &securityKey);
            WiFi::configureClient(SSID, securityKey);
        }
    }
    
    
    // can be re-applied
    // doesn't support GPIO16
    void STC_FLASHMEM ConfigurationManager::applyGPIO()
    {
        // GPIO
        for (uint32_t i = 0; i < 17; ++i)
        {
            bool configured, isOutput, pullUp, value;
            getGPIOParams(i, &configured, &isOutput, &pullUp, &value);
            if (configured)
            {
                // GPIO0..15
                GPIO gpio(i);
                if (isOutput)
                    gpio.modeOutput();
                else
                    gpio.modeInput();
                gpio.enablePullUp(pullUp);
                if (isOutput)
                    gpio.write(value);
            }
        }
    }		
    

    // can be re-applied
    void STC_FLASHMEM ConfigurationManager::applyAccessPointIP()
    {
        if (getWiFiMode() == WiFi::AccessPoint || getWiFiMode() == WiFi::ClientAndAccessPoint)
        {
            // Access Point IP
            char const* IP;
            char const* netmask;
            char const* gateway;
            getAccessPointIPParams(&IP, &netmask, &gateway);
            IP::configureStatic(WiFi::AccessPointNetwork, IP, netmask, gateway);
        }
    }			
    
    
    // can be re-applied
    void STC_FLASHMEM ConfigurationManager::applyClientIP()
    {
        if (getWiFiMode() == WiFi::Client || getWiFiMode() == WiFi::ClientAndAccessPoint)
        {			
            // Client IP
            bool staticIP;
            char const* IP;
            char const* netmask;
            char const* gateway;
            getClientIPParams(&staticIP, &IP, &netmask, &gateway);
            if (staticIP)
                IP::configureStatic(WiFi::ClientNetwork, IP, netmask, gateway);
            else
                IP::configureDHCP(WiFi::ClientNetwork);
        }
    }			

        
    // can be re-applied
    void STC_FLASHMEM ConfigurationManager::applyDHCPServer()
    {
        // DCHP Server
        if (getWiFiMode() == WiFi::AccessPoint || getWiFiMode() == WiFi::ClientAndAccessPoint)
        {
            bool enabled;
            char const* startIP;
            char const* endIP;
            getDHCPServerParams(&enabled, &startIP, &endIP);
            if (enabled)
                DHCPServer::configure(startIP, endIP);
        }
    }
    
    
    void STC_FLASHMEM ConfigurationManager::applyDNS()
    {
        IPAddress DNS1, DNS2;
        getDNSParams(&DNS1, &DNS2);
        NSLookup::setDNSServer(0, DNS1);
        NSLookup::setDNSServer(1, DNS2);
    }
    
    
    void STC_FLASHMEM ConfigurationManager::applyRouting()
    {
        bool routing;
        getRouting(&routing);
        if (routing)
            Router::enable();
        else
            Router::disable();
    }
        
    
    // can be re-applied
    void STC_FLASHMEM ConfigurationManager::applyDateTime()
    {
        int8_t timezoneHours;
        uint8_t timezoneMinutes;
        char const* defaultNTPServer;
        getDateTimeParams(&timezoneHours, &timezoneMinutes, &defaultNTPServer);
        DateTime::setDefaults(timezoneHours, timezoneMinutes, defaultNTPServer);
        DateTime().now();   // force NTP server sync
    }

    
    void STC_FLASHMEM ConfigurationManager::restore()
    {
        FlashDictionary::eraseContent();
        system_restore();
    }
        
    
    void STC_FLASHMEM ConfigurationManager::setWiFiMode(WiFi::Mode value)
    {
        FlashDictionary::setInt(STR_WiFiMode, (int32_t)value);
    }
    
    
    WiFi::Mode STC_FLASHMEM ConfigurationManager::getWiFiMode()
    {
        return (WiFi::Mode)FlashDictionary::getInt(STR_WiFiMode, (int32_t)WiFi::AccessPoint);
    }
    
    
    void STC_FLASHMEM ConfigurationManager::setAccessPointParams(char const* SSID, char const* securityKey, uint8_t channel, WiFi::SecurityProtocol securityProtocol, bool hiddenSSID)
    {
        FlashDictionary::setString(STR_APSSID, SSID);
        FlashDictionary::setString(STR_APSECKEY, securityKey);
        FlashDictionary::setInt(STR_APCH, channel);
        FlashDictionary::setInt(STR_APSP, (int32_t)securityProtocol);
        FlashDictionary::setBool(STR_APHSSID, hiddenSSID);
    }
    
    
    void STC_FLASHMEM ConfigurationManager::getAccessPointParams(char const** SSID, char const** securityKey, uint8_t* channel, WiFi::SecurityProtocol* securityProtocol, bool* hiddenSSID)
    {
        static char defaultSSID[10];
        uint8_t mac[16];
        WiFi::getMACAddress(WiFi::AccessPointNetwork, mac);			
        sprintf(defaultSSID, FSTR("ESP%02X%02X%02X%02X%02X%02X"), mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        *SSID             = FlashDictionary::getString(STR_APSSID, defaultSSID);
        *securityKey      = FlashDictionary::getString(STR_APSECKEY, STR_);
        *channel          = FlashDictionary::getInt(STR_APCH, 9);
        *securityProtocol = (WiFi::SecurityProtocol)FlashDictionary::getInt(STR_APSP, (int32_t)WiFi::Open);
        *hiddenSSID       = FlashDictionary::getBool(STR_APHSSID, false);
    }
    
    
    void STC_FLASHMEM ConfigurationManager::setClientParams(char const* SSID, char const* securityKey)
    {
        FlashDictionary::setString(STR_CLSSID, SSID);
        FlashDictionary::setString(STR_CLSECKEY, securityKey);
    }
    
    
    void STC_FLASHMEM ConfigurationManager::getClientParams(char const** SSID, char const** securityKey)
    {
        *SSID        = FlashDictionary::getString(STR_CLSSID, STR_);
        *securityKey = FlashDictionary::getString(STR_CLSECKEY, STR_);
    }
    
        
    // IP, netmask, gateway valid only if staticIP = true
    void STC_FLASHMEM ConfigurationManager::setClientIPParams(bool staticIP, char const* IP, char const* netmask, char const* gateway)
    {
        FlashDictionary::setBool(STR_CLSTATIC, staticIP);
        FlashDictionary::setString(STR_CLIP, IP);
        FlashDictionary::setString(STR_CLNETMSK, netmask);
        FlashDictionary::setString(STR_CLGTW, gateway);			
    }
    
    
    // IP, netmask, gateway valid only if staticIP = true
    void STC_FLASHMEM ConfigurationManager::getClientIPParams(bool* staticIP, char const** IP, char const** netmask, char const** gateway)
    {
        *staticIP = FlashDictionary::getBool(STR_CLSTATIC, false);
        *IP       = FlashDictionary::getString(STR_CLIP, STR_);
        *netmask  = FlashDictionary::getString(STR_CLNETMSK, STR_);
        *gateway  = FlashDictionary::getString(STR_CLGTW, STR_);
    }
    
    
    void STC_FLASHMEM ConfigurationManager::setAccessPointIPParams(char const* IP, char const* netmask, char const* gateway)
    {
        FlashDictionary::setString(STR_APIP, IP);
        FlashDictionary::setString(STR_APNETMSK, netmask);
        FlashDictionary::setString(STR_APGTW, gateway);			
    }
    
    
    void STC_FLASHMEM ConfigurationManager::getAccessPointIPParams(char const** IP, char const** netmask, char const** gateway)
    {
        *IP       = FlashDictionary::getString(STR_APIP, FSTR("192.168.4.1"));
        *netmask  = FlashDictionary::getString(STR_APNETMSK, FSTR("255.255.255.0"));
        *gateway  = FlashDictionary::getString(STR_APGTW, FSTR("192.168.4.1"));
    }
    
    
    void STC_FLASHMEM ConfigurationManager::setDHCPServerParams(bool enabled, char const* startIP, char const* endIP)
    {
        FlashDictionary::setBool(STR_DHCPDEN, enabled);
        if (startIP && endIP)
        {
            FlashDictionary::setString(STR_DHCPDIP1, startIP);
            FlashDictionary::setString(STR_DHCPDIP2, endIP);
        }
    }
    
    
    void STC_FLASHMEM ConfigurationManager::getDHCPServerParams(bool* enabled, char const** startIP, char const** endIP)
    {
        *enabled   = FlashDictionary::getBool(STR_DHCPDEN, true);
        *startIP   = FlashDictionary::getString(STR_DHCPDIP1, FSTR("192.168.4.100"));
        *endIP     = FlashDictionary::getString(STR_DHCPDIP2, FSTR("192.168.4.110"));
    }
    

    void STC_FLASHMEM ConfigurationManager::setRouting(bool enabled)
    {
        FlashDictionary::setBool(STR_ROUTING, enabled);
    }
    

    void STC_FLASHMEM ConfigurationManager::getRouting(bool* enabled)
    {
        *enabled = FlashDictionary::getBool(STR_ROUTING, false);
    }

    
    void STC_FLASHMEM ConfigurationManager::setDNSParams(IPAddress DNS1, IPAddress DNS2)
    {
        FlashDictionary::setInt(STR_DNS1, DNS1.get_uint32());
        FlashDictionary::setInt(STR_DNS2, DNS2.get_uint32());
    }
    
    
    void STC_FLASHMEM ConfigurationManager::getDNSParams(IPAddress* DNS1, IPAddress* DNS2)
    {
        *DNS1 = FlashDictionary::getInt(STR_DNS1, IPAddress(8, 8, 8, 8).get_uint32());
        *DNS2 = FlashDictionary::getInt(STR_DNS2, IPAddress(8, 8, 4, 4).get_uint32());
    }
    
    
    void STC_FLASHMEM ConfigurationManager::setWebServerParams(uint16_t port)
    {
        FlashDictionary::setInt(STR_WEBPORT, port);
    }
    
    
    void STC_FLASHMEM ConfigurationManager::getWebServerParams(uint16_t* port)
    {
        *port = FlashDictionary::getInt(STR_WEBPORT, 80);
    }
    
    
    void STC_FLASHMEM ConfigurationManager::setUARTParams(uint32_t baudRate, bool enableSystemOutput, SerialService serialService)
    {
        FlashDictionary::setInt(STR_BAUD, baudRate);
        FlashDictionary::setBool(STR_SYSOUT, enableSystemOutput);
        FlashDictionary::setInt(STR_UARTSRV, (int32_t)serialService);
    }
    
    
    void STC_FLASHMEM ConfigurationManager::getUARTParams(uint32_t* baudRate, bool* enableSystemOutput, SerialService* serialService)
    {
        *baudRate           = FlashDictionary::getInt(STR_BAUD, 9600);
        *enableSystemOutput = FlashDictionary::getBool(STR_SYSOUT, false);

#if (FDV_INCLUDE_SERIALBINARY == 1)     
        *serialService = (SerialService)FlashDictionary::getInt(STR_UARTSRV, (int32_t)SerialService_BinaryProtocol);
#elif (FDV_INCLUDE_SERIALCONSOLE == 1)
        *serialService = (SerialService)FlashDictionary::getInt(STR_UARTSRV, (int32_t)SerialService_Console);
#else
        *serialService = (SerialService)FlashDictionary::getInt(STR_UARTSRV, (int32_t)SerialService_None);
#endif    
    }
    
    
#if (FDV_INCLUDE_SERIALCONSOLE == 1)
    SerialConsole* STC_FLASHMEM ConfigurationManager::getSerialConsole()
    {
        return s_serialConsole;
    }
#endif
    
    
#if (FDV_INCLUDE_SERIALBINARY == 1)
    SerialBinary* STC_FLASHMEM ConfigurationManager::getSerialBinary()
    {
        return s_serialBinary;
    }
#endif


    void STC_FLASHMEM ConfigurationManager::setGPIOParams(uint32_t gpioNum, bool configured, bool isOutput, bool pullUp, bool value)
    {
        APtr<char> key(f_printf(FSTR("GPIO%d"), gpioNum));
        GPIOInfo info = {configured, isOutput, pullUp, value};
        FlashDictionary::setValue(key.get(), &info, sizeof(GPIOInfo));
    }
    
    
    void STC_FLASHMEM ConfigurationManager::getGPIOParams(uint32_t gpioNum, bool* configured, bool* isOutput, bool* pullUp, bool* value)
    {
        APtr<char> key(f_printf(FSTR("GPIO%d"), gpioNum));
        uint8_t const* infoPtr = FlashDictionary::getValue(key.get());			
        if (infoPtr)
        {
            uint32_t infoInt = getDWord(infoPtr);
            GPIOInfo* info = (GPIOInfo*)&infoInt;
            *configured = info->configured;
            *isOutput   = info->isOutput;
            *pullUp     = info->pullUp;
            *value      = info->value;
        }
        else
        {
            // defaults
            *configured = false;
            *isOutput   = false;
            *pullUp     = false;
            *value      = false;
        }
    }
    
    
    void STC_FLASHMEM ConfigurationManager::setDateTimeParams(int8_t timezoneHours, uint8_t timezoneMinutes, char const* defaultNTPServer)
    {
        FlashDictionary::setInt(STR_TZHH, timezoneHours);
        FlashDictionary::setInt(STR_TZMM, timezoneMinutes);
        FlashDictionary::setString(STR_DEFNTPSRV, defaultNTPServer);
    }
    
    
    void STC_FLASHMEM ConfigurationManager::getDateTimeParams(int8_t* timezoneHours, uint8_t* timezoneMinutes, char const** defaultNTPServer)
    {
        *timezoneHours    = FlashDictionary::getInt(STR_TZHH, 0);
        *timezoneMinutes  = FlashDictionary::getInt(STR_TZMM, 0);
        *defaultNTPServer = FlashDictionary::getString(STR_DEFNTPSRV, FSTR("ntp1.inrim.it"));
    }
    
    
    DateTime STC_FLASHMEM ConfigurationManager::getBootDateTime(bool set, DateTime const& value)
    {
        static DateTime s_bootTime;
        static bool s_init = false;
        
        if (!s_init)
        {
            // this is necessary because statics classes (like DateTime is not initializated automatically)
            s_init = true;
            s_bootTime = DateTime();
        }
        
        if (set)
            s_bootTime = value;
        
        return s_bootTime;
    }
    
    
    // outbuf must be at least 22 bytes
    void STC_FLASHMEM ConfigurationManager::getUpTimeStr(char* outbuf)
    {
        int32_t seconds = DateTime::now() - getBootDateTime();
        uint32_t days = seconds / 86400;
        seconds %= 86400;
        uint32_t hours = seconds / 3600;
        seconds %= 3600;
        uint32_t minutes = seconds / 60;
        seconds %= 60;
        sprintf(outbuf, FSTR("%d days, %02d:%02d:%02d\r\n"), days, hours, minutes, seconds);
    }


    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPHelperConfiguration

    
    void MTD_FLASHMEM HTTPHelperConfiguration::getWiFiMode(HTTPTemplateResponse* response)
    {
        switch (ConfigurationManager::getWiFiMode())
        {
            case WiFi::Client:
                response->addParamStr(STR_clientmode, STR_checked);
                break;
            case WiFi::AccessPoint:
                response->addParamStr(STR_apmode, STR_checked);
                break;
            case WiFi::ClientAndAccessPoint:
                response->addParamStr(STR_bothsmode, STR_checked);
                break;
        }
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::setWiFiMode(HTTPTemplateResponse* response)
    {
        char const* Mode = response->getRequest().form[STR_Mode];
        if (f_strcmp(Mode, STR_bothsmode) == 0)
            ConfigurationManager::setWiFiMode(WiFi::ClientAndAccessPoint);
        else if (f_strcmp(Mode, STR_clientmode) == 0)
            ConfigurationManager::setWiFiMode(WiFi::Client);
        else if (f_strcmp(Mode, STR_apmode) == 0)
            ConfigurationManager::setWiFiMode(WiFi::AccessPoint);
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::getClientModeWiFiParams(HTTPTemplateResponse* response)
    {
        char const* SSID = response->getRequest().query[FSTR("AP")]; // get SSID from last scan?
        char const* securityKey;
        if (!SSID)
        {				
            // get from configuration among the password
            ConfigurationManager::getClientParams(&SSID, &securityKey);
            response->addParamStr(FSTR("CLPSW"), securityKey);
        }
        response->addParamStr(FSTR("CLSSID"), SSID);
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::setClientModeWiFiParams(HTTPTemplateResponse* response)
    {
        ConfigurationManager::setClientParams(response->getRequest().form[FSTR("CLSSID")],
                                              response->getRequest().form[FSTR("CLPSW")]);
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::getClientModeIP(HTTPTemplateResponse* response)
    {
        bool staticIP;
        char const* IP;
        char const* netmask;
        char const* gateway;
        ConfigurationManager::getClientIPParams(&staticIP, &IP, &netmask, &gateway);			
        if (staticIP)
            response->addParamStr(STR_stcIP, STR_checked);
        else
            response->addParamStr(STR_dynIP, STR_checked);
        response->addParamStr(STR_CLIP, IP);
        response->addParamStr(STR_CLMSK, netmask);
        response->addParamStr(STR_CLGTW, gateway);            
    }

    void MTD_FLASHMEM HTTPHelperConfiguration::setClientModeIP(HTTPTemplateResponse* response)
    {
        ConfigurationManager::setClientIPParams(f_strcmp(response->getRequest().form[STR_CLIPMOD], STR_stcIP) == 0,
                                                response->getRequest().form[STR_CLIP],
                                                response->getRequest().form[STR_CLMSK],
                                                response->getRequest().form[STR_CLGTW]);
    }

    // DNS1str and DNS2str cannot be allocated into the stack here because they are used in response object
    void MTD_FLASHMEM HTTPHelperConfiguration::getDNSServer(HTTPTemplateResponse* response, IPAddress::IPAddressStr& DNS1str, IPAddress::IPAddressStr& DNS2str)
    {
        IPAddress DNS1, DNS2;
        ConfigurationManager::getDNSParams(&DNS1, &DNS2);
        DNS1str = DNS1.get_str();
        DNS2str = DNS2.get_str();
        response->addParamStr(STR_DNS1, DNS1str);
        response->addParamStr(STR_DNS2, DNS2str);
    }

    void MTD_FLASHMEM HTTPHelperConfiguration::setDNSServer(HTTPTemplateResponse* response)
    {
        ConfigurationManager::setDNSParams(IPAddress(response->getRequest().form[STR_DNS1]), IPAddress(response->getRequest().form[STR_DNS2]));
    }
    
    // must be "char dateStr[11]" and "char timeStr[9]"
    void MTD_FLASHMEM HTTPHelperConfiguration::getDateTime(HTTPTemplateResponse* response, char* dateStr, char* timeStr)
    {
        // get current date
        DateTime::now().format(dateStr, FSTR("%d/%m/%Y"));
        response->addParamStr(STR_date, dateStr);
        
        // get current time
        DateTime::now().format(timeStr, FSTR("%H:%M:%S"));
        response->addParamStr(STR_time, timeStr);
        
        // get timezone and NTP server
        int8_t timezoneHours;
        uint8_t timezoneMinutes;
        char const* defaultNTPServer;
        ConfigurationManager::getDateTimeParams(&timezoneHours, &timezoneMinutes, &defaultNTPServer);
        response->addParamInt(STR_tzh, timezoneHours);
        response->addParamInt(STR_tzm, timezoneMinutes);
        response->addParamStr(STR_ntpsrv, defaultNTPServer);
        
        if (f_strlen(defaultNTPServer) == 0)
            response->addParamStr(STR_CHTIMEMAN, STR_checked);
        else
            response->addParamStr(STR_CHTIMEAUT, STR_checked);
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::setDateTime(HTTPTemplateResponse* response)
    {
        // set current date and time
        char const* dateStr = response->getRequest().form[STR_date];
        char const* timeStr = response->getRequest().form[STR_time];
        if (dateStr && timeStr)
        {
            DateTime dt;
            dt.decode(dateStr, FSTR("%d/%m/%Y"));
            dt.decode(timeStr, FSTR("%H:%M:%S"));
            DateTime::setCurrentDateTime(dt);
        }
        
        // set timezone and NTP server
        char const* tzh = response->getRequest().form[STR_tzh];
        char const* tzm = response->getRequest().form[STR_tzm];
        char const* ntpsrv = response->getRequest().form[STR_ntpsrv];
        if (tzh && tzm)
        {
            ConfigurationManager::setDateTimeParams(strtol(tzh, NULL, 10),
                                                    strtol(tzm, NULL, 10),
                                                    ntpsrv? ntpsrv : STR_);                                                            
            ConfigurationManager::applyDateTime();
        }
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::getUART(HTTPTemplateResponse* response)
    {
        uint32_t baudRate;
        bool enableSystemOutput;
        SerialService serialService;
        ConfigurationManager::getUARTParams(&baudRate, &enableSystemOutput, &serialService);
        response->addParamInt(STR_baud, baudRate);
        if (enableSystemOutput)
            response->addParamStr(STR_debugout, STR_checked);
        switch (serialService)
        {
            case SerialService_None:
                response->addParamStr(STR_srv0, STR_checked);
                break;
            case SerialService_Console:
                response->addParamStr(STR_srv1, STR_checked);
                break;
            case SerialService_BinaryProtocol:
                response->addParamStr(STR_srv2, STR_checked);
                break;
        }
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::setUART(HTTPTemplateResponse* response)
    {
        char const* baud = response->getRequest().form[STR_baud];
        char const* serv = response->getRequest().form[FSTR("srv")];
        if (baud && serv)
        {
            ConfigurationManager::setUARTParams(strtol(baud, NULL, 10),
                                                response->getRequest().form[STR_debugout] != NULL,
                                                (SerialService)strtol(serv, NULL, 10));
            ConfigurationManager::applyUARTServices();
        }            
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::getAPWiFiParams(HTTPTemplateResponse* response, APtr<char>& APCHStr, APtr<char>& APSECStr)
    {
        uint8_t channel;
        WiFi::SecurityProtocol securityProtocol;
        bool hiddenSSID;
        char const* SSID;
        char const* securityKey;
        ConfigurationManager::getAccessPointParams(&SSID, &securityKey, &channel, &securityProtocol, &hiddenSSID);
        response->addParamStr(FSTR("APSSID"), SSID);
        response->addParamStr(FSTR("APPSW"), securityKey);
        APCHStr.reset(f_printf(FSTR("APCH%d"), channel));
        response->addParamStr(APCHStr.get(), STR_selected);
        APSECStr.reset(f_printf(FSTR("APSEC%d"), (int32_t)securityProtocol));
        response->addParamStr(APSECStr.get(), STR_selected);
        if (hiddenSSID)
            response->addParamStr(FSTR("APHSSID"), STR_checked);
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::setAPWiFiParams(HTTPTemplateResponse* response)
    {
        char const* APCH    = response->getRequest().form[FSTR("APCH")];
        char const* APSEC   = response->getRequest().form[FSTR("APSEC")];
        if (APCH && APSEC)
            ConfigurationManager::setAccessPointParams(response->getRequest().form[FSTR("APSSID")], 
                                                       response->getRequest().form[FSTR("APPSW")], 
                                                       strtol(APCH, NULL, 10),
                                                       (WiFi::SecurityProtocol)strtol(APSEC, NULL, 10),
                                                       response->getRequest().form[FSTR("APHSSID")] != NULL);
        
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::getAPModeIP(HTTPTemplateResponse* response)
    {
        char const* IP;
        char const* netmask;
        char const* gateway;
        ConfigurationManager::getAccessPointIPParams(&IP, &netmask, &gateway);			
        response->addParamStr(STR_APIP, IP);
        response->addParamStr(STR_APMSK, netmask);
        response->addParamStr(STR_APGTW, gateway);            
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::setAPModeIP(HTTPTemplateResponse* response)
    {
        ConfigurationManager::setAccessPointIPParams(response->getRequest().form[STR_APIP],
                                                     response->getRequest().form[STR_APMSK],
                                                     response->getRequest().form[STR_APGTW]);
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::getDHCPServer(HTTPTemplateResponse* response)
    {
        bool DHCPDEnabled;
        char const* startIP;
        char const* endIP;
        ConfigurationManager::getDHCPServerParams(&DHCPDEnabled, &startIP, &endIP);
        if (DHCPDEnabled)
            response->addParamStr(STR_DHCPD, STR_checked);
        response->addParamStr(STR_startIP, startIP);
        response->addParamStr(STR_endIP, endIP);            
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::setDHCPServer(HTTPTemplateResponse* response)
    {
        if (response->getRequest().form[STR_DHCPD] != NULL)
            ConfigurationManager::setDHCPServerParams(true,
                                                      response->getRequest().form[STR_startIP],
                                                      response->getRequest().form[STR_endIP]);
        else
            ConfigurationManager::setDHCPServerParams(false);
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::getRouting(HTTPTemplateResponse* response)
    {
        bool routing;
        ConfigurationManager::getRouting(&routing);
        if (routing)
            response->addParamStr(STR_ROUTING, STR_checked);
    }
    
    void MTD_FLASHMEM HTTPHelperConfiguration::setRouting(HTTPTemplateResponse* response)
    {
        ConfigurationManager::setRouting(response->getRequest().form[STR_ROUTING] != NULL);
    }

    

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPWifiConfigurationResponse
    
    MTD_FLASHMEM HTTPWifiConfigurationResponse::HTTPWifiConfigurationResponse(HTTPHandler* httpHandler, char const* filename)
        : HTTPTemplateResponse(httpHandler, filename)
    {
    }
    
    void MTD_FLASHMEM HTTPWifiConfigurationResponse::flush()
    {
        if (getRequest().method == HTTPHandler::Post)
        {
            // set WiFi mode
            HTTPHelperConfiguration::setWiFiMode(this);
            
            // set client mode WiFi parameters
            HTTPHelperConfiguration::setClientModeWiFiParams(this);
            
            // set access point parameters
            HTTPHelperConfiguration::setAPWiFiParams(this);
        }
        
        // get WiFi mode
        HTTPHelperConfiguration::getWiFiMode(this);
        
        // get client mode WiFi parameters
        HTTPHelperConfiguration::getClientModeWiFiParams(this);
        
        // get access point parameters
        APtr<char> APCHStr, APSECStr;
        HTTPHelperConfiguration::getAPWiFiParams(this, APCHStr, APSECStr);
        
        HTTPTemplateResponse::flush();
    }
    
    
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPNetworkConfigurationResponse

    MTD_FLASHMEM HTTPNetworkConfigurationResponse::HTTPNetworkConfigurationResponse(HTTPHandler* httpHandler, char const* filename)
        : HTTPTemplateResponse(httpHandler, filename)
    {
    }
    
    void MTD_FLASHMEM HTTPNetworkConfigurationResponse::flush()
    {
        if (getRequest().method == HTTPHandler::Post)
        {
            // set client mode IP configuration
            HTTPHelperConfiguration::setClientModeIP(this);
                                                    
            // set access point IP configuration
            HTTPHelperConfiguration::setAPModeIP(this);

            // set DHCP server configuration
            HTTPHelperConfiguration::setDHCPServer(this);
            
            // set DNS
            HTTPHelperConfiguration::setDNSServer(this);
            
            // set Routing
            HTTPHelperConfiguration::setRouting(this);
            ConfigurationManager::applyRouting();
        }
        
        
        // get client mode IP configuration
        HTTPHelperConfiguration::getClientModeIP(this);
        WiFi::Mode mode = ConfigurationManager::getWiFiMode();
        addParamStr(STR_DISP_CLIPCONF, mode == WiFi::Client || mode == WiFi::ClientAndAccessPoint? STR_ : STR_disabled);
        
        // get access point IP configuration
        HTTPHelperConfiguration::getAPModeIP(this);
        addParamStr(STR_DISP_APIPCONF, mode == WiFi::AccessPoint || mode == WiFi::ClientAndAccessPoint? STR_ : STR_disabled);
        
        // get DHCP server configuration
        HTTPHelperConfiguration::getDHCPServer(this);
        addParamStr(FSTR("DISP_DHCPD"), mode == WiFi::AccessPoint || mode == WiFi::ClientAndAccessPoint? STR_ : STR_disabled);
        
        // get DNS server configuration
        IPAddress::IPAddressStr DNS1str, DNS2str;
        HTTPHelperConfiguration::getDNSServer(this, DNS1str, DNS2str);            
        
        // get routing configuration
        HTTPHelperConfiguration::getRouting(this);
        
        HTTPTemplateResponse::flush();
    }
    
    
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPServicesConfigurationResponse

    MTD_FLASHMEM HTTPServicesConfigurationResponse::HTTPServicesConfigurationResponse(HTTPHandler* httpHandler, char const* filename)
        : HTTPTemplateResponse(httpHandler, filename)
    {
    }
    
    void MTD_FLASHMEM HTTPServicesConfigurationResponse::flush()
    {
        if (getRequest().method == HTTPHandler::Post)
        {
            // set Web server configuration
            char const* httpport = getRequest().form[STR_httpport];
            if (httpport)
                ConfigurationManager::setWebServerParams(strtol(httpport, NULL, 10));
            
            // set UART configuration
            HTTPHelperConfiguration::setUART(this);
        }
        
        // get Web server configuration
        uint16_t webPort;
        ConfigurationManager::getWebServerParams(&webPort);
        addParamInt(STR_httpport, webPort);
        
        // get UART configuration
        HTTPHelperConfiguration::getUART(this);
        
        HTTPTemplateResponse::flush();
    }
		
    
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPWiFiScanResponse

    MTD_FLASHMEM HTTPWiFiScanResponse::HTTPWiFiScanResponse(HTTPHandler* httpHandler, char const* filename)
        : HTTPTemplateResponse(httpHandler, filename)
    {
    }
    
    void MTD_FLASHMEM HTTPWiFiScanResponse::flush()
    {
        uint32_t count = 0;
        WiFi::APInfo* infos = WiFi::getAPList(&count, true);

        LinkedCharChunks* linkedChunks = addParamCharChunks(FSTR("APS"));
        for (uint32_t i = 0; i != count; ++i)
        {
            linkedChunks->addChunk(f_printf(FSTR("<tr> <td><a href='confwifi?AP=%s'>%s</a></td> <td>%02X:%02X:%02X:%02X:%02X:%02X</td> <td>%d</td> <td>%d</td> <td>%s</td> </tr>"), 
                                            infos[i].SSID,
                                            infos[i].SSID,
                                            infos[i].BSSID[0], infos[i].BSSID[1], infos[i].BSSID[2], infos[i].BSSID[3], infos[i].BSSID[4], infos[i].BSSID[5],
                                            infos[i].Channel,
                                            infos[i].RSSI,
                                            WiFi::convSecurityProtocolToString(infos[i].AuthMode)),
                                   true);
        }						

        HTTPTemplateResponse::flush();
    }

    
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPWiFiScanResponseHTMLRows
    // Helper for HTTPWizardConfigurationResponse

    MTD_FLASHMEM HTTPWiFiScanResponseHTMLRows::HTTPWiFiScanResponseHTMLRows(HTTPHandler* httpHandler)
        : HTTPResponse(httpHandler, NULL)
    {
    }
    
    void MTD_FLASHMEM HTTPWiFiScanResponseHTMLRows::flush()
    {
        setStatus(STR_200_OK);
        addHeader(STR_Content_Type, FSTR("text/html"));            
        
        uint32_t count = 0;
        WiFi::APInfo* infos = WiFi::getAPList(&count, true);

        addContent(FSTR("<tr> <th>SSID</th> <th>Address</th> <th>Channel</th> <th>RSSI</th> <th>Security</th> </tr>"));
        for (uint32_t i = 0; i != count; ++i)
        {
            addContent(f_printf(FSTR("<tr> <td>%s</td> <td>%02X:%02X:%02X:%02X:%02X:%02X</td> <td>%d</td> <td>%d</td> <td>%s</td> </tr>"), 
                                infos[i].SSID,
                                infos[i].BSSID[0], infos[i].BSSID[1], infos[i].BSSID[2], infos[i].BSSID[3], infos[i].BSSID[4], infos[i].BSSID[5],
                                infos[i].Channel,
                                infos[i].RSSI,
                                WiFi::convSecurityProtocolToString(infos[i].AuthMode)),
                       true);
        }						

        HTTPResponse::flush();
    }
    
    
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPGPIOConfigurationResponse

    MTD_FLASHMEM HTTPGPIOConfigurationResponse::HTTPGPIOConfigurationResponse(HTTPHandler* httpHandler, char const* filename)
        : HTTPTemplateResponse(httpHandler, filename)
    {
    }
    
    void MTD_FLASHMEM HTTPGPIOConfigurationResponse::flush()
    {
        if (getRequest().method == HTTPHandler::Post)
        {
            char const* gpio = getRequest().form[FSTR("GPIO")];
            if (getRequest().form[FSTR("configured")])
            {					
                char const* mode     = getRequest().form[FSTR("mode")];
                char const* pullUp   = getRequest().form[FSTR("pullup")];
                ConfigurationManager::setGPIOParams(strtol(gpio, NULL, 10), true, f_strcmp(mode, FSTR("out")) == 0, pullUp != NULL, false);
                ConfigurationManager::applyGPIO();
            }
            else if (gpio)
            {
                ConfigurationManager::setGPIOParams(strtol(gpio, NULL, 10), false, false, false, false);
            }
        }
        
        bool configured, isOutput, pullUp, value;
        
        char const* gpio = getRequest().query[FSTR("gpio")];
        char const* val  = getRequest().query[FSTR("val")];
        if (gpio && val)
        {
            uint8_t gpion = strtol(gpio, NULL, 10);
            ConfigurationManager::getGPIOParams(gpion, &configured, &isOutput, &pullUp, &value);
            value = *val - '0';
            ConfigurationManager::setGPIOParams(gpion, configured, isOutput, pullUp, value);
            GPIO(gpion).write(value);
        }
            
        LinkedCharChunks* linkedChunks = addParamCharChunks(FSTR("GPIOS"));
        for (uint32_t i = 0; i != 16; ++i)
        {
            if (i != 1 && i != 3 && (i < 6 || i > 11))
            {
                bool configured, isOutput, pullUp, value;
                ConfigurationManager::getGPIOParams(i, &configured, &isOutput, &pullUp, &value);
                
                linkedChunks->addChunk(f_printf(FSTR("<tr> <td>%d</td> <td><form method='POST'>"), i), true);
                linkedChunks->addChunk(f_printf(FSTR("Enabled <input type='checkbox' name='configured' value='1' onclick=\"document.getElementById('GPIO%d').disabled=!this.checked\" %s>"), i, configured? STR_checked:STR_), true);
                linkedChunks->addChunk(f_printf(FSTR("<fieldset class='inline' id='GPIO%d' %s>"), i, configured? STR_:STR_disabled), true);
                linkedChunks->addChunk(f_printf(FSTR("<select name='mode'><option value='in' %s>IN</option><option value='out' %s>OUT</option></select>"), 
                                               isOutput? STR_:STR_selected, 
                                               isOutput? STR_selected:STR_), 
                                      true);
                linkedChunks->addChunk(f_printf(FSTR("     PullUp <input type='checkbox' name='pullup' value='1' %s> </fieldset>"), pullUp? STR_checked:STR_), true);
                linkedChunks->addChunk(f_printf(FSTR("<input type='hidden' name='GPIO' value='%d'>"), i), true);
                linkedChunks->addChunk(FSTR("<input type='submit' value='Save'></form></td>"));
                if (configured)
                {
                    if (isOutput)
                    {
                        linkedChunks->addChunk(f_printf(FSTR("<td><a href='confgpio?gpio=%d&val=%d' class='link_button2'>%s</a></td> </tr>"), i, !value, value? STR_HI:STR_LO), true);
                    }
                    else
                    {
                        linkedChunks->addChunk(f_printf(FSTR("<td>%s</td> </tr>"), GPIO(i).read()? STR_HI:STR_LO), true);
                    }
                }
                else
                {
                    linkedChunks->addChunk(FSTR("<td></td></tr>"));
                }
            }
        }			
            
        HTTPTemplateResponse::flush();
    }
	


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPTimeConfigurationResponse

    MTD_FLASHMEM HTTPTimeConfigurationResponse::HTTPTimeConfigurationResponse(HTTPHandler* httpHandler, char const* filename)
        : HTTPTemplateResponse(httpHandler, filename)
    {
    }
    
    void MTD_FLASHMEM HTTPTimeConfigurationResponse::flush()
    {
        if (getRequest().method == HTTPHandler::Post)
        {
            HTTPHelperConfiguration::setDateTime(this);
        }
        
        char dateStr[11], timeStr[9];
        HTTPHelperConfiguration::getDateTime(this, dateStr, timeStr);
                    
        HTTPTemplateResponse::flush();
    }
		
	
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPWizardConfigurationResponse

    MTD_FLASHMEM HTTPWizardConfigurationResponse::HTTPWizardConfigurationResponse(HTTPHandler* httpHandler, char const* filename)
        : HTTPTemplateResponse(httpHandler, filename)
    {
    }
    
    void HTTPWizardConfigurationResponse::flush()
    {
        if (getRequest().method == HTTPHandler::Post)
        {
            // set WiFi mode
            HTTPHelperConfiguration::setWiFiMode(this);

            // set client mode WiFi parameters
            HTTPHelperConfiguration::setClientModeWiFiParams(this);

            // set client mode IP configuration
            HTTPHelperConfiguration::setClientModeIP(this);
            
            // set DNS
            HTTPHelperConfiguration::setDNSServer(this);                
            
            // date time, ntp, ...
            HTTPHelperConfiguration::setDateTime(this);

            // set UART configuration
            HTTPHelperConfiguration::setUART(this);

            // set access point parameters
            HTTPHelperConfiguration::setAPWiFiParams(this);
            
            // set access point IP configuration
            HTTPHelperConfiguration::setAPModeIP(this);                
            
            // set DHCP server configuration
            HTTPHelperConfiguration::setDHCPServer(this);                
            
            // set Routing
            HTTPHelperConfiguration::setRouting(this);                
        }
                
        // get WiFi mode
        HTTPHelperConfiguration::getWiFiMode(this);
                   
        // get client mode WiFi parameters
        HTTPHelperConfiguration::getClientModeWiFiParams(this);
              
        // get client mode IP configuration
        HTTPHelperConfiguration::getClientModeIP(this);                  
        
        // get DNS server configuration
        IPAddress::IPAddressStr DNS1str, DNS2str;
        HTTPHelperConfiguration::getDNSServer(this, DNS1str, DNS2str);            
        
        // datetime, ntp, ...
        char dateStr[11], timeStr[9];
        HTTPHelperConfiguration::getDateTime(this, dateStr, timeStr);            

        // get UART configuration
        HTTPHelperConfiguration::getUART(this);

        // get access point parameters
        APtr<char> APCHStr, APSECStr;
        HTTPHelperConfiguration::getAPWiFiParams(this, APCHStr, APSECStr);
        
        // get access point IP configuration
        HTTPHelperConfiguration::getAPModeIP(this);            

        // get DHCP server configuration
        HTTPHelperConfiguration::getDHCPServer(this);

        // get routing configuration
        HTTPHelperConfiguration::getRouting(this);
        
        HTTPTemplateResponse::flush();
    }
		
    

    
    

    
}



