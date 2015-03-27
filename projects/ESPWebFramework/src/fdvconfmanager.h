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

#ifndef _FDVCONFMANAGER_H_
#define _FDVCONFMANAGER_H_



#include "fdv.h"





namespace fdv
{


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// ConfigurationManager

	
	// ConfigurationManager flash parameters
	static char const STR_WiFiMode[] FLASHMEM = "WiFiMode";
	static char const STR_APSSID[] FLASHMEM   = "APSSID";
	static char const STR_APSECKEY[] FLASHMEM = "APSECKEY";
	static char const STR_APCH[] FLASHMEM     = "APCH";
	static char const STR_APSP[] FLASHMEM     = "APSP";
	static char const STR_APHSSID[] FLASHMEM  = "APHSSID";
	static char const STR_CLSSID[] FLASHMEM   = "CLSSID";
	static char const STR_CLSECKEY[] FLASHMEM = "CLSECKEY";
	static char const STR_CLSTATIC[] FLASHMEM = "CLSTATIC";
	static char const STR_CLIP[] FLASHMEM     = "CLIP";
	static char const STR_CLNETMSK[] FLASHMEM = "CLNETMSK";
	static char const STR_CLGTW[] FLASHMEM    = "CLGTW";
	static char const STR_APIP[] FLASHMEM     = "APIP";
	static char const STR_APNETMSK[] FLASHMEM = "APNETMSK";
	static char const STR_APGTW[] FLASHMEM    = "APGTW";
	static char const STR_DHCPDEN[] FLASHMEM  = "DHCPDEN";
	static char const STR_DHCPDIP1[] FLASHMEM = "DHCPDIP1";
	static char const STR_DHCPDIP2[] FLASHMEM = "DHCPDIP2";
	static char const STR_DHCPDMXL[] FLASHMEM = "DHCPDMXL";
	static char const STR_WEBPORT[] FLASHMEM  = "WEBPORT";
	static char const STR_BAUD[] FLASHMEM     = "BAUD";
	static char const STR_SYSOUT[] FLASHMEM   = "SYSOUT";
	static char const STR_UARTSRV[] FLASHMEM  = "UARTSRV";
	

	
	class ConfigurationManager
	{		
		
		template <typename HTTPCustomServer_T>
		static void MTD_FLASHMEM applyDelayed()
		{
			applyAccessPointIP();
			applyClientIP();
			applyDHCPServer();
			applyWebServer<HTTPCustomServer_T>();
			applyGPIO();
		}
		
	
	public:
		
		template <typename HTTPCustomServer_T>
		static void MTD_FLASHMEM applyAll()
		{
			applyUARTServices();
			applyWiFi();
			asyncExec< applyDelayed<HTTPCustomServer_T> >(512);
		}
		
		
		// cannot be re-applied
		static void MTD_FLASHMEM applyUARTServices()
		{
			// UART and serial services
			uint32_t baudRate;
			bool enableSystemOutput;
			SerialService serialService;
			getUARTParams(&baudRate, &enableSystemOutput, &serialService);
			HardwareSerial::getSerial(0)->reconfig(baudRate);
			if (!enableSystemOutput)
				DisableStdOut();
		    switch (serialService)
			{
				case SerialService_Console:
					new SerialConsole;
					break;
				case SerialService_BinaryProtocol:
					// todo
					break;
			}
		}
		
		
		// can be re-applied
		static void MTD_FLASHMEM applyWiFi()
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
		static void MTD_FLASHMEM applyGPIO()
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
		static void MTD_FLASHMEM applyAccessPointIP()
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
		static void MTD_FLASHMEM applyClientIP()
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
		static void MTD_FLASHMEM applyDHCPServer()
		{
			// DCHP Server
			if (getWiFiMode() == WiFi::AccessPoint || getWiFiMode() == WiFi::ClientAndAccessPoint)
			{
				bool enabled;
				char const* startIP;
				char const* endIP;
				uint32_t maxLeases;
				getDHCPServerParams(&enabled, &startIP, &endIP, &maxLeases);
				if (enabled)
					DHCPServer::configure(startIP, endIP, maxLeases);
			}
		}			
		

