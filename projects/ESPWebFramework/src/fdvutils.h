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
// Memory

struct Memory
{
	static void* malloc(uint32_t size);
	static void free(void* ptr);
};



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// ChunkedBuffer

template <typename T, uint32_t CHUNKITEMS_V>
struct ChunkedBuffer
{

	static uint32_t const CHUNKITEMS = CHUNKITEMS_V;

	struct Chunk
	{
		Chunk*   next;
		uint32_t items;
		T        data[CHUNKITEMS];
		
		Chunk()
			: next(NULL), items(0)
		{
		}		
	};

	ChunkedBuffer()
		: m_chunks(NULL), m_current(NULL)
	{
	}
	
	~ChunkedBuffer()
	{
		clear();
	}
	
	void MTD_FLASHMEM clear()
	{
		Chunk* chunk = m_chunks;
		while (chunk)
		{
			Chunk* next = chunk->next;
			delete chunk;
			chunk = next;
		}
		m_chunks = m_current = NULL;
	}
	
	Chunk* MTD_FLASHMEM addChunk()
	{
		if (m_chunks == NULL)
			m_chunks = m_current = new Chunk;
		else
			m_current = m_current->next = new Chunk;		
		return m_current;
	}
	
	int32_t MTD_FLASHMEM find(T const* pattern, uint32_t patternLength)
	{
		int32_t pos = 0;
		uint32_t matches = 0;
		Chunk* chunk = m_chunks;
		while (chunk)
		{
			for (uint32_t i = 0; i != chunk->items; ++i, ++pos)
				if (chunk->data[i] == pattern[matches])
				{
					++matches;
					if (matches == patternLength)
						return pos;
				}
				else
					matches = 0;
			chunk = chunk->next;
		}
		return -1;
	}

private:
	Chunk* m_chunks;
	Chunk* m_current;
};




}


#endif