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

#ifndef _FDVTASK_H_
#define _FDVTASK_H_


#include "fdv.h"


namespace fdv
{
	
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	// Task
	// An abstract wrapper for FreeRTOS task
	// Child class destructor should take care of call terminate() to destroy the task.
	//
	// Example:
	//
	// struct MainTask : fdv::Task
	// {
	//   void MTD_FLASHMEM exec()
	//   {
	//     fdv::DisableStdOut();
	//     fdv::DisableWatchDog();		
	//     fdv::HardwareSerial serial(115200, 128);		
	//     Task1 anotherTask(false);  // creates another task		
	//     suspend();
	//   }
	// };

	
	class Task
	{
	public:
		
		Task(bool suspended = true, uint16_t stackDepth = 256, uint32_t priority = 2);		
		void setStackDepth(uint16_t stackDepth);		
		void suspend();		
		void terminate();		
		void resume();
        bool suspended();
		static void delay(uint32_t ms);
		static uint32_t getMinFreeStack();
		static uint32_t getFreeHeap();
		
	public:
	
		virtual void exec() = 0;
		
	private:
	
		static void entry(void* params);
		
	private:
    
		uint16_t    m_stackDepth;
		uint32_t    m_priority;
		xTaskHandle m_handle;
        bool        m_suspended;
		
	};


	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	// MethodTask
	// A way to execute different tasks in different methods of the same class
	//
	// Example:
	// struct MyClass
	// {
	//   MyClass()
	//   {		
	//      m_task1 = new MethodTask<MyClass, &MyClass::task1>(this, false);
	//      m_task2 = new MethodTask<MyClass, &MyClass::task2>(this, false);
	//   }
	//   void task1()
	//   {
	//      ...
	//   }
	//   void task2()
	//   {
	//      ...
	//   }
	//   Task* m_task1;
	//   Task* m_task2;
	// };
	
	
	template <typename T, void (T::*Method)()>
	class MethodTask : public Task
	{
	public:
		MethodTask(T* object = NULL, bool suspended = true, uint16_t stackDepth = 256, uint32_t priority = 2)
			: Task(suspended, stackDepth, priority), m_object(object)
		{
		}
		
		void MTD_FLASHMEM setObject(T* object)
		{
			m_object = object;
		}
		
		void exec()
		{
			(m_object->*Method)();
		}
	private:
		T* m_object;
	};


	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	// asyncExec
	// creates a temporary task to execute the specified function
	//
	// Example:
	//   void myfunc()
	//   {
	//      ...
	//   }
	//
	//   asyncExec<myfunc>();
	
	
	template <void (*FP)()>
	void TMTD_FLASHMEM asyncExec_(void* params)
	{		
		FP();
		vTaskDelete(NULL);
	}
	
	template <void (*FP)()>
	void TMTD_FLASHMEM asyncExec(uint32_t stackDepth = 256, uint32_t priority = 2)
	{
		xTaskHandle handle;
		xTaskCreate(asyncExec_<FP>, (const signed char*)"", stackDepth, NULL, priority, &handle);
	}
	
	
}



#endif