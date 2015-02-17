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




struct Task1 : fdv::Task
{

	Task1(fdv::Serial* serial)
		: m_serial(serial)
	{		
	}

	fdv::Serial* m_serial;

	struct MyStore
	{
		char nome[16];
		char cognome[16];
		uint32_t seq;
	};

	void ICACHE_FLASH_ATTR run()
	{
		fdv::FlashValue<MyStore> mystore;
		while (1)
		{
			if (m_serial->waitForData())
			{
				uint8_t c = m_serial->read();
				switch (c)
				{
					case 'h':
						m_serial->writeln("Comandi disponibili:");
						m_serial->writeln("h    = help");
						m_serial->writeln("r    = reset");	
						m_serial->writeln("1..9 = test 1 a 9");	
						break;
					case 'r':
						system_restart();
						break;
					case '1':
						{
							MyStore t = mystore;
							strcpy(t.nome, "Fabrizio");
							strcpy(t.cognome, "Di Vittorio");
							t.seq++;
							mystore = t;
							break;
						}
					case '2':
						{
							MyStore t = mystore;
							m_serial->writeln(t.nome);
							m_serial->writeln(t.cognome);
							m_serial->writeUInt32(t.seq); m_serial->writeNewLine();
							break;
						}
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
		fdv::DisableStdOut();
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