		// cannot be re-applied
		template <typename HTTPCustomServer_T>
		static void MTD_FLASHMEM applyWebServer()
		{
			// Web Server
			uint16_t webPort;
			getWebServerParams(&webPort);
			new HTTPCustomServer_T(webPort);
		}			

		
		static void MTD_FLASHMEM restore()
		{
			FlashDictionary::eraseContent();
			system_restore();
		}
		
		
		//// WiFi settings
		
		static void MTD_FLASHMEM setWiFiMode(WiFi::Mode value)
		{
			FlashDictionary::setInt(STR_WiFiMode, (int32_t)value);
		}
		
		static WiFi::Mode MTD_FLASHMEM getWiFiMode()
		{
			return (WiFi::Mode)FlashDictionary::getInt(STR_WiFiMode, (int32_t)WiFi::AccessPoint);
		}
		
		
		//// Access Point mode parameters
		
		static void MTD_FLASHMEM setAccessPointParams(char const* SSID, char const* securityKey, uint8_t channel, WiFi::SecurityProtocol securityProtocol, bool hiddenSSID)
		{
			FlashDictionary::setString(STR_APSSID, SSID);
			FlashDictionary::setString(STR_APSECKEY, securityKey);
			FlashDictionary::setInt(STR_APCH, channel);
			FlashDictionary::setInt(STR_APSP, (int32_t)securityProtocol);
			FlashDictionary::setBool(STR_APHSSID, hiddenSSID);
		}
		
