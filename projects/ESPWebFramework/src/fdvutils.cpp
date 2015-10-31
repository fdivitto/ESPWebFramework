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


#include "fdv.h"

extern "C"
{
	#include "freertos/semphr.h"
	#include "lwip/mem.h"
}




void *__dso_handle;


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Memory

namespace fdv
{
    
    //static uint32_t s_blocksAllocated = 0;
    

	void* STC_FLASHMEM Memory::malloc(uint32_t size)
	{
		return pvPortMalloc(size);
        /*++s_blocksAllocated;
        void* ptr = pvPortMalloc(size);
        if (s_blocksAllocated > 2) debug("malloc %d %p (%d bytes)\r\n", s_blocksAllocated, ptr, size);
        return ptr;*/
	}

	void STC_FLASHMEM Memory::free(void* ptr)
	{        
        //debug("free %d %p\r\n", --s_blocksAllocated, ptr);
		vPortFree(ptr);
	}

}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void * FUNC_FLASHMEM operator new(size_t size)
{
    return fdv::Memory::malloc(size);
}

void * FUNC_FLASHMEM operator new[](size_t size) 
{
    return fdv::Memory::malloc(size);
}

void FUNC_FLASHMEM operator delete(void * ptr) 
{
    fdv::Memory::free(ptr);
}

void FUNC_FLASHMEM operator delete[](void * ptr) 
{
    fdv::Memory::free(ptr);
}

extern "C" void __cxa_pure_virtual(void) __attribute__ ((__noreturn__));

extern "C" void __cxa_deleted_virtual(void) __attribute__ ((__noreturn__));

extern "C" void FUNC_FLASHMEM abort() 
{
  while(true); // enter an infinite loop and get reset by the WDT
}

void FUNC_FLASHMEM __cxa_pure_virtual(void) 
{
  abort();
}

void FUNC_FLASHMEM __cxa_deleted_virtual(void) 
{
  abort();
}



namespace fdv
{


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// reboot
// creates a task and reboot after specified time (ms)

RebootTask::RebootTask(uint32_t time) 
    : Task(false, 400), m_time(time)
{
}


void MTD_FLASHMEM RebootTask::exec()
{
    delay(m_time);
    taskENTER_CRITICAL();
    taskDISABLE_INTERRUPTS();
    while(1);	// reset using watchdog
}
    

void FUNC_FLASHMEM reboot(uint32_t time)
{	
    new RebootTask(time);
}





/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// MemPool


// bufferLength should be a multiple of MemPoolBlock size
MTD_FLASHMEM MemPool::MemPool(void* buffer, SIZE_T bufferLength)
    : m_blocks((MemPoolBlock*)buffer)
{
    // make sure bufferLength is a multiple of sizeof(MemPoolBlock)
    bufferLength -= bufferLength % sizeof(MemPoolBlock);
    
    // creates a unique free block having the same size of main buffer
    m_blocks->next  = NULL;
    m_blocks->alloc = 0;
    m_blocks->size  = bufferLength - sizeof(MemPoolBlock);
}


MemPool::MemPoolBlock* MTD_FLASHMEM MemPool::findFreeBlock(SIZE_T minsize)
{
    for (MemPoolBlock* curblk = m_blocks; curblk; curblk = curblk->next)
        if ((curblk->alloc == 0) && curblk->size >= minsize)
            return curblk;
    return NULL;
}


MemPool::MemPoolBlock* MTD_FLASHMEM MemPool::findBlockFromPtr(void const* ptr)
{
    for (MemPoolBlock* curblk = m_blocks; curblk; curblk = curblk->next)
        if (ptr == curblk + 1)
            return curblk;
    return NULL;
}


void* MTD_FLASHMEM MemPool::malloc(SIZE_T size)
{
    // make size a multiple of MemPoolBlock size
    if (size % sizeof(MemPoolBlock) != 0)
        size += sizeof(MemPoolBlock) - size % sizeof(MemPoolBlock);
    
    MemPoolBlock* freeblk = findFreeBlock(size);
    if (freeblk)
    {
        // found a free block
        uint8_t* ptr = (uint8_t*)(freeblk + 1); // ptr aligned to MemPoolBlock size (hence should be to CPU word size)
        if (freeblk->size > size + sizeof(MemPoolBlock))    // is there space for another free block?
        {
            // split this block
            MemPoolBlock* newblk = freeblk + 1 + size / sizeof(MemPoolBlock);
            newblk->next  = freeblk->next;
            newblk->alloc = 0;
            newblk->size  = freeblk->size - size - sizeof(MemPoolBlock);
            freeblk->next = newblk;
            freeblk->size = size;
        }
        freeblk->alloc = 1;
        
        return ptr;
    }
    else
        return NULL;
}


void MTD_FLASHMEM MemPool::free(void const* ptr)
{
    if (ptr)
    {
        MemPoolBlock* blk = findBlockFromPtr(ptr);
        if (blk)
        {
            blk->alloc = 0;
            mergeFreeBlocks();
        }
    }
}


void MTD_FLASHMEM MemPool::mergeFreeBlocks()
{
    MemPoolBlock* curblk = m_blocks;
    while (curblk->next)
    {
        if (curblk->alloc == 0 && curblk->next->alloc == 0)
        {
            // merge this and next block
            curblk->size += curblk->next->size + sizeof(MemPoolBlock);
            curblk->next = curblk->next->next;
        }
        else
        {
            curblk = curblk->next;
        }
    }
}


void MTD_FLASHMEM MemPool::getStats(SIZE_T* largestFreeBlock, SIZE_T* totalFreeSize)
{
    *largestFreeBlock = 0;
    *totalFreeSize    = 0;
    for (MemPoolBlock* blk = m_blocks; blk; blk = blk->next)
    {
        if (blk->alloc == 0)
        {
            *totalFreeSize += blk->size;
            if (blk->size > *largestFreeBlock)
                *largestFreeBlock = blk->size;
        }
    }
}


MemPool::SIZE_T MTD_FLASHMEM MemPool::getLargestFreeBlock()
{
    SIZE_T largestFreeBlock, totalFreeSize;
    getStats(&largestFreeBlock, &totalFreeSize);
    return largestFreeBlock;
}




}   // end of namespace


