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


#ifndef _FDVUTILS_H_
#define _FDVUTILS_H_


#include "fdv.h"




namespace fdv
{


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// creates a task and reboot after specified time (ms)

struct RebootTask : Task
{
    RebootTask(uint32_t time);
    void exec();

private:    
    uint32_t m_time;
};


// Helper for RebootTask
void reboot(uint32_t time);



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// MemPool
//
// Example of malloc/free implementation using MemPool
//
// static uint32_t const FDVHEAPSIZE = 16384;
// static MemPool* s_memPool = NULL;
//
// void* malloc(uint32_t size)
// {
//     enterCritical();    // or use mutex
//     if (s_memPool == NULL)
//         s_memPool = new(pvPortMalloc(sizeof(MemPool))) MemPool(pvPortMalloc(FDVHEAPSIZE), FDVHEAPSIZE);
//     void* ptr = s_memPool->malloc(size);
//     exitCritical();
//     return ptr;
// }
//
// void free(void* ptr)
// {        
//     enterCritical();
//     s_memPool->free(ptr);
//     exitCritical();
// }

#if (FDV_INCLUDE_MEMPOOL == 1)

class MemPool
{
public:

    typedef uint16_t SIZE_T;
    
    MemPool(void* buffer, SIZE_T bufferLength);
    
    void* malloc(SIZE_T size);
    void free(void const* ptr);
    
    void getStats(SIZE_T* largestFreeBlock, SIZE_T* totalFreeSize);
    SIZE_T getLargestFreeBlock();   // just an helper of getStats()
    
private:

    struct MemPoolBlock
    {
        MemPoolBlock* next;
        SIZE_T        size;  // size not including this structure. This is a multiple of sizeof(MemPoolBlock)
        uint8_t       alloc; // 0 = free, 1 = allocated
    };
    
    MemPoolBlock* findFreeBlock(SIZE_T minsize);
    MemPoolBlock* findBlockFromPtr(void const* ptr);
    void mergeFreeBlocks();
    
    MemPoolBlock* m_blocks;
};

#endif


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Memory

struct Memory
{        
	static void* malloc(uint32_t size);
	static void free(void* ptr);
};



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Ptr
// A very simple smart pointer (without copy or ref counting functionalities)
// For arrays (new[]) use APtr

template <typename T>
class Ptr
{	
private:
	Ptr(Ptr const& c);	// no copy constructor
	
public:
	explicit Ptr(T* ptr)
		: m_ptr(ptr)
	{
	}
	
	Ptr()
		: m_ptr(NULL)
	{
	}
	
	
	~Ptr()
	{
		delete m_ptr;
	}
	
	T& TMTD_FLASHMEM operator*()
	{
		return *m_ptr;
	}
	
	T* TMTD_FLASHMEM operator->()
	{
		return m_ptr;
	}
	
	T* TMTD_FLASHMEM get()
	{
		return m_ptr;
	}
	
	void TMTD_FLASHMEM reset(T* ptr)
	{
		delete m_ptr;
		m_ptr = ptr;
	}
	
private:
	T* m_ptr;
};


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// APtr
// A very simple smart pointer (without copy or ref counting functionalities)
// For single objects (new) use Ptr

template <typename T>
class APtr
{	
private:
	APtr(APtr const& c);	// no copy constructor
	
public:
	explicit APtr(T* ptr)
		: m_ptr(ptr)
	{
	}
	
	APtr()
		: m_ptr(NULL)
	{
	}
	
	~APtr()
	{
		delete[] m_ptr;
	}
	
	T& TMTD_FLASHMEM operator*()
	{
		return *m_ptr;
	}
	
	T* TMTD_FLASHMEM operator->()
	{
		return m_ptr;
	}
	
	T* TMTD_FLASHMEM get()
	{
		return m_ptr;
	}
	
	T& TMTD_FLASHMEM operator[](uint32_t index)
	{
		return m_ptr[index];
	}

	void TMTD_FLASHMEM reset(T* ptr)
	{
		delete[] m_ptr;
		m_ptr = ptr;
	}
	
private:
	T* m_ptr;
};


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// min / max

template <typename T>
T TMTD_FLASHMEM min(T const& v1, T const& v2)
{
	return v1 < v2? v1 : v2;
}

template <typename T>
T TMTD_FLASHMEM max(T const& v1, T const& v2)
{
	return v1 > v2? v1 : v2;
}




}


#endif