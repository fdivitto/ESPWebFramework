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


#ifndef _FDVWIFI_H_
#define _FDVWIFI_H_



extern "C"
{
	#include "esp_common.h"    
	#include "freertos/FreeRTOS.h"
	#include "freertos/task.h"
	#include "lwip/ip_addr.h"
	#include "lwip/sockets.h"
	#include "lwip/dns.h"
	#include "lwip/netdb.h"
	#include "lwip/api.h"
	#include "lwip/netbuf.h"
	#include "udhcp/dhcpd.h"	
}


#include "fdvserial.h"
#include "fdvsync.h"
#include "fdvflash.h"
#include "fdvtask.h"


extern "C"
{
bool wifi_station_dhcpc_start(void);
bool wifi_station_dhcpc_stop(void);
bool dhcp_set_info(dhcp_info *if_dhcp);
}	

	

namespace fdv
{
	
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// WiFi
	
	struct WiFi
	{
			
		enum Mode
		{
			Client               = STATION_MODE,
			AccessPoint          = SOFTAP_MODE,
			ClientAndAccessPoint = STATIONAP_MODE			
		};
		
		enum SecurityProtocol
		{
			Open          = AUTH_OPEN,
			WEP           = AUTH_WEP,
			WPA_PSK       = AUTH_WPA_PSK,
			WPA2_PSK      = AUTH_WPA2_PSK,
			WPA_WPA2_PSK  = AUTH_WPA_WPA2_PSK
		};

		static Mode ICACHE_FLASH_ATTR setMode(Mode mode)
		{
			DisableInterrupts();
			wifi_set_opmode(mode);
			EnableInterrupts();
		}
		
		static Mode ICACHE_FLASH_ATTR getMode()
		{
			Mode mode = (Mode)wifi_get_opmode();
			return mode;
		}

		// setMode must be called with AccessPoint or ClientAndAccessPoint
		// note: make sure there is enough stack space free otherwise mail cause reset (fatal exception)!
		// channel: 1..13
		static void ICACHE_FLASH_ATTR configureAccessPoint(char const* SSID, char const* securityKey, uint8_t channel, SecurityProtocol securityProtocol = WPA2_PSK, bool hiddenSSID = false)
		{									
			softap_config* pconfig = (softap_config*)zalloc(sizeof(softap_config));	// avoid to use stack
			wifi_softap_get_config(pconfig);
			strcpy((char *)pconfig->ssid, SSID);
			pconfig->ssid_len = strlen(SSID);
			strcpy((char *)pconfig->password, securityKey);
			pconfig->channel = channel;
			pconfig->authmode = securityProtocol;
			pconfig->ssid_hidden = (uint8)hiddenSSID;
			//printf("-----> %d\n\r", pconfig->max_connection);
			DisableInterrupts();
			wifi_softap_set_config(pconfig);
			EnableInterrupts();
			free(pconfig);
		}
		
		// setMode must be called with Client or ClientAndAccessPoint
		static void ICACHE_FLASH_ATTR configureClient(char const* SSID, char const* securityKey)
		{
			station_config* pconfig = (station_config*)zalloc(sizeof(station_config));	// avoid to use stack
			strcpy((char *)pconfig->ssid, SSID);
			strcpy((char *)pconfig->password, securityKey);
			DisableInterrupts();
			wifi_station_disconnect();
			wifi_station_set_config(pconfig);
			wifi_station_connect();
			EnableInterrupts();
			free(pconfig);
		}

		
				
	};
	

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// IP
	
	struct IP
	{

		enum Network
		{
			ClientNetwork      = 0,
			AccessPointNetwork = 1
		};
	
		// don't need to call configureDHCP
		static void ICACHE_FLASH_ATTR configureStatic(Network network, char const* IP, char const* netmask, char const* gateway)
		{
			ip_info info;
			info.ip.addr      = ipaddr_addr(IP);
			info.netmask.addr = ipaddr_addr(netmask);
			info.gw.addr      = ipaddr_addr(gateway);
			DisableInterrupts();
			if (network == ClientNetwork)
				wifi_station_dhcpc_stop();
			wifi_set_ip_info(network, &info);
			EnableInterrupts();
		}
		
		// applied only to ClientNetwork
		static void ICACHE_FLASH_ATTR configureDHCP(Network network)
		{
			if (network == ClientNetwork)
			{
				DisableInterrupts();
				wifi_station_dhcpc_start();
				EnableInterrupts();
			}
		}
		
	};
	
	
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// DHCPServer
	
	struct DHCPServer
	{
		