		static void MTD_FLASHMEM getAccessPointParams(char const** SSID, char const** securityKey, uint8_t* channel, WiFi::SecurityProtocol* securityProtocol, bool* hiddenSSID)
		{
			static char defaultSSID[10];
			uint8_t mac[16];
			WiFi::getMACAddress(WiFi::AccessPointNetwork, mac);			
			sprintf(defaultSSID, FSTR("ESP%02X%02X%02X%02X%02X%02X"), mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			*SSID             = FlashDictionary::getString(STR_APSSID, defaultSSID);
			*securityKey      = FlashDictionary::getString(STR_APSECKEY, FSTR(""));
			*channel          = FlashDictionary::getInt(STR_APCH, 9);
			*securityProtocol = (WiFi::SecurityProtocol)FlashDictionary::getInt(STR_APSP, (int32_t)WiFi::Open);
			*hiddenSSID       = FlashDictionary::getBool(STR_APHSSID, false);
		}
		
		
		//// Client mode parameters
		
		static void MTD_FLASHMEM setClientParams(char const* SSID, char const* securityKey)
		{
			FlashDictionary::setString(STR_CLSSID, SSID);
			FlashDictionary::setString(STR_CLSECKEY, securityKey);
		}
		
		static void MTD_FLASHMEM getClientParams(char const** SSID, char const** securityKey)
		{
			*SSID        = FlashDictionary::getString(STR_CLSSID, FSTR(""));
			*securityKey = FlashDictionary::getString(STR_CLSECKEY, FSTR(""));
		}
		
		
		//// Client mode IP parameters
		
		// IP, netmask, gateway valid only if staticIP = true
		static void MTD_FLASHMEM setClientIPParams(bool staticIP, char const* IP, char const* netmask, char const* gateway)
		{
			FlashDictionary::setBool(STR_CLSTATIC, staticIP);
			FlashDictionary::setString(STR_CLIP, IP);
			FlashDictionary::setString(STR_CLNETMSK, netmask);
			FlashDictionary::setString(STR_CLGTW, gateway);			
		}
		
		// IP, netmask, gateway valid only if staticIP = true
		static void MTD_FLASHMEM getClientIPParams(bool* staticIP, char const** IP, char const** netmask, char const** gateway)
		{
			*staticIP = FlashDictionary::getBool(STR_CLSTATIC, false);
			*IP       = FlashDictionary::getString(STR_CLIP, FSTR(""));
			*netmask  = FlashDictionary::getString(STR_CLNETMSK, FSTR(""));
			*gateway  = FlashDictionary::getString(STR_CLGTW, FSTR(""));
		}
		
		
		//// Access point IP parameters
		
		static void MTD_FLASHMEM setAccessPointIPParams(char const* IP, char const* netmask, char const* gateway)
		{
			FlashDictionary::setString(STR_APIP, IP);
			FlashDictionary::setString(STR_APNETMSK, netmask);
			FlashDictionary::setString(STR_APGTW, gateway);			
		}
		
		static void MTD_FLASHMEM getAccessPointIPParams(char const** IP, char const** netmask, char const** gateway)
		{
			*IP       = FlashDictionary::getString(STR_APIP, FSTR("192.168.4.1"));
			*netmask  = FlashDictionary::getString(STR_APNETMSK, FSTR("255.255.255.0"));
			*gateway  = FlashDictionary::getString(STR_APGTW, FSTR(""));
		}
		
		
		//// DHCP server parameters
		
		static void MTD_FLASHMEM setDHCPServerParams(bool enabled, char const* startIP = NULL, char const* endIP = NULL, uint32_t maxLeases = 0)
		{
			FlashDictionary::setBool(STR_DHCPDEN, enabled);
			if (startIP && endIP && maxLeases)
			{
				FlashDictionary::setString(STR_DHCPDIP1, startIP);
				FlashDictionary::setString(STR_DHCPDIP2, endIP);
				FlashDictionary::setInt(STR_DHCPDMXL, maxLeases);
			}
		}
		
		static void MTD_FLASHMEM getDHCPServerParams(bool* enabled, char const** startIP, char const** endIP, uint32_t* maxLeases)
		{
			*enabled   = FlashDictionary::getBool(STR_DHCPDEN, true);
			*startIP   = FlashDictionary::getString(STR_DHCPDIP1, FSTR("192.168.4.100"));
			*endIP     = FlashDictionary::getString(STR_DHCPDIP2, FSTR("192.168.4.110"));
			*maxLeases = FlashDictionary::getInt(STR_DHCPDMXL, 10);
		}
		
		
		//// Web Server parameters
		
		static void MTD_FLASHMEM setWebServerParams(uint16_t port)
		{
			FlashDictionary::setInt(STR_WEBPORT, port);
		}
		
		static void MTD_FLASHMEM getWebServerParams(uint16_t* port)
		{
			*port = FlashDictionary::getInt(STR_WEBPORT, 80);
		}
		
		
		//// UART parameters
		
		static void MTD_FLASHMEM setUARTParams(uint32_t baudRate, bool enableSystemOutput, SerialService serialService)
		{
			FlashDictionary::setInt(STR_BAUD, baudRate);
			FlashDictionary::setBool(STR_SYSOUT, enableSystemOutput);
			FlashDictionary::setInt(STR_UARTSRV, (int32_t)serialService);
		}
		
		static void MTD_FLASHMEM getUARTParams(uint32_t* baudRate, bool* enableSystemOutput, SerialService* serialService)
		{
			*baudRate           = FlashDictionary::getInt(STR_BAUD, 115200);
			*enableSystemOutput = FlashDictionary::getBool(STR_SYSOUT, false);
			*serialService      = (SerialService)FlashDictionary::getInt(STR_UARTSRV, (int32_t)SerialService_Console);
		}
		
		
		//// GPIO parameters
		
		struct GPIOInfo
		{
			uint32_t configured: 1, isOutput: 1, pullUp: 1, value: 1;
		};

		static void MTD_FLASHMEM setGPIOParams(uint32_t gpioNum, bool configured, bool isOutput, bool pullUp, bool value)
		{
			APtr<char> key(f_printf(FSTR("GPIO%d"), gpioNum));
			GPIOInfo info = {configured, isOutput, pullUp, value};
			FlashDictionary::setValue(key.get(), &info, sizeof(GPIOInfo));
		}
		
		static void MTD_FLASHMEM getGPIOParams(uint32_t gpioNum, bool* configured, bool* isOutput, bool* pullUp, bool* value)
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
	};



	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// Configuration helper web pages
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPWifiConfigurationResponse
	
	struct HTTPWifiConfigurationResponse : public HTTPTemplateResponse
	{
		HTTPWifiConfigurationResponse(HTTPHandler* httpHandler, char const* filename)
			: HTTPTemplateResponse(httpHandler, filename)
		{
		}
		
