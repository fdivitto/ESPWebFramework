/*
# Created by Fabrizio Di Vittorio (fdivitto@gmail.com)
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

#ifndef _FDVTASK_H_
#define _FDVTASK_H_

extern "C"
{
    #include "esp_common.h"    
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
	#include "stdarg.h"
}



namespace fdv
{
	
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	// Task
	// An abstract wrapper for FreeRTOS task
	
	class Task
	{
	public:
		
		Task(uint16_t stackDepth = 256, uint32_t priority = 2)
		{
			xTaskCreate(entry, (const signed char*)"", stackDepth, this, priority, &m_handle);
		}
		
		~Task()
		{
			vTaskDelete(m_handle);
		}		
		
		void suspend()
		{
			vTaskSuspend(m_handle);
		}
		
		void resume()
		{
			vTaskResume(m_handle);
		}
		
		void delay(uint32_t ms)
		{
			vTaskDelay(ms / portTICK_RATE_MS);
		}
		
	public:
	
		virtual void run() = 0;
		

	private:
	
		static void ICACHE_FLASH_ATTR entry(void* params)
		{
			static_cast<Task*>(params)->run();
		}
		
	private:
		xTaskHandle m_handle;
		
	};
	
	
}



#endif