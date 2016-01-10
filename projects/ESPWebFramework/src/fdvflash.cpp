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


namespace fdv
{
	

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	
	// size in Bytes
	uint32_t FUNC_FLASHMEM getFlashSize()
	{
		uint32_t flags = *((uint32_t volatile*)0x40200000);
		switch(flags >> 24 & 0xF0)
		{
			case 0:
				return 0x080000;	// 512K
			case 1:
				return 0x040000;	// 256K
			case 2:
				return 0x100000;	// 1MB
			case 3:
				return 0x200000;	// 2MB
			case 4:
				return 0x400000;	// 4MB				
		}
		return 0;	// unknown
	}

	// size in MHz
	uint32_t FUNC_FLASHMEM getFlashSpeed()
	{
		uint32_t flags = *((uint32_t volatile*)0x40200000);
		switch(flags >> 24 & 0x0F)
		{
			case 0:
				return 40;
			case 1:
				return 26;
			case 2:
				return 20;
			case 15:
				return 80;
		}
		return 0;	// unknown
	}
	

    
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
    
    
	bool FUNC_FLASHMEM isStoredInFlash(void const* ptr)
	{
		return (uint32_t)ptr >= FLASH_MAP_START;
	}
    
    

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	char FUNC_FLASHMEM getChar(char const* str, uint32_t index)
	{
		if (isStoredInFlash(str))
		{
			uint32_t u32 = ((uint32_t const*)str)[index >> 2];
			return ((char const*)&u32)[index & 0x3];
		}
		else
			return str[index];
	}

    
  	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	uint8_t FUNC_FLASHMEM getByte(void const* buffer)
	{
		return (uint8_t)getChar((char const*)buffer);
	}

	
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	char FUNC_FLASHMEM getChar(char const* str)
	{
		if (isStoredInFlash(str))
		{
			uint32_t index = (uint32_t)str & 0x3;
			str = (char const*)((uint32_t)str & 0xFFFFFFFC);  // align str
			uint32_t u32 = *((uint32_t const*)str);
			return ((char const*)&u32)[index];
		}
		else
			return *str;
	}		
	
	

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	uint16_t FUNC_FLASHMEM getWord(void const* buffer)
	{
		char const* pc = (char const*)buffer;
		return (uint8_t)getChar(pc) | ((uint8_t)getChar(pc + 1) << 8);
	}
	
	
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	uint32_t FUNC_FLASHMEM getDWord(void const* buffer)
	{
		char const* pc = (char const*)buffer;
		return (uint8_t)getChar(pc) | ((uint8_t)getChar(pc + 1) << 8) | ((uint8_t)getChar(pc + 2) << 16) | ((uint8_t)getChar(pc + 3) << 24);
	}


	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

    // should be executed into a "Critical" section
    void flashCopyMemory(void* dst, void const* src, uint32_t size)
    {
        uint8_t* bDst = (uint8_t*)dst;
        uint8_t const* bSrc = (uint8_t const*)src;
        
        uint8_t* page = new uint8_t[SPI_FLASH_SEC_SIZE];

        while (size > 0)
        {        
            // alignedDest is aligned to the start of flash page (a page is SPI_FLASH_SEC_SIZE bytes)
            uint8_t* alignedDest = (uint8_t*)((uint32_t)bDst & ~(SPI_FLASH_SEC_SIZE - 1));
            uint32_t offset = bDst - alignedDest;
            
            // load page from flash
            memcpy(page, alignedDest, SPI_FLASH_SEC_SIZE);
            
            // to optimize: copy byte by byte because we don't know if "src" is on RAM or Flash
            for (; size > 0 && offset < SPI_FLASH_SEC_SIZE; --size, ++bDst)
                page[offset++] = getByte(bSrc++);
            
            // write back to flash
            Critical critical;
            uint32_t flashAddr = (uint32_t)alignedDest - FLASH_MAP_START;
            spi_flash_erase_sector(flashAddr / SPI_FLASH_SEC_SIZE);
            spi_flash_write(flashAddr, (uint32*)page, SPI_FLASH_SEC_SIZE);            
        }
        
        delete[] page;        
    }
    

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// CharIterator

    char const* MTD_FLASHMEM CharIterator::get()
    {
        return m_str;
    }

    char MTD_FLASHMEM CharIterator::operator*()
    {
        return getChar(m_str);
    }

    CharIterator MTD_FLASHMEM CharIterator::operator++(int)
    {
        CharIterator p = *this;
        ++m_str;
        return p;
    }

    CharIterator MTD_FLASHMEM CharIterator::operator++()
    {
        ++m_str;
        return *this;
    }

    CharIterator MTD_FLASHMEM CharIterator::operator+(int32_t rhs)
    {
        return m_str + rhs;
    }

    int32_t MTD_FLASHMEM CharIterator::operator-(CharIterator const& rhs)
    {
        return m_str - rhs.m_str;
    }

    bool MTD_FLASHMEM CharIterator::operator==(char const* rhs)
    {
        return getChar(m_str) == *rhs;
    }

    bool MTD_FLASHMEM CharIterator::operator==(CharIterator const& rhs)
    {
        return m_str == rhs.m_str;
    }

    bool MTD_FLASHMEM CharIterator::operator!=(char const* rhs)
    {
        return getChar(m_str) != *rhs;
    }

    bool MTD_FLASHMEM CharIterator::operator!=(CharIterator const& rhs)
    {
        return m_str != rhs.m_str;
    }
		
	
}