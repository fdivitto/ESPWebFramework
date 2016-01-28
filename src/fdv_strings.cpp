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
    // f_strlen
    // str can be stored in Flash or/and in RAM
    uint32_t FUNC_FLASHMEM f_strlen(char const* str)
    {
        return t_strlen(CharIterator(str));
    }

        
    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    // f_strnlen
    // str can be stored in Flash or/and in RAM
    uint32_t FUNC_FLASHMEM f_strnlen(char const* str, uint32_t maxlen)
    {
        return t_strnlen(CharIterator(str), maxlen);
    }


    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    // f_strcpy
    // source can be stored in Flash or/and in RAM
    char* FUNC_FLASHMEM f_strcpy(char* destination, char const* source)
    {
        return t_strcpy(destination, CharIterator(source));
    }


    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    // f_strdup
    // use delete[] to free memory
    // str can be stored in Flash or/and in RAM
    char* FUNC_FLASHMEM f_strdup(char const* str)
    {
        return t_strdup(CharIterator(str));
    }

    // adds automatically ending zero
    char* FUNC_FLASHMEM f_strdup(char const* sourceStart, char const* sourceEnd)
    {
        return t_strdup(CharIterator(sourceStart), CharIterator(sourceEnd));
    }


    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    // f_memdup
    // use delete[] to free memory
    // str can be stored in Flash or/and in RAM
    void* FUNC_FLASHMEM f_memdup(void const* buffer, uint32_t length)
    {
        return t_memdup(ByteIterator((uint8_t const*)buffer), length);
    }
            

    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    // f_strcmp
    // both s1 and s2 can be stored in Flash or/and in RAM
    int32_t FUNC_FLASHMEM f_strcmp(char const* s1, char const* s2)
    {
        return t_strcmp(CharIterator(s1), CharIterator(s2));
    }


    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    // f_memcmp
    // both s1 and s2 can be stored in Flash or/and in RAM
    int32_t FUNC_FLASHMEM f_memcmp(void const* s1, void const* s2, uint32_t length)
    {
        return t_memcmp(ByteIterator((uint8_t const*)s1), ByteIterator((uint8_t const*)s2), length);
    }


    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    // f_memcpy
    // source can be stored in Flash or/and in RAM
    void* FUNC_FLASHMEM f_memcpy(void* destination, void const* source, uint32_t length)
    {
        return t_memcpy(destination, ByteIterator((uint8_t const*)source), length);
    }


    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    // f_strstr
    // both str and substr can be stored in Flash or/and RAM
    char const* FUNC_FLASHMEM f_strstr(char const* str, char const* substr)
    {
        return t_strstr(CharIterator(str), CharIterator(substr)).get();
    }

    char const* FUNC_FLASHMEM f_strstr(char const* str, char const* strEnd, char const* substr)
    {
        return t_strstr(CharIterator(str), CharIterator(strEnd), CharIterator(substr)).get();
    }


    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    // isspace
    bool FUNC_FLASHMEM isspace(char c)
    {
        return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
    }


    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    // isalpha
    bool FUNC_FLASHMEM isalpha(char c)
    {
        return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
    }


    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    // isdigit
    bool FUNC_FLASHMEM isdigit(char c)
    {
        return (c >= '0' && c <= '9');
    }

    
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    // isalnum
    bool FUNC_FLASHMEM isalnum(char c)
    {
        return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    }

    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    // isxdigit
    bool FUNC_FLASHMEM isxdigit(char c)
    {
        return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
    }


    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    // isupper
    bool FUNC_FLASHMEM isupper(char c)
    {
        return c >= 'A' && c <= 'Z';
    }


    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    // islower
    bool FUNC_FLASHMEM islower(char c)
    {
        return c >= 'a' && c <= 'z';
    }


    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    // hexDigitToInt
    // assume x is a valid hex digit
    uint32_t FUNC_FLASHMEM hexDigitToInt(char x)
    {
        return isdigit(x)? x - '0' : (islower(x)? x - 'a' + 10 : x - 'A' + 10);
    }


	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	char* FUNC_FLASHMEM f_printf(char const *fmt, ...)
	{
		va_list args;
		
		va_start(args, fmt);
		uint16_t len = vsprintf(NULL, fmt, args);
		va_end(args);

		char* buf = new char[len + 1];
		
		va_start(args, fmt);
		vsprintf(buf, fmt, args);
		va_end(args);

		return buf;
	}


	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	// inplaceURLDecode
	// str can stay only in RAM
	// returns str
	
	char* FUNC_FLASHMEM inplaceURLDecode(char* str)
	{
		char* rpos = str;
		char* wpos = str;
		while (*rpos)
		{
			if (*rpos == '%')
			{
				if (isxdigit(rpos[1]) && rpos[2] && isxdigit(rpos[2]))
				{
					*wpos++ = (hexDigitToInt(rpos[1]) << 4) | hexDigitToInt(rpos[2]);
					rpos += 3;
				}
			}
			else if (*rpos == '+')
			{
				*wpos++ = 0x20;
				++rpos;
			}
			else
			{
				*wpos++ = *rpos++;
			}
		}
		*wpos = 0;
		return str;
	}

	
	


	

}



