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




namespace fdv
{


    // returns month as Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
    char const* MTD_FLASHMEM DateTime::monthStr() const
    {
        static char const* MONTHS[] = {FSTR("Jan"), 
                                       FSTR("Feb"), 
                                       FSTR("Mar"), 
                                       FSTR("Apr"), 
                                       FSTR("May"), 
                                       FSTR("Jun"), 
                                       FSTR("Jul"), 
                                       FSTR("Aug"), 
                                       FSTR("Sep"), 
                                       FSTR("Oct"), 
                                       FSTR("Nov"), 
                                       FSTR("Dec")};
        return MONTHS[month];
    }

    
    // 0=sunday...6=saturday
    uint8_t MTD_FLASHMEM DateTime::dayOfWeek() const
    {
        return (date2days(year, month, day) + 6) % 7;
    }    


    DateTime& MTD_FLASHMEM DateTime::setUnixDateTime(uint32_t unixTime)
    {
        unixTime      -= SECONDS_FROM_1970_TO_2000;
        seconds        = unixTime % 60;
        unixTime      /= 60;
        minutes        = unixTime % 60;
        unixTime      /= 60;
        hours         = unixTime % 24;
        uint16_t days = unixTime / 24;
        uint8_t leap;
        for (year = 2000; ; ++year)
        {
            leap = year % 4 == 0;
            if (days < 365u + leap)
                break;
            days -= 365 + leap;
        }
        for (month = 1; ; ++month)
        {
            uint8_t daysPerMonth = daysInMonth(month - 1);
            if (leap && month == 2)
                ++daysPerMonth;
            if (days < daysPerMonth)
                break;
            days -= daysPerMonth;
        }
        day = days + 1;    
        return *this;
    }


    uint32_t MTD_FLASHMEM DateTime::getUnixDateTime() const
    {
        uint16_t days = date2days(year, month, day);
        return time2long(days, hours, minutes, seconds) + SECONDS_FROM_1970_TO_2000;
    }


    DateTime& MTD_FLASHMEM DateTime::setNTPDateTime(uint8_t const* datetimeField, uint8_t timeZone)
    {
        uint32_t t = 0;
        for (uint8_t i = 0; i < 4; ++i)
            t = t << 8 | datetimeField[i];
        float f = ((long)datetimeField[4] * 256 + datetimeField[5]) / 65535.0; 
        t -= 2208988800UL; 
        t += (timeZone * 3600L);
        if (f > 0.4) 
            ++t;
        return setUnixDateTime(t);
    }


    // must be updated before 50 days using adjustNow()
    DateTime MTD_FLASHMEM DateTime::now()
    {
        uint32_t currentMillis = millis();
        uint32_t locLastMillis = lastMillis();
        uint32_t diff = (currentMillis < locLastMillis) ? (0xFFFFFFFF - locLastMillis + currentMillis) : (currentMillis - locLastMillis);
        return DateTime().setUnixDateTime( lastDateTime().getUnixDateTime() + (diff / 1000) );
    }


    void MTD_FLASHMEM DateTime::adjustNow(DateTime const& currentDateTime)
    {
        lastMillis()   = millis();
        lastDateTime() = currentDateTime;
    }


    // Format:
    //    'd' : Day of the month, 2 digits with leading zeros (01..31)
    //    'j' : Day of the month without leading zeros (1..31)
    //    'w' : Numeric representation of the day of the week (0=sunday, 6=saturday)
    //    'm' : Numeric representation of a month, with leading zeros (01..12)
    //    'n' : Numeric representation of a month, without leading zeros (1..12)
    //    'Y' : A full numeric representation of a year, 4 digits (1999, 2000...)
    //    'y' : Two digits year (99, 00...)
    //    'H' : 24-hour format of an hour with leading zeros (00..23)
    //    'i' : Minutes with leading zeros (00..59)
    //    's' : Seconds, with leading zeros (00..59)
    // Example:
    //   char str[50];
    //   datetime.format(str, "d/m/Y H:i:s");
    void MTD_FLASHMEM DateTime::format(char* outbuf, char const* format)
    {
        for (; *format; ++format)
        {
            switch (*format)
            {
                case 'd':
                    outbuf += sprintf(outbuf, "%02d", day);
                    break;
                case 'j':
                    outbuf += sprintf(outbuf, "%d", day);
                    break;
                case 'w':
                    outbuf += sprintf(outbuf, "%d", dayOfWeek());
                    break;
                case 'm':
                    outbuf += sprintf(outbuf, "%02d", month);
                    break;
                case 'n':
                    outbuf += sprintf(outbuf, "%d", month);
                    break;
                case 'Y':
                    outbuf += sprintf(outbuf, "%d", year);
                    break;
                case 'y':
                    outbuf += sprintf(outbuf, "%02d", year % 100);
                    break;
                case 'H':
                    outbuf += sprintf(outbuf, "%02d", hours);
                    break;
                case 'i':
                    outbuf += sprintf(outbuf, "%02d", minutes);
                    break;
                case 's':
                    outbuf += sprintf(outbuf, "%02d", seconds);
                    break;
                default:
                    *outbuf++ = *format;
                    break;
            }
        }
        *outbuf = 0;
    }


    uint8_t MTD_FLASHMEM DateTime::daysInMonth(uint8_t month)
    {
        static uint8_t const DIMO[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return DIMO[month];
    }


    long MTD_FLASHMEM DateTime::time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s)
    {
        return ((days * 24L + h) * 60 + m) * 60 + s;
    }  


    uint16_t MTD_FLASHMEM DateTime::date2days(uint16_t y, uint8_t m, uint8_t d)
    {
        if (y >= 2000)
            y -= 2000;
        uint16_t days = d;
        for (uint8_t i = 1; i < m; ++i)
            days += daysInMonth(i - 1);
        if (m > 2 && y % 4 == 0)
            ++days;
        return days + 365 * y + (y + 3) / 4 - 1;
    }


    DateTime& MTD_FLASHMEM DateTime::lastDateTime()
    {
        static DateTime s_lastDateTime;
        return s_lastDateTime;
    }


    uint32_t& MTD_FLASHMEM DateTime::lastMillis()
    {
        static uint32_t s_lastMillis = millis();
        return s_lastMillis;
    }





} // end of "fdv" namespace

