/*
# Created by Fabrizio Di Vittorio (fdivitto2013@gmail.com)
# Copyright (c) 2015/2016 Fabrizio Di Vittorio.
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

#ifndef _FDVCONFMANAGER_H_
#define _FDVCONFMANAGER_H_

#include "fdv.h"

namespace fdv {

enum SerialService {
  SerialService_None = 0,
  SerialService_Console,
  SerialService_BinaryProtocol,
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// ConfigurationManager

class ConfigurationManager {

  template <typename HTTPCustomServer_T> static void MTD_FLASHMEM applyDelayed() {
    applyAccessPointIP();
    applyClientIP();
    applyDHCPServer();
    applyDNS();
    applyDateTime();
    applyGPIO();
    applyWebServer<HTTPCustomServer_T>();
    applyRouting();
  }

public:
  template <typename HTTPCustomServer_T> static void MTD_FLASHMEM applyAll() {
    applyUARTServices();
    applyWiFi();
    asyncExec< applyDelayed<HTTPCustomServer_T> >(512);
  }

  // can be re-applied
  static void applyUARTServices();

  // can be re-applied
  static void applyWiFi();

  // can be re-applied
  // doesn't support GPIO16
  static void applyGPIO();

  // can be re-applied
  static void applyAccessPointIP();

  // can be re-applied
  static void applyClientIP();

  // can be re-applied
  static void applyDHCPServer();

  // can be re-applied
  static void applyDNS();

  // can be re-applied
  static void applyRouting();

  // cannot be re-applied
  template <typename HTTPCustomServer_T> static void MTD_FLASHMEM applyWebServer() {
    // Web Server
    uint16_t webPort;
    getWebServerParams(&webPort);
    new HTTPCustomServer_T(webPort);
  }

  // can be re-applied
  static void applyDateTime();

  static void restore();

  //// WiFi settings

  static void setWiFiMode(WiFi::Mode value);

  static WiFi::Mode getWiFiMode();

  //// Access Point mode parameters

  static void setAccessPointParams(char const *SSID, char const *securityKey, uint8_t channel,
                                   WiFi::SecurityProtocol securityProtocol, bool hiddenSSID);

  static void getAccessPointParams(char const **SSID, char const **securityKey, uint8_t *channel,
                                   WiFi::SecurityProtocol *securityProtocol, bool *hiddenSSID);

  //// Client mode parameters

  static void setClientParams(char const *SSID, char const *securityKey);

  static void getClientParams(char const **SSID, char const **securityKey);

  //// Client mode IP parameters

  // IP, netmask, gateway valid only if staticIP = true
  static void setClientIPParams(bool staticIP, char const *IP, char const *netmask, char const *gateway);

  // IP, netmask, gateway valid only if staticIP = true
  static void getClientIPParams(bool *staticIP, char const **IP, char const **netmask, char const **gateway);

  //// Access point IP parameters

  static void setAccessPointIPParams(char const *IP, char const *netmask, char const *gateway);

  static void getAccessPointIPParams(char const **IP, char const **netmask, char const **gateway);

  //// DHCP server parameters

  static void setDHCPServerParams(bool enabled, char const *startIP = NULL, char const *endIP = NULL);

  static void getDHCPServerParams(bool *enabled, char const **startIP, char const **endIP);

  //// Routing

  static void setRouting(bool enabled);

  static void getRouting(bool *enabled);

  //// DNS parameters

  static void setDNSParams(IPAddress DNS1, IPAddress DNS2);

  static void getDNSParams(IPAddress *DNS1, IPAddress *DNS2);

  //// Web Server parameters

  static void setWebServerParams(uint16_t port);

  static void getWebServerParams(uint16_t *port);

  //// UART parameters

  static void setUARTParams(uint32_t baudRate, bool enableSystemOutput, SerialService serialService);

  static void getUARTParams(uint32_t *baudRate, bool *enableSystemOutput, SerialService *serialService);

#if (FDV_INCLUDE_SERIALCONSOLE == 1)
  static SerialConsole *getSerialConsole();
#endif

#if (FDV_INCLUDE_SERIALBINARY == 1)
  static SerialBinary *getSerialBinary();
#endif

  //// GPIO parameters

  struct GPIOInfo {
    uint32_t configured : 1, isOutput : 1, pullUp : 1, value : 1;
  };

  static void setGPIOParams(uint32_t gpioNum, bool configured, bool isOutput, bool pullUp, bool value);

  static void getGPIOParams(uint32_t gpioNum, bool *configured, bool *isOutput, bool *pullUp, bool *value);

  //// Date-time parameters

  static void setDateTimeParams(int8_t timezoneHours, uint8_t timezoneMinutes, char const *defaultNTPServer);

  static void getDateTimeParams(int8_t *timezoneHours, uint8_t *timezoneMinutes, char const **defaultNTPServer);

  static DateTime getBootDateTime(bool set = false, DateTime const &value = DateTime());
  static void getUpTimeStr(char *outbuf);

private:
#if (FDV_INCLUDE_SERIALCONSOLE == 1)
  static SerialConsole *s_serialConsole;
#endif
#if (FDV_INCLUDE_SERIALBINARY == 1)
  static SerialBinary *s_serialBinary;
#endif
};

}	// end of namespace

#endif	// _FDVCONFMANAGER_H_
