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

#ifndef _FDVFLASH_H_
#define _FDVFLASH_H_

extern "C"
{
    #include "esp_common.h"    
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
}


#include "fdvsync.h"
#include "fdvserial.h"


#define ICACHE_RODATA_ATTR __attribute__((section(".irom.text")))
#define ICACHE_STORE_ATTR __attribute__((aligned(4)))


// Flash from 0x0 to 0x8000      mapped to 0x40100000, len = 0x8000 (32KBytes)    - ".text"
// Flash from 0x40000 to 0x7C000 mapped to 0x40240000, len = 0x3C000 (240KBytes)  - ".irom0.text"
//
// We use flash from 0x14000 for a maximum size of 180KBytes (usable in blocks of 4K)
static uint32_t const FLASHDATABASE   = 0x14000;





namespace fdv
{

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	// FlashReadonlyDataRead
	// Example:
	//
	// char const ICACHE_STORE_ATTR ICACHE_RODATA_ATTR STR2[] = "Stored in flash!\r\n";
	//
	// To read use:
	//
	// char str[sizeof(STR2)];
	// FlashReadonlyDataRead(STR2, str, sizeof(STR2));
	// serial.write(buf);
	inline void FlashReadonlyDataRead(void const* source, void* dest, uint32_t size)
	{
		DisableInterrupts();
		spi_flash_read((uint32_t)source - 0x40240000 + 0x40000, (uint32*)dest, size);
		EnableInterrupts();		
	}
	

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	// FlashAllocator
	// Used internally by FlashValue
	
	struct FlashAllocator
	{
		template <typename T>
		static uint32_t allocate(uint32_t itemsCount)
		{
			uint32_t ret = s_pos;
			s_pos += getSectorsCount<T>(itemsCount) * SPI_FLASH_SEC_SIZE;
			return ret;
		}
		
		template <typename T>
		static uint16_t getSectorsCount(uint32_t itemsCount)
		{
			return (sizeof(T) * itemsCount + SPI_FLASH_SEC_SIZE - 1) / SPI_FLASH_SEC_SIZE;
		}

	private:
		static uint32_t s_pos;
	};

	
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	// FlashValue
	//
	// Example:
	//
	// struct MyStore
	// {
	//   char nome[16];
	//   char cognome[16];
	//   uint32_t seq;
	// };
	//
	//
	// fdv::FlashValue<MyStore> mystore;
	//
	// -> write
	//	 MyStore t = mystore;
	//	 strcpy(t.nome, "Fabrizio");
	// 	 strcpy(t.cognome, "Di Vittorio");
	//   t.seq++;
	//   mystore = t;
	//
	// -> recall
	//   MyStore t = mystore;
	//   printf(t.nome);
	//   printf(t.cognome);
	
	template <typename T>
	struct FlashValue
	{
		FlashValue()
		{
			m_data = FlashAllocator::allocate<T>(1);
		}

		explicit FlashValue(T const& value)
		{
			m_data = FlashAllocator::allocate<T>(1);
			set(value);
		}

		operator const T() const
		{
			return get();
		}

		void operator = (T const& value)
		{
			set(value);
		}

	private:

		void set(T const& value)
		{
			DisableInterrupts();
			for (uint16_t i = 0; i != FlashAllocator::getSectorsCount<T>(1); ++i)
				spi_flash_erase_sector(m_data / SPI_FLASH_SEC_SIZE + i);			
			spi_flash_write((uint32_t)m_data, (uint32*)&value, sizeof(T));
			EnableInterrupts();
		}

		T const get() const
		{
			T value;
			DisableInterrupts();
			spi_flash_read((uint32_t)m_data, (uint32*)&value, sizeof(T));
			EnableInterrupts();		
			return value;
		}

	private:

		uint32_t m_data;
	};

	
	
	
}


#endif