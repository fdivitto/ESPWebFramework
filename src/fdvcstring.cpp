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

extern "C" {
#include <limits.h>
#include <float.h>
#include <math.h>
}


namespace fdv {

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_strlen
// str can be stored in Flash or/and in RAM
uint32_t FUNC_FLASHMEM f_strlen(char const *str) {
  return t_strlen(CharIterator(str)); 
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_strnlen
// str can be stored in Flash or/and in RAM
uint32_t FUNC_FLASHMEM f_strnlen(char const *str, uint32_t maxlen) {
  return t_strnlen(CharIterator(str), maxlen); 
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_strcpy
// source can be stored in Flash or/and in RAM
char *FUNC_FLASHMEM f_strcpy(char *destination, char const *source) {
  return t_strcpy(destination, CharIterator(source));
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_strncpy
// source can be stored in Flash or/and in RAM
char *FUNC_FLASHMEM f_strncpy(char *destination, char const *source, uint32_t n) {
  return t_strncpy(destination, CharIterator(source), n);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_strdup
// use delete[] to free memory
// str can be stored in Flash or/and in RAM
char *FUNC_FLASHMEM f_strdup(char const *str) {
  return t_strdup(CharIterator(str)); 
}

// adds automatically ending zero
char *FUNC_FLASHMEM f_strdup(char const *sourceStart, char const *sourceEnd) {
  return t_strdup(CharIterator(sourceStart), CharIterator(sourceEnd));
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_memdup
// use delete[] to free memory
// str can be stored in Flash or/and in RAM
void *FUNC_FLASHMEM f_memdup(void const *buffer, uint32_t length) {
  return t_memdup(ByteIterator((uint8_t const *)buffer), length);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_strcmp
// both s1 and s2 can be stored in Flash or/and in RAM
int32_t FUNC_FLASHMEM f_strcmp(char const *s1, char const *s2) {
  return t_strcmp(CharIterator(s1), CharIterator(s2)); 
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_strncmp
// both s1 and s2 can be stored in Flash or/and in RAM
int32_t FUNC_FLASHMEM f_strncmp(char const *s1, char const *s2, uint32_t n) {
  return t_strncmp(CharIterator(s1), CharIterator(s2), n); 
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_memcmp
// both s1 and s2 can be stored in Flash or/and in RAM
int32_t FUNC_FLASHMEM f_memcmp(void const *s1, void const *s2, uint32_t length) {
  return t_memcmp(ByteIterator((uint8_t const *)s1), ByteIterator((uint8_t const *)s2), length);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_memcpy
// source can be stored in Flash or/and in RAM
void *FUNC_FLASHMEM f_memcpy(void *destination, void const *source, uint32_t length) {
  return t_memcpy(destination, ByteIterator((uint8_t const *)source), length);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// f_strstr
// both str and substr can be stored in Flash or/and RAM
char const *FUNC_FLASHMEM f_strstr(char const *str, char const *substr) {
  return t_strstr(CharIterator(str), CharIterator(substr)).get();
}

char const *FUNC_FLASHMEM f_strstr(char const *str, char const *strEnd, char const *substr) {
  return t_strstr(CharIterator(str), CharIterator(strEnd), CharIterator(substr)).get();
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// isspace
bool FUNC_FLASHMEM isspace(char c) {
  return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// isalpha
bool FUNC_FLASHMEM isalpha(char c) {
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')); 
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// isdigit
bool FUNC_FLASHMEM isdigit(char c) {
  return (c >= '0' && c <= '9'); 
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// isalnum
bool FUNC_FLASHMEM isalnum(char c) {
  return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// isxdigit
bool FUNC_FLASHMEM isxdigit(char c) {
  return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); 
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// isupper
bool FUNC_FLASHMEM isupper(char c) {
  return c >= 'A' && c <= 'Z'; 
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// islower
bool FUNC_FLASHMEM islower(char c) {
  return c >= 'a' && c <= 'z'; 
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// isascii
bool FUNC_FLASHMEM isascii(char c) {
  return c >= 0 && c <= 127;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// hexDigitToInt
// assume x is a valid hex digit
uint32_t FUNC_FLASHMEM hexDigitToInt(char x) {
  return isdigit(x) ? x - '0' : (islower(x) ? x - 'a' + 10 : x - 'A' + 10);
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// inplaceURLDecode
// str can stay only in RAM
// returns str

char *FUNC_FLASHMEM inplaceURLDecode(char *str) {
  char *rpos = str;
  char *wpos = str;
  while (*rpos) {
    if (*rpos == '%') {
      if (isxdigit(rpos[1]) && rpos[2] && isxdigit(rpos[2])) {
        *wpos++ = (hexDigitToInt(rpos[1]) << 4) | hexDigitToInt(rpos[2]);
        rpos += 3;
      }
    } else if (*rpos == '+') {
      *wpos++ = 0x20;
      ++rpos;
    } else {
      *wpos++ = *rpos++;
    }
  }
  *wpos = 0;
  return str;
}



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// f_strtoul
// str can be stored in Flash or/and RAM
// 
/*
 * Copyright (c) 1990, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *        may be used to endorse or promote products derived from this software
 *        without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.      IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * 2016: Adapted by Fabrizio Di Vittorio 
 */

/*
 * Convert a string to an unsigned long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
uint32_t FUNC_FLASHMEM f_strtoul(char const *nptr, char **endptr, int base)
{
  const char    *s = nptr;
  uint32_t      acc;
  unsigned char c;
  uint32_t      cutoff;
  int32_t       neg = 0, any, cutlim;

  do {
    c = getChar(s++);
  } while (isspace(c));
  if (c == '-') {
    neg = 1;
    c = getChar(s++);
  } else if (c == '+')
    c = getChar(s++);
  if ((base == 0 || base == 16) && c == '0' && (getChar(s) == 'x' || getChar(s) == 'X')) {
    c = getChar(s, 1);
    s += 2;
    base = 16;
  }
  if (base == 0)
    base = c == '0' ? 8 : 10;
  cutoff = (uint32_t) ULONG_MAX / (uint32_t) base;
  cutlim = (uint32_t) ULONG_MAX % (uint32_t) base;
  for (acc = 0, any = 0;; c = getChar(s++)) {
    if (!isascii(c))
      break;
    if (isdigit(c))
      c -= '0';
    else if (isalpha(c))
      c -= isupper(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base)
      break;
    if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
      any = -1;
    else {
      any = 1;
      acc *= base;
      acc += c;
    }
  }
  if (any < 0) {
    acc = ULONG_MAX;
    errno = ERANGE;
  } else if (neg)
    acc = -acc;
  if (endptr != 0)
    *endptr = (char *) (any ? s - 1 : nptr);
  return (acc);
}



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// f_strtol
// str can be stored in Flash or/and RAM
// 
/* 
 * Copyright (c) 1988 The Regents of the University of California.
 * Copyright (c) 1994 Sun Microsystems, Inc.
 */

int32_t FUNC_FLASHMEM f_strtol(const char *string, char **endPtr, int base) {
  const char *p;
  long result;

  p = string;
  while (isspace(getChar(p)))
    ++p;

  if (getChar(p) == '-') {
    ++p;
    result = -(f_strtoul(p, endPtr, base));
  } else {
    if (getChar(p) == '+') {
      ++p;
    }
    result = f_strtoul(p, endPtr, base);
  }
  if ((result == 0) && (endPtr != 0) && (*endPtr == p)) {
    *endPtr = (char *) string;
  }
  return result;
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// f_strtod
// str can be stored in Flash or/and RAM
//
// Copyright (C) 2002 Michael Ringgaard. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
// 1. Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.  
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.  
// 3. Neither the name of the project nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission. 
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
// SUCH DAMAGE.
//
// 2016: Adapted by Fabrizio Di Vittorio 

double FUNC_FLASHMEM f_strtod(const char *str, char **endptr) {
  double number;
  int exponent;
  int negative;
  char *p = (char *) str;
  double p10;
  int n;
  int num_digits;
  int num_decimals;

  // Skip leading whitespace
  while (isspace(getChar(p))) p++;

  // Handle optional sign
  negative = 0;
  switch (getChar(p)) {
    case '-': negative = 1; // Fall through to increment position
    case '+': p++;
  }

  number = 0.;
  exponent = 0;
  num_digits = 0;
  num_decimals = 0;

  // Process string of digits
  while (isdigit(getChar(p))) {
    number = number * 10. + (getChar(p) - '0');
    p++;
    num_digits++;
  }

  // Process decimal part
  if (getChar(p) == '.') {
    p++;

    while (isdigit(getChar(p))) {
      number = number * 10. + (getChar(p) - '0');
      p++;
      num_digits++;
      num_decimals++;
    }

    exponent -= num_decimals;
  }

  if (num_digits == 0) {
    errno = ERANGE;
    return 0.0;
  }

  // Correct for sign
  if (negative) number = -number;

  // Process an exponent string
  if (getChar(p) == 'e' || getChar(p) == 'E') {
    // Handle optional sign
    negative = 0;
    switch (getChar(++p)) {
      case '-': negative = 1;   // Fall through to increment pos
      case '+': p++;
    }

    // Process string of digits
    n = 0;
    while (isdigit(getChar(p))) {
      n = n * 10 + (getChar(p) - '0');
      p++;
    }

    if (negative) {
      exponent -= n;
    } else {
      exponent += n;
    }
  }

  if (exponent < DBL_MIN_EXP  || exponent > DBL_MAX_EXP) {
    errno = ERANGE;
    return HUGE_VAL;
  }

  // Scale the result
  p10 = 10.;
  n = exponent;
  if (n < 0) n = -n;
  while (n) {
    if (n & 1) {
      if (exponent < 0) {
        number /= p10;
      } else {
        number *= p10;
      }
    }
    n >>= 1;
    p10 *= p10;
  }

  if (number == HUGE_VAL) errno = ERANGE;
  if (endptr) *endptr = p;

  return number;
} 
 
}
