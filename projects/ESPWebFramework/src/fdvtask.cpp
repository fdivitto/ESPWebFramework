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


#include "fdv.h"

extern "C"
{
	#include "freertos/semphr.h"
	#include "lwip/mem.h"
}





namespace fdv
{


    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    // Task

    MTD_FLASHMEM Task::Task(bool suspended, uint16_t stackDepth, uint32_t priority)
        : m_stackDepth(stackDepth), m_priority(priority), m_handle(NULL), m_suspended(true)
    {
        if (!suspended)
            resume();			
    }

    
    // call only when "suspended" in constructor is true and before resume()
    void MTD_FLASHMEM Task::setStackDepth(uint16_t stackDepth)
    {
        m_stackDepth = stackDepth;
    }
    
    
    void  Task::suspend()
    {
        m_suspended = true;
        vTaskSuspend(m_handle);
    }
    
    xTaskHandle MTD_FLASHMEM Task::getCurrentTaskHandle()
    {
        return xTaskGetCurrentTaskHandle();
    }
    
    // may be not in synch with Task::suspend() or Task::resume(). Unfortunately we don't have eTaskGetState!
    bool MTD_FLASHMEM Task::suspended()
    {        
        return m_suspended;
    }
            
    
    void MTD_FLASHMEM Task::terminate()
    {
        vTaskDelete(m_handle);
    }    
    
    
    void MTD_FLASHMEM Task::resume()
    {
        if (m_handle)
            vTaskResume(m_handle);
        else
            xTaskCreate(entry, (const signed char*)"", m_stackDepth, this, m_priority, &m_handle);			
        m_suspended = false;
    }
    
        
    void STC_FLASHMEM Task::delay(uint32_t ms)
    {
        vTaskDelay(ms / portTICK_RATE_MS);
    }
    
    
    // task min touched free stack (in bytes)
    uint32_t STC_FLASHMEM Task::getMinFreeStack()
    {
        return uxTaskGetStackHighWaterMark(NULL) * 4;
    }
    
        
    // global free heap (in bytes)
    uint32_t STC_FLASHMEM Task::getFreeHeap()
    {
        return system_get_free_heap_size();
    }
    
    
    void STC_FLASHMEM Task::entry(void* params)
    {
        static_cast<Task*>(params)->exec();
        vTaskSuspend(NULL);
    }

    
}

