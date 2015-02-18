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

// disable macros like "read"
#define LWIP_POSIX_SOCKETS_IO_NAMES 0

extern "C"
{
    #include "esp_common.h"    
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
	#include "stdarg.h"
}

#include "fdvserial.h"
#include "fdvsync.h"
#include "fdvflash.h"
#include "fdvtask.h"
#include "fdvnetwork.h"



struct Task1 : fdv::Task
{

	Task1(fdv::Serial* serial)
		: fdv::Task(1024), m_serial(serial)
	{		
	}

	fdv::Serial* m_serial;
	
	
	void ICACHE_FLASH_ATTR run()
	{
		
		
		while (1)
		{
			if (m_serial->waitForData())
			{
				uint8_t c = m_serial->read();
				switch (c)
				{
					case 'h':
						m_serial->writeln("Tests:\r\n");
						m_serial->writeln("h    = help");
						m_serial->writeln("r    = reset");	
						m_serial->writeln("0    = format flash filesystem");
						m_serial->writeln("1    = start AccessPoint mode");
						m_serial->writeln("2    = start Client mode static IP");
						m_serial->writeln("3    = start Client mode dynamic IP");
						break;
					case 'r':
						system_restart();
						break;
					case '0':
						fdv::FlashFileSystem::format();
						m_serial->writeln("Ok");
						break;
					case '1':
						// Access point with DHCP server enabled
						fdv::WiFi::setMode(fdv::WiFi::AccessPoint);
						fdv::WiFi::configureAccessPoint("MyESP", "myesp111", 6);
						fdv::IP::configureStatic(fdv::IP::AccessPointNetwork, "192.168.5.1", "255.255.255.0", "192.168.5.1");
						fdv::DHCPServer::configure("192.168.5.100", "192.168.5.110", 10);
						m_serial->writeln("Ok");
						break;
					case '2':
						// Client mode with static IP
						fdv::WiFi::setMode(fdv::WiFi::Client);
						fdv::WiFi::configureClient("OSPITI", "31415926");
						fdv::IP::configureStatic(fdv::IP::ClientNetwork, "192.168.1.199", "255.255.255.0", "192.168.1.1");						
						m_serial->writeln("Ok");
						break;
					case '3':
						// Client mode with dynamic IP
						fdv::WiFi::setMode(fdv::WiFi::Client);
						fdv::WiFi::configureClient("OSPITI", "31415926");
						fdv::IP::configureDHCP(fdv::IP::ClientNetwork);
						m_serial->writeln("Ok");
						break;
				}
			}
		}		
	}
	
};



struct MainTask : fdv::Task
{
	void ICACHE_FLASH_ATTR run()
	{
		//fdv::DisableStdOut(); 
		fdv::DisableWatchDog();
		
		fdv::HardwareSerial serial(115200, 128);
		
		Task1 task1(&serial);
		
		suspend();
	}
};


extern "C" void /*ICACHE_FLASH_ATTR*/ user_init(void) 
{
	new MainTask;	// never destroy!
}

