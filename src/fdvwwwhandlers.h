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

#ifndef _FDVWWWHANDLERS_H_
#define _FDVWWWHANDLERS_H_

#include "fdv.h"

namespace fdv {


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPHelperConfiguration
// Common configuration GET and POST handling routines

struct HTTPHelperConfiguration {
  static void getWiFiMode(HTTPTemplateResponse *response);
  static void setWiFiMode(HTTPTemplateResponse *response);

  static void getClientModeWiFiParams(HTTPTemplateResponse *response);
  static void setClientModeWiFiParams(HTTPTemplateResponse *response);

  static void getClientModeIP(HTTPTemplateResponse *response);
  static void setClientModeIP(HTTPTemplateResponse *response);

  static void getDNSServer(HTTPTemplateResponse *response, IPAddress::IPAddressStr &DNS1str,
                           IPAddress::IPAddressStr &DNS2str);
  static void setDNSServer(HTTPTemplateResponse *response);

  static void getDateTime(HTTPTemplateResponse *response, char *dateStr, char *timeStr);
  static void setDateTime(HTTPTemplateResponse *response);

  static void getUART(HTTPTemplateResponse *response);
  static void setUART(HTTPTemplateResponse *response);

  static void getAPWiFiParams(HTTPTemplateResponse *response, APtr<char> &APCHStr, APtr<char> &APSECStr);
  static void setAPWiFiParams(HTTPTemplateResponse *response);

  static void getAPModeIP(HTTPTemplateResponse *response);
  static void setAPModeIP(HTTPTemplateResponse *response);

  static void getDHCPServer(HTTPTemplateResponse *response);
  static void setDHCPServer(HTTPTemplateResponse *response);

  static void getRouting(HTTPTemplateResponse *response);
  static void setRouting(HTTPTemplateResponse *response);

  static void GPIOSetValue(HTTPResponse *response);
  static void GPIOConf(HTTPResponse *response);
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPWifiConfigurationResponse

struct HTTPWifiConfigurationResponse : public HTTPTemplateResponse {
  HTTPWifiConfigurationResponse(HTTPHandler *httpHandler, char const *filename);

  virtual void flush();
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPNetworkConfigurationResponse

struct HTTPNetworkConfigurationResponse : public HTTPTemplateResponse {
  HTTPNetworkConfigurationResponse(HTTPHandler *httpHandler, char const *filename);

  virtual void flush();
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPServicesConfigurationResponse

struct HTTPServicesConfigurationResponse : public HTTPTemplateResponse {
  HTTPServicesConfigurationResponse(HTTPHandler *httpHandler, char const *filename);

  virtual void flush();
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPWiFiScanResponseHTMLRows
// Helper for HTTPWizardConfigurationResponse

struct HTTPWiFiScanResponseHTMLRows : public HTTPResponse {
  HTTPWiFiScanResponseHTMLRows(HTTPHandler *httpHandler);

  virtual void flush();
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPGPIOConfigurationResponse

struct HTTPGPIOConfigurationResponse : public HTTPTemplateResponse {
  HTTPGPIOConfigurationResponse(HTTPHandler *httpHandler, char const *filename);

  virtual void flush();
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPTimeConfigurationResponse

struct HTTPTimeConfigurationResponse : public HTTPTemplateResponse {
  HTTPTimeConfigurationResponse(HTTPHandler *httpHandler, char const *filename);

  virtual void flush();
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPWizardConfigurationResponse

struct HTTPWizardConfigurationResponse : public HTTPTemplateResponse {
  HTTPWizardConfigurationResponse(HTTPHandler *httpHandler, char const *filename);

  virtual void flush();
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPGPIOResponseHTML
// Just allows to read write gpio values or to configure gpio port
//
// Query string:
//   cmd   = get/set/conf (if not present, "get" is assumed)
// If cmd="get":
//   gpio  = 0..16
// If cmd="set":
//   gpio  = 0..16
//   val   = 0..1
//   store = 0..1 (0=not store in flash, 1= store in flash) (if not present is like "not store")
// If cmd="conf":
//   gpio  = 0..16
//   mode  = "in".."out"
//   pullup = 0..1 (if not present is like "no pullup")
//   store = 0..1 (0=not store in flash, 1= store in flash) (if not present is like "not store")
// Always returns current state (or new state when cmd=set)
//
// Example: configures GPIO2 as input
//   http://192.168.4.1/gpio?cmd=conf&gpio=2&mode=in
// Example: reads current value of GPIO2
//   http://192.168.4.1/gpio?cmd=get&gpio=2
// Example: configures GPIO2 as output
//   http://192.168.4.1/gpio?cmd=conf&gpio=2&mode=out
// Example: writes 1 to GPIO2 (without storing current value into the flash)
//   http://192.168.4.1/gpio?cmd=set&gpio=2&val=1
// Example: writes 0 to GPIO2 (without storing current value into the flash)
//   http://192.168.4.1/gpio?cmd=set&gpio=2&val=0

struct HTTPGPIOResponseHTML : public HTTPResponse {
  HTTPGPIOResponseHTML(HTTPHandler *httpHandler);

  virtual void flush();
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// HTTPFileSystemBrowserResponse

struct HTTPFileSystemBrowserResponse : public HTTPTemplateResponse {
  HTTPFileSystemBrowserResponse(HTTPHandler *httpHandler, char const *filename);

  virtual void flush();
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// DefaultHTTPHandler

class DefaultHTTPHandler : public HTTPHandler {

public:
  DefaultHTTPHandler();

  virtual void dispatch();

  void get_home();
  void get_confwifi();
  void get_wifiscan();
  void get_confnet();
  void get_confserv();
  void get_confgpio();
  void get_gpio();
  void get_conftime();
  void get_reboot();
  void get_restore();
  void get_confwizard();
  void get_fsbrowser();
  void get_all();
};
}

#endif	// _FDVWWWHANDLERS_H_