		// warn: each IP in the range requires memory!
		static void ICACHE_FLASH_ATTR configure(char const* startIP, char const* endIP, uint32_t maxLeases)
		{		
			dhcp_info* pinfo = (dhcp_info*)zalloc(sizeof(dhcp_info));	// avoid to use stack
			pinfo->start_ip      = ipaddr_addr(startIP);
			pinfo->end_ip        = ipaddr_addr(endIP);
			pinfo->max_leases    = maxLeases;
			pinfo->auto_time     = 60;
			pinfo->decline_time  = 60;
			pinfo->conflict_time = 60;
			pinfo->offer_time    = 60;
			pinfo->min_lease_sec = 60;
			dhcp_set_info(pinfo);
			free(pinfo);
			udhcpd_start();
		}
    };


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// TCPServer
	
	template <typename ConnectionHandler>
	struct TCPServer
	{
		
		static uint32_t const ACCEPTWAITTIMEOUTMS = 35000;
		
		
		TCPServer(uint16_t port, uint16_t maxThreads = 1, uint16_t threadsStackDepth = 512)
			: m_threadsStackDepth(threadsStackDepth), m_threadResourcesCounter(maxThreads)
		{
			m_netconn = netconn_new(NETCONN_TCP);
			netconn_bind(m_netconn, IP_ADDR_ANY, port);	// todo: allow other choices other than IP_ADDR_ANY
			netconn_listen(m_netconn);
			m_listenerTask = new MethodTask<TCPServer, &TCPServer::listenerTask>(*this, 512);
		}
		
		virtual ~TCPServer()
		{
			delete m_listenerTask;
			netconn_delete(m_netconn);
		}
		
		void listenerTask()
		{
			// todo: causes crash if there is another incoming connection (already accepted or not accepted) which sends data!!
			while (true)
			{
				if (m_threadResourcesCounter.get())
				{
					printf("Wait for accept\n\r");
					netconn* conn;
					if (netconn_accept(m_netconn, &conn) == ERR_OK)
					{
						printf("Connected\n\r");
						ConnectionHandler* connectionHandler = new ConnectionHandler;
						connectionHandler->start(m_threadsStackDepth, conn, m_threadResourcesCounter);
					}
					else
						m_threadResourcesCounter.release();
				}
			}
			/*
			while (true)
			{
				netconn* conn;
				if (netconn_accept(m_netconn, &conn) == ERR_OK)
				{
					printf("Connected, waiting for free thread\n\r");
					if (m_threadResourcesCounter.get(ACCEPTWAITTIMEOUTMS))
					{
						ConnectionHandler* connectionHandler = new ConnectionHandler;
						connectionHandler->start(m_threadsStackDepth, conn, m_threadResourcesCounter);
					}
					else
					{
						printf("Timeout! No thread is available\n\r");
						netconn_shutdown(conn, 1, 1);
						netconn_close(conn);
						netconn_delete(conn);
						printf("Connection deleted\n\r");
					}
				}
			}
			*/
		}
		
	private:
	
		uint16_t            m_threadsStackDepth;
		netconn*            m_netconn;
		Task*               m_listenerTask;
		uint16_t            m_maxThreads;
		ResourceCounter     m_threadResourcesCounter;
	};
	
	
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// TCPConnectionHandler
	
	struct TCPConnectionHandler : public Task
	{
		
		TCPConnectionHandler()
			: Task(256, 2, true)	// create task as suspended
		{
		}
		
		void start(uint16_t stackDepth, netconn* conn, ResourceCounter& threadsResourcesCounter)
		{
			m_conn = conn;
			m_threadResourcesCounter = &threadsResourcesCounter;
			setStackDepth(stackDepth);
			resume();
		}
		
		void exec()
		{
			while (true)
			{
				printf("Waiting for data\n\r");
				netbuf* buf;
				if (netconn_recv(m_conn, &buf) == ERR_OK)
				{
					char const* data;
					uint16_t len;
					do
					{
						netbuf_data(buf, (void**)&data, &len);
						printf("%d -> ", len);
						while (len--)
							printf("%c", *data++);
					} while (netbuf_next(buf) >= 0);
					printf("\n\r");
					netbuf_delete(buf);
				}				
				else
					break;
			}
			printf("disconnected\n\r");
			netconn_shutdown(m_conn, 1, 1);
			netconn_close(m_conn);
			netconn_delete(m_conn);
			m_threadResourcesCounter->release();
			delete this;	// this will free heap for the object and remove the RTOS vTaskDelete
		}
		
	private:
		netconn*         m_conn;
		ResourceCounter* m_threadResourcesCounter;
	};
    
	
	
	
}


#endif