		virtual void MTD_FLASHMEM flush()
		{
			if (getRequest().method == HTTPHandler::Post)
			{
				// set WiFi mode
				char const* clientmode = getRequest().form[FSTR("clientmode")];
				char const* apmode     = getRequest().form[FSTR("apmode")];
				if (clientmode && apmode)
					ConfigurationManager::setWiFiMode(WiFi::ClientAndAccessPoint);
				else if (clientmode)
					ConfigurationManager::setWiFiMode(WiFi::Client);
				else if (apmode)
					ConfigurationManager::setWiFiMode(WiFi::AccessPoint);
				
				// set client mode parameters
				ConfigurationManager::setClientParams(getRequest().form[FSTR("CLSSID")],
				                                      getRequest().form[FSTR("CLPSW")]);
				
				// set access point parameters
				char const* APCH    = getRequest().form[FSTR("APCH")];
				char const* APSEC   = getRequest().form[FSTR("APSEC")];
				if (APCH && APSEC)
					ConfigurationManager::setAccessPointParams(getRequest().form[FSTR("APSSID")], 
															   getRequest().form[FSTR("APPSW")], 
															   strtol(APCH, NULL, 10),
															   (WiFi::SecurityProtocol)strtol(APSEC, NULL, 10),
															   getRequest().form[FSTR("APHSSID")] != NULL);
			}
			
			// get WiFi mode
			WiFi::Mode mode = ConfigurationManager::getWiFiMode();			
			if (mode == WiFi::Client || mode == WiFi::ClientAndAccessPoint)
				addParamStr(FSTR("clientmode"), FSTR("checked"));			
			if (mode == WiFi::AccessPoint || mode == WiFi::ClientAndAccessPoint)
				addParamStr(FSTR("apmode"), FSTR("checked"));
			
			// get client mode parameters
			char const* SSID = getRequest().query[FSTR("AP")]; // get SSID from last scan?
			char const* securityKey;
			if (!SSID)
			{				
				// get from configuration among the password
				ConfigurationManager::getClientParams(&SSID, &securityKey);
				addParamStr(FSTR("CLPSW"), securityKey);
			}
			addParamStr(FSTR("CLSSID"), SSID);
			
			// get access point parameters
			uint8_t channel;
			WiFi::SecurityProtocol securityProtocol;
			bool hiddenSSID;
			ConfigurationManager::getAccessPointParams(&SSID, &securityKey, &channel, &securityProtocol, &hiddenSSID);
			addParamStr(FSTR("APSSID"), SSID);
			addParamStr(FSTR("APPSW"), securityKey);
			APtr<char> APCHStr(f_printf(FSTR("APCH%d"), channel));
			addParamStr(APCHStr.get(), FSTR("selected"));
			APtr<char> APSECStr(f_printf(FSTR("APSEC%d"), (int32_t)securityProtocol));
			addParamStr(APSECStr.get(), FSTR("selected"));
			if (hiddenSSID)
				addParamStr(FSTR("APHSSID"), FSTR("checked"));
			
			HTTPTemplateResponse::flush();
		}
	};


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPNetworkConfigurationResponse

	struct HTTPNetworkConfigurationResponse : public HTTPTemplateResponse
	{
		HTTPNetworkConfigurationResponse(HTTPHandler* httpHandler, char const* filename)
			: HTTPTemplateResponse(httpHandler, filename)
		{
		}
		
