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

    
    void ICACHE_FLASH_ATTR selectFlashBank(uint32_t bank)
    {
        Cache_Read_Enable(bank & 1, (bank & 2) >> 1, 1);
    }

    
    void ICACHE_FLASH_ATTR selectFlashBankSafe(uint32_t bank)
    {
        enterCritical();
        Cache_Read_Enable(bank & 1, (bank & 2) >> 1, 1);
        exitCritical();
    }
    
    
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
    
        
    
    uint32_t FUNC_FLASHMEM getActualFlashSize()
    {
        static uint32_t const COMPSIZE = 128;
                
        if (f_memcmp(FLASH_MAP_START_PTR, FLASH_MAP_START_PTR + 0x500000, COMPSIZE) != 0)
        {
            // does not overlap at 0x0, should be 4MB (32mbit)
            return 0x400000;
        }

        if (f_memcmp(FLASH_MAP_START_PTR, FLASH_MAP_START_PTR + 0x300000, COMPSIZE) != 0)
        {
            // does not overlap at 0x0, should be 2MB (16mbit)
            return 0x200000;
        }
        
        if (f_memcmp(FLASH_MAP_START_PTR, FLASH_MAP_START_PTR + 0x80000, COMPSIZE) != 0)
        {
            // does not overlap at 0x80000, should be 1MB (8mbit)
            return 0x100000;
        }        
                
        // should be 512K (4mbit)
        return 0x80000;
    }
    
    
    void FUNC_FLASHMEM fixActualFlashSize()
    {
        uint8_t szflag = 0x00;  // default 512K
        switch (getActualFlashSize())
        {
            case 0x100000:  // 1MB?
                szflag = 0x20;
                break;
            case 0x200000:  // 2MB?
                szflag = 0x30;
                break;
            case 0x400000:  // 4MB?
                szflag = 0x40;
                break;
        }
        FlashWriter fw(FLASH_MAP_START_PTR);
        uint32_t v = getDWord(FLASH_MAP_START_PTR) & 0x0FFFFFFF | (szflag << 24);
        fw.write(&v, 4);
    }
    

	// size in MHz
	uint32_t FUNC_FLASHMEM getFlashSpeed()
	{
		uint32_t flags = *((uint32_t volatile*)FLASH_MAP_START_PTR);
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
    
    // Actually flash memory can be mapped a 1MB a the time starting from FLASH_MAP_START
    // This function creates a "virtual" allocation from FLASH_MAP_START up to the actual size of the flash memory,
    // switching the right bank and restoring it at the end.
    uint32_t ICACHE_FLASH_ATTR getFlashAlignedDWord(uint32_t const* ptr)
    {
        // Following assuming FLASH_MAP_START = 0x40200000:
        //   select bank 0 (for 0x40200000 - 0x402FFFFF)
        //   select bank 1 (for 0x40300000 - 0x403FFFFF)
        //   select bank 2 (for 0x40400000 - 0x404FFFFF)
        //   select bank 3 (for 0x40500000 - 0x405FFFFF)
        uint32_t bank = ((uint32_t)ptr >> 20 & 0xF) - 2;
        if (bank > 0)
        {
            enterCritical();
            selectFlashBank(bank);
        }
        
        // calculate actual address (only first megabyte is directly addressable)
        uint32_t addr = (uint32_t)ptr & 0xFFFFF + FLASH_MAP_START;
        
        // get aligned dword
        uint32_t result = *((uint32_t volatile*)addr);
        
        if (bank > 0)
        {
            // restore bank 0 for code execution
            selectFlashBank(0);
            exitCritical();
        }
        
        return result;        
    }
    

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	uint8_t FUNC_FLASHMEM getByte(void const* address)
	{
        if (isStoredInFlash(address))
        {
            // align address to 32 bit
            uint32_t const* alignedAddress = (uint32_t const*)((uint32_t)address & 0xFFFFFFFC);  
            // get content from flash taking care about right bank
            uint32_t result32 = getFlashAlignedDWord(alignedAddress);
            // return required by inside the dword
            return ((uint8_t const*)&result32)[(uint32_t)address & 0x3];
        }
        else
        {
            return *((uint8_t const*)address);
        }
	}


  	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	char FUNC_FLASHMEM getChar(char const* str, uint32_t index)
	{
        return isStoredInFlash(str)? (char)getByte(str + index) : str[index];
	}

    	
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	char FUNC_FLASHMEM getChar(char const* str)
	{
        return isStoredInFlash(str)? (char)getByte(str) : *str;
	}		
		

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	uint16_t FUNC_FLASHMEM getWord(void const* buffer)
	{
		uint8_t const* pc = (uint8_t const*)buffer;
		return getByte(pc) | (getByte(pc + 1) << 8);
	}
	
	
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	uint32_t FUNC_FLASHMEM getDWord(void const* buffer)
	{
		uint8_t const* pc = (uint8_t const*)buffer;
		return getByte(pc) | (getByte(pc + 1) << 8) | (getByte(pc + 2) << 16) | (getByte(pc + 3) << 24);
	}

    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
    // FlashWriter
    
    MTD_FLASHMEM FlashWriter::FlashWriter(void const* dest)
        : m_currentPage(NULL), m_maxPosition(getBeginOfSDKSettings())
    {
        m_dest = (uint8_t const*)dest;
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
        uint8_t const* alignedDest = (uint8_t const*)((uint32_t)m_dest & ~(SPI_FLASH_SEC_SIZE - 1));
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