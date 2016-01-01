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
	
	class ConfigurationManager
	{		
		
		template <typename HTTPCustomServer_T>
		static void MTD_FLASHMEM applyDelayed()
		{
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
		
		template <typename HTTPCustomServer_T>
		static void MTD_FLASHMEM applyAll()
		{
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
		template <typename HTTPCustomServer_T>
		static void MTD_FLASHMEM applyWebServer()
		{
			// Web Server
			uint16_t webPort;
			getWebServerParams(&webPort);
			new HTTPCustomServer_T(webPort);
		}

        // can be re-applied
        static void applyDateTime();
		
		static void MTD_FLASHMEM restore();
		
		
		//// WiFi settings
		
		static void setWiFiMode(WiFi::Mode value);
		
		static WiFi::Mode getWiFiMode();

		
		//// Access Point mode parameters
		
		static void setAccessPointParams(char const* SSID, char const* securityKey, uint8_t channel, WiFi::SecurityProtocol securityProtocol, bool hiddenSSID);
		
		static void getAccessPointParams(char const** SSID, char const** securityKey, uint8_t* channel, WiFi::SecurityProtocol* securityProtocol, bool* hiddenSSID);
		
		
		//// Client mode parameters
		
		static void setClientParams(char const* SSID, char const* securityKey);
		
		static void getClientParams(char const** SSID, char const** securityKey);
		
		
		//// Client mode IP parameters
		
		// IP, netmask, gateway valid only if staticIP = true
		static void setClientIPParams(bool staticIP, char const* IP, char const* netmask, char const* gateway);
		
		// IP, netmask, gateway valid only if staticIP = true
		static void getClientIPParams(bool* staticIP, char const** IP, char const** netmask, char const** gateway);
		
		
		//// Access point IP parameters
		
		static void setAccessPointIPParams(char const* IP, char const* netmask, char const* gateway);
		
		static void getAccessPointIPParams(char const** IP, char const** netmask, char const** gateway);
		
		
		//// DHCP server parameters
		
		static void setDHCPServerParams(bool enabled, char const* startIP = NULL, char const* endIP = NULL);
		
		static void getDHCPServerParams(bool* enabled, char const** startIP, char const** endIP);
        
        
        //// Routing
        
        static void setRouting(bool enabled);
        
        static void getRouting(bool* enabled);
		
		
        //// DNS parameters
        
        static void setDNSParams(IPAddress DNS1, IPAddress DNS2);
        
        static void getDNSParams(IPAddress* DNS1, IPAddress* DNS2);
        
        
		//// Web Server parameters
		
		static void setWebServerParams(uint16_t port);
		
		static void getWebServerParams(uint16_t* port);
		
		
		//// UART parameters
		
		static void setUARTParams(uint32_t baudRate, bool enableSystemOutput, SerialService serialService);
		
		static void getUARTParams(uint32_t* baudRate, bool* enableSystemOutput, SerialService* serialService);
		
#if (FDV_INCLUDE_SERIALCONSOLE == 1)
		static SerialConsole* getSerialConsole();
#endif
		
#if (FDV_INCLUDE_SERIALBINARY == 1)
		static SerialBinary* getSerialBinary();
#endif
		
		
		//// GPIO parameters
		
		struct GPIOInfo
		{
			uint32_t configured: 1, isOutput: 1, pullUp: 1, value: 1;
		};

		static void setGPIOParams(uint32_t gpioNum, bool configured, bool isOutput, bool pullUp, bool value);
		
		static void getGPIOParams(uint32_t gpioNum, bool* configured, bool* isOutput, bool* pullUp, bool* value);
        
        
        //// Date-time parameters
        
        static void setDateTimeParams(int8_t timezoneHours, uint8_t timezoneMinutes, char const* defaultNTPServer);
        
        static void getDateTimeParams(int8_t* timezoneHours, uint8_t* timezoneMinutes, char const** defaultNTPServer);
        
        static DateTime getBootDateTime(bool set = false, DateTime const& value = DateTime());        
        static void getUpTimeStr(char* outbuf);
		
		
	private:
#if (FDV_INCLUDE_SERIALCONSOLE == 1)
		static SerialConsole* s_serialConsole;
#endif
#if (FDV_INCLUDE_SERIALBINARY == 1)
		static SerialBinary*  s_serialBinary;
#endif
	};



	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// Configuration helper web pages
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

    
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
    // HTTPHelperConfiguration
    // Common configuration GET and POST handling routines
    
    struct HTTPHelperConfiguration
    {
        static void getWiFiMode(HTTPTemplateResponse* response);
        static void setWiFiMode(HTTPTemplateResponse* response);

        static void getClientModeWiFiParams(HTTPTemplateResponse* response);
        static void setClientModeWiFiParams(HTTPTemplateResponse* response);
        
        static void getClientModeIP(HTTPTemplateResponse* response);
        static void setClientModeIP(HTTPTemplateResponse* response);
        
        static void getDNSServer(HTTPTemplateResponse* response, IPAddress::IPAddressStr& DNS1str, IPAddress::IPAddressStr& DNS2str);
        static void setDNSServer(HTTPTemplateResponse* response);

        static void getDateTime(HTTPTemplateResponse* response, char* dateStr, char* timeStr);        
        static void setDateTime(HTTPTemplateResponse* response);
        
        static void getUART(HTTPTemplateResponse* response);
        static void setUART(HTTPTemplateResponse* response);

        static void getAPWiFiParams(HTTPTemplateResponse* response, APtr<char>& APCHStr, APtr<char>& APSECStr);
        static void setAPWiFiParams(HTTPTemplateResponse* response);
        
        static void getAPModeIP(HTTPTemplateResponse* response);
        static void setAPModeIP(HTTPTemplateResponse* response);
        
        static void getDHCPServer(HTTPTemplateResponse* response);
        static void setDHCPServer(HTTPTemplateResponse* response);

        static void getRouting(HTTPTemplateResponse* response);
        static void setRouting(HTTPTemplateResponse* response);
    };
    

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPWifiConfigurationResponse
	
	struct HTTPWifiConfigurationResponse : public HTTPTemplateResponse
	{
        HTTPWifiConfigurationResponse(HTTPHandler* httpHandler, char const* filename);
        
        virtual void flush();
	};


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPNetworkConfigurationResponse

	struct HTTPNetworkConfigurationResponse : public HTTPTemplateResponse
	{
		HTTPNetworkConfigurationResponse(HTTPHandler* httpHandler, char const* filename);
		
		virtual void flush();		
	};


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPServicesConfigurationResponse

	struct HTTPServicesConfigurationResponse : public HTTPTemplateResponse
	{
		HTTPServicesConfigurationResponse(HTTPHandler* httpHandler, char const* filename);
		
		virtual void flush();
	};
	

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPWiFiScanResponse

	struct HTTPWiFiScanResponse : public HTTPTemplateResponse
	{
		HTTPWiFiScanResponse(HTTPHandler* httpHandler, char const* filename);
		
		virtual void flush();
	};

    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPWiFiScanResponseHTMLRows
    // Helper for HTTPWizardConfigurationResponse

	struct HTTPWiFiScanResponseHTMLRows : public HTTPResponse
	{
		HTTPWiFiScanResponseHTMLRows(HTTPHandler* httpHandler);
		
		virtual void flush();
	};
    
	
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPGPIOConfigurationResponse

	struct HTTPGPIOConfigurationResponse : public HTTPTemplateResponse
	{
		HTTPGPIOConfigurationResponse(HTTPHandler* httpHandler, char const* filename);
		
		virtual void flush();		
	};



	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPTimeConfigurationResponse

	struct HTTPTimeConfigurationResponse : public HTTPTemplateResponse
	{
		HTTPTimeConfigurationResponse(HTTPHandler* httpHandler, char const* filename);
		
		virtual void flush();
	};

    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPWizardConfigurationResponse

	struct HTTPWizardConfigurationResponse : public HTTPTemplateResponse
	{
		HTTPWizardConfigurationResponse(HTTPHandler* httpHandler, char const* filename);
		
		virtual void flush();
	};
    

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
    // DefaultHTTPHandler
    

    class DefaultHTTPHandler : public HTTPHandler
    {
        
    public:
        
        DefaultHTTPHandler()
        {
            static const Route routes[] =
            {
                {FSTR("/"),	          (PageHandler)&DefaultHTTPHandler::get_home},
                {FSTR("/confwizard"), (PageHandler)&DefaultHTTPHandler::get_confwizard},
                {FSTR("/confwifi"),   (PageHandler)&DefaultHTTPHandler::get_confwifi},
                {FSTR("/wifiscan"),   (PageHandler)&DefaultHTTPHandler::get_wifiscan},
                {FSTR("/confnet"),    (PageHandler)&DefaultHTTPHandler::get_confnet},
                {FSTR("/confserv"),   (PageHandler)&DefaultHTTPHandler::get_confserv},
                {FSTR("/confgpio"),   (PageHandler)&DefaultHTTPHandler::get_confgpio},
                {FSTR("/conftime"),   (PageHandler)&DefaultHTTPHandler::get_conftime},
                {FSTR("/reboot"),     (PageHandler)&DefaultHTTPHandler::get_reboot},
                {FSTR("/restore"),    (PageHandler)&DefaultHTTPHandler::get_restore},
                {FSTR("/wifiscan2"),  (PageHandler)&DefaultHTTPHandler::get_wifiscan2},
                {FSTR("*"),           (PageHandler)&DefaultHTTPHandler::get_all},
            };
            setRoutes(routes, sizeof(routes) / sizeof(Route));
        } 
        
        virtual void MTD_FLASHMEM dispatch()
        {
#if (FDV_INCLUDE_SERIALBINARY == 1)            
            if (ConfigurationManager::getSerialBinary() && ConfigurationManager::getSerialBinary()->isReady())
            {
                StringList* routes = ConfigurationManager::getSerialBinary()->getHTTPRoutes();
                if (routes)
                {                
                    for (uint32_t i = 0; i != routes->size(); ++i)
                    {
                        if (f_strcmp(FSTR("*"), routes->getItem(i)) == 0 || t_strcmp(getRequest().requestedPage, CharIterator(routes->getItem(i))) == 0)
                        {
                            ConfigurationManager::getSerialBinary()->send_CMD_HTTPREQUEST(i, this);
                            return;
                        }
                    }
                }
            }
#endif            
            HTTPHandler::dispatch();
        }
        
        void MTD_FLASHMEM get_home()
        {
            HTTPTemplateResponse response(this, FSTR("home.html"));
            response.flush();
        }

        void MTD_FLASHMEM get_confwifi()
        {
            HTTPWifiConfigurationResponse response(this, FSTR("configwifi.html"));
            response.flush();
        }

        void MTD_FLASHMEM get_wifiscan()
        {
            HTTPWiFiScanResponse response(this, FSTR("wifiscan.html"));
            response.flush();
        }

        void MTD_FLASHMEM get_wifiscan2()
        {
            HTTPWiFiScanResponseHTMLRows response(this);
            response.flush();
        }

        void MTD_FLASHMEM get_confnet()
        {
            HTTPNetworkConfigurationResponse response(this, FSTR("confignet.html"));
            response.flush();
        }

        void MTD_FLASHMEM get_confserv()
        {
            HTTPServicesConfigurationResponse response(this, FSTR("confserv.html"));
            response.flush();
        }

        void MTD_FLASHMEM get_confgpio()
        {
            HTTPGPIOConfigurationResponse response(this, FSTR("confgpio.html"));
            response.flush();
        }

        void MTD_FLASHMEM get_conftime()
        {
            HTTPTimeConfigurationResponse response(this, FSTR("conftime.html"));
            response.flush();
        }
        
        void MTD_FLASHMEM get_reboot()
        {
            HTTPTemplateResponse response(this, FSTR("reboot.html"));
            reboot(3000);	// reboot in 3s
            response.flush();
        }

        void MTD_FLASHMEM get_restore()
        {
            if (getRequest().method == HTTPHandler::Get)
            {
                HTTPTemplateResponse response(this, FSTR("restore.html"));
                response.flush();
            }
            else
            {
                ConfigurationManager::restore();
                get_reboot();
            }
        }
        
        void MTD_FLASHMEM get_confwizard()
        {
            HTTPWizardConfigurationResponse response(this, FSTR("confwizard.html"));
            response.flush();
        }
        
        void MTD_FLASHMEM get_all()
        {
            HTTPStaticFileResponse response(this, getRequest().requestedPage);
            response.flush();
        }		

    };
	
	
}

#endif

