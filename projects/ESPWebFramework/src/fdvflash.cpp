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
    void Cache_Read_Enable(uint32 odd_even, uint32 mb_count, uint32 unk);
}


namespace fdv
{
	

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	
	// size in Bytes
	uint32_t FUNC_FLASHMEM getFlashSize()
	{
		uint32_t flags = *((uint32_t volatile*)FLASH_MAP_START);
		switch(flags >> 24 & 0xF0)
		{
			case 0x00:
				return 0x080000;	// 512K - 4mbit
			case 0x10:
				return 0x040000;	// 256K - 2mbit
			case 0x20:
				return 0x100000;	// 1MB  - 8mbit
			case 0x30:
				return 0x200000;	// 2MB  - 16mbit
			case 0x40:
				return 0x400000;	// 4MB  - 32mbit
            case 0x50:
                return 0x200000;    // 2MB  - 16mbit
            case 0x60:
            case 0x70:
                return 0x400000;    // 4MB  - 32mbit
                
		}
		return 0;	// unknown
	}
    
    
    // Bank 0..3 (each bank maps 1MB bank to FLASH_MAP_START
    void ICACHE_FLASH_ATTR selectFlashBank(uint32_t bank)
    {
        Cache_Read_Enable(bank & 1, (bank & 2) >> 1, 1);
    }
    
    
    uint32_t ICACHE_FLASH_ATTR getActualFlashSize()
    {
        static uint32_t const COMPSIZE = 128;
        void* startOfFlash = (void*)(FLASH_MAP_START);
                
        selectFlashBank(3);
        if (f_memcmp(startOfFlash, (void*)(FLASH_MAP_START), COMPSIZE) != 0)
        {
            // does not overlap at 0x0 of bank 2, should be 4MB (32mbit)
            selectFlashBank(0);
            return 0x400000;
        }

        selectFlashBank(1);
        if (f_memcmp(startOfFlash, (void*)(FLASH_MAP_START), COMPSIZE) != 0)
        {
            // does not overlap at 0x0 of bank 1, should be 2MB (16mbit)
            selectFlashBank(0);
            return 0x200000;
        }
        
        selectFlashBank(0);
        if (f_memcmp(startOfFlash, (void*)(FLASH_MAP_START + 0x80000), COMPSIZE) != 0)
        {
            // does not overlap at 0x80000 of bank 0, should be 1MB (8mbit)
            selectFlashBank(0);
            return 0x100000;
        }        
                
        // should be 512K (4mbit)
        selectFlashBank(0);
        return 0x80000;

        /*
        FlashWriter fw(NULL, FLASH_MAP_START + 0x400000);        
        uint32_t v = getDWord((void*)(FLASH_MAP_START + 0x00000000));
        fw.seek((void*)(FLASH_MAP_START + 0x00000000));
        v = v & 0x0FFFFFFF | (0x40 << 24);
        fw.write(&v, 4);
        fw.flush();
        */        
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

	char ICACHE_FLASH_ATTR getChar(char const* str, uint32_t index)
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

	uint8_t ICACHE_FLASH_ATTR getByte(void const* buffer)
	{
		return (uint8_t)getChar((char const*)buffer);
	}

	
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	char ICACHE_FLASH_ATTR getChar(char const* str)
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

	uint16_t ICACHE_FLASH_ATTR getWord(void const* buffer)
	{
		char const* pc = (char const*)buffer;
		return (uint8_t)getChar(pc) | ((uint8_t)getChar(pc + 1) << 8);
	}
	
	
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	uint32_t ICACHE_FLASH_ATTR getDWord(void const* buffer)
	{
		char const* pc = (char const*)buffer;
		return (uint8_t)getChar(pc) | ((uint8_t)getChar(pc + 1) << 8) | ((uint8_t)getChar(pc + 2) << 16) | ((uint8_t)getChar(pc + 3) << 24);
	}

    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
    // FlashWriter
    
    MTD_FLASHMEM FlashWriter::FlashWriter(void* dest, uint32_t maxPosition)
        : m_currentPage(NULL), m_maxPosition((uint8_t*)(FLASH_MAP_START + maxPosition))
    {
        m_dest = (uint8_t*)dest;
        m_pageBuffer = new uint8_t[SPI_FLASH_SEC_SIZE];
    }
    
    MTD_FLASHMEM FlashWriter::~FlashWriter()
    {
        flush();
        delete[] m_pageBuffer;
    }
    
    void MTD_FLASHMEM FlashWriter::loadPage()
    {
        // alignedDest is aligned to the start of flash page (a page is SPI_FLASH_SEC_SIZE bytes)
        uint8_t* alignedDest = (uint8_t*)((uint32_t)m_dest & ~(SPI_FLASH_SEC_SIZE - 1));
        if (alignedDest != m_currentPage)
        {
            // save current page if necessary
            flush();
                        
            // load page from flash
            m_currentPage = alignedDest;
            memcpy(m_pageBuffer, m_currentPage, SPI_FLASH_SEC_SIZE);
        }
        m_writePtr = &m_pageBuffer[m_dest - m_currentPage];
    }
    
    void MTD_FLASHMEM FlashWriter::flush()
    {
        if (m_currentPage)
        {
            // write current page back to flash
            Critical critical;
            uint32_t flashAddr = (uint32_t)m_currentPage - FLASH_MAP_START;
            spi_flash_erase_sector(flashAddr / SPI_FLASH_SEC_SIZE);
            spi_flash_write(flashAddr, (uint32*)m_pageBuffer, SPI_FLASH_SEC_SIZE);            
            
            m_currentPage = NULL;
        }
    }
    
    bool MTD_FLASHMEM FlashWriter::write(void const* source, uint32_t size)
    {
        for (uint8_t const* bSrc = (uint8_t const*)source; size > 0; --size, ++m_dest)
        {
            if (m_dest >= m_maxPosition)
                return false;
            loadPage();
            *m_writePtr = getByte(bSrc++);
        }
        return true;
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