		virtual void MTD_FLASHMEM flush()
		{
			if (getRequest().method == HTTPHandler::Post)
			{
				// set client mode IP configuration
				ConfigurationManager::setClientIPParams(getRequest().form[FSTR("staticIP")] != NULL,
													    getRequest().form[FSTR("CLIP")],
														getRequest().form[FSTR("CLMSK")],
														getRequest().form[FSTR("CLGTW")]);
														
				// set access point IP configuration
				ConfigurationManager::setAccessPointIPParams(getRequest().form[FSTR("APIP")],
														     getRequest().form[FSTR("APMSK")],
														     getRequest().form[FSTR("APGTW")]);

				// set DHCP server configuration
				if (getRequest().form[FSTR("DHCPD")] != NULL)
					ConfigurationManager::setDHCPServerParams(true,
															  getRequest().form[FSTR("startIP")],
															  getRequest().form[FSTR("endIP")],
															  strtol(getRequest().form[FSTR("maxLeases")], NULL, 10));
				else
					ConfigurationManager::setDHCPServerParams(false);
			}
			
			WiFi::Mode mode = ConfigurationManager::getWiFiMode();
			
			// get client mode IP configuration
			bool staticIP;
			char const* IP;
			char const* netmask;
			char const* gateway;
			ConfigurationManager::getClientIPParams(&staticIP, &IP, &netmask, &gateway);
			addParamStr(FSTR("DISP_CLIPCONF"), mode == WiFi::Client || mode == WiFi::ClientAndAccessPoint? FSTR("") : FSTR("disabled"));
			if (staticIP)
				addParamStr(FSTR("staticIP"), FSTR("checked"));
			addParamStr(FSTR("CLIP"), IP);
			addParamStr(FSTR("CLMSK"), netmask);
			addParamStr(FSTR("CLGTW"), gateway);
			
			// get access point IP configuration
			ConfigurationManager::getAccessPointIPParams(&IP, &netmask, &gateway);
			addParamStr(FSTR("DISP_APIPCONF"), mode == WiFi::AccessPoint || mode == WiFi::ClientAndAccessPoint? FSTR("") : FSTR("disabled"));
			addParamStr(FSTR("APIP"), IP);
			addParamStr(FSTR("APMSK"), netmask);
			addParamStr(FSTR("APGTW"), gateway);
			
			// get DHCP server configuration
			bool DHCPDEnabled;
			char const* startIP;
			char const* endIP;
			uint32_t maxLeases;
			ConfigurationManager::getDHCPServerParams(&DHCPDEnabled, &startIP, &endIP, &maxLeases);
			if (DHCPDEnabled)
				addParamStr(FSTR("DHCPD"), FSTR("checked"));
			addParamStr(FSTR("startIP"), startIP);
			addParamStr(FSTR("endIP"), endIP);
			addParamInt(FSTR("maxLeases"), maxLeases);
			
			HTTPTemplateResponse::flush();
		}
		
	};


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPServicesConfigurationResponse

	struct HTTPServicesConfigurationResponse : public HTTPTemplateResponse
	{
		HTTPServicesConfigurationResponse(HTTPHandler* httpHandler, char const* filename)
			: HTTPTemplateResponse(httpHandler, filename)
		{
		}
		
		virtual void MTD_FLASHMEM flush()
		{
			if (getRequest().method == HTTPHandler::Post)
			{
				// set Web server configuration
				char const* httpport = getRequest().form[FSTR("httpport")];
				if (httpport)
					ConfigurationManager::setWebServerParams(strtol(httpport, NULL, 10));
				
				// set UART configuration
				char const* baud = getRequest().form[FSTR("baud")];
				char const* serv = getRequest().form[FSTR("serv")];
				if (baud && serv)
					ConfigurationManager::setUARTParams(strtol(baud, NULL, 10),
														getRequest().form[FSTR("debugout")] != NULL,
														(SerialService)strtol(serv, NULL, 10));
			}
			
			// get Web server configuration
			uint16_t webPort;
			ConfigurationManager::getWebServerParams(&webPort);
			addParamInt(FSTR("httpport"), webPort);
			
			// get UART configuration
			uint32_t baudRate;
			bool enableSystemOutput;
			SerialService serialService;
			ConfigurationManager::getUARTParams(&baudRate, &enableSystemOutput, &serialService);
			addParamInt(FSTR("baud"), baudRate);
			if (enableSystemOutput)
				addParamStr(FSTR("debugout"), FSTR("checked"));
			APtr<char> serialServiceStr(f_printf(FSTR("serv%d"), (int32_t)serialService));
			addParamStr(serialServiceStr.get(), FSTR("checked"));						
			
			HTTPTemplateResponse::flush();
		}
		
	};
	

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPWiFiScanResponse

	struct HTTPWiFiScanResponse : public HTTPTemplateResponse
	{
		HTTPWiFiScanResponse(HTTPHandler* httpHandler, char const* filename)
			: HTTPTemplateResponse(httpHandler, filename)
		{
		}
		
		virtual void MTD_FLASHMEM flush()
		{
			uint32_t count = 0;
			WiFi::APInfo* infos = WiFi::getAPList(&count, true);

			LinkedCharChunks linkedChunks;
			for (uint32_t i = 0; i != count; ++i)
			{
				linkedChunks.addChunk(f_printf(FSTR("<tr> <td><a href='confwifi?AP=%s'>%s</a></td> <td>%02X:%02X:%02X:%02X:%02X:%02X</td> <td>%d</td> <td>%d</td> <td>%s</td> </tr>"), 
				                               infos[i].SSID,
											   infos[i].SSID,
											   infos[i].BSSID[0], infos[i].BSSID[1], infos[i].BSSID[2], infos[i].BSSID[3], infos[i].BSSID[4], infos[i].BSSID[5],
											   infos[i].Channel,
											   infos[i].RSSI,
											   WiFi::convSecurityProtocolToString(infos[i].AuthMode)),
									  true);
			}
			addParamCharChunks(FSTR("APS"), &linkedChunks);
			

			HTTPTemplateResponse::flush();
		}
		
	};

	
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPGPIOConfigurationResponse

	struct HTTPGPIOConfigurationResponse : public HTTPTemplateResponse
	{
		HTTPGPIOConfigurationResponse(HTTPHandler* httpHandler, char const* filename)
			: HTTPTemplateResponse(httpHandler, filename)
		{
		}
		
		virtual void MTD_FLASHMEM flush()
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
				
			LinkedCharChunks linkedChunks;
			for (uint32_t i = 0; i != 16; ++i)
			{
				if (i != 1 && i != 3 && (i < 6 || i > 11))
				{
					bool configured, isOutput, pullUp, value;
					ConfigurationManager::getGPIOParams(i, &configured, &isOutput, &pullUp, &value);
					
					linkedChunks.addChunk(f_printf(FSTR("<tr> <td>%d</td> <td><form method='POST'>"), i), true);
					linkedChunks.addChunk(f_printf(FSTR("Enabled <input type='checkbox' name='configured' value='1' onclick=\"document.getElementById('GPIO%d').disabled=!this.checked\" %s>"), i, configured? FSTR("checked"):FSTR("")), true);
					linkedChunks.addChunk(f_printf(FSTR("<fieldset class='inline' id='GPIO%d' %s>"), i, configured? FSTR(""):FSTR("disabled")), true);
					linkedChunks.addChunk(f_printf(FSTR("<select name='mode'><option value='in' %s>IN</option><option value='out' %s>OUT</option></select>"), 
					                               isOutput? FSTR(""):FSTR("selected"), 
												   isOutput? FSTR("selected"):FSTR("")), 
										  true);
					linkedChunks.addChunk(f_printf(FSTR("     PullUp <input type='checkbox' name='pullup' value='1' %s> </fieldset>"), pullUp? FSTR("checked") : FSTR("")), true);
					linkedChunks.addChunk(f_printf(FSTR("<input type='hidden' name='GPIO' value='%d'>"), i), true);
					linkedChunks.addChunk(FSTR("<input type='submit' value='Save'></form></td>"));
					if (configured)
					{
						if (isOutput)
						{
							linkedChunks.addChunk(f_printf(FSTR("<td><a href='confgpio?gpio=%d&val=%d' class='link_button2'>%s</a></td> </tr>"), i, !value, value? FSTR("HI"):FSTR("LO")), true);
						}
						else
						{
							linkedChunks.addChunk(f_printf(FSTR("<td>%s</td> </tr>"), GPIO(i).read()? FSTR("HI"):FSTR("LO")), true);
						}
					}
					else
					{
						linkedChunks.addChunk(FSTR("<td></td></tr>"));
					}
				}
			}
			addParamCharChunks(FSTR("GPIOS"), &linkedChunks);
				
			HTTPTemplateResponse::flush();
		}
		
	};
	
	
}

#endif

