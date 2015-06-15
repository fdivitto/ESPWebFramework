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



//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// SerialConsole
	
#if (FDV_INCLUDE_SERIALCONSOLE == 1)


	
void MTD_FLASHMEM SerialConsole::cmd_uptime()
{
    int32_t seconds = DateTime::now() - ConfigurationManager::getBootDateTime();
    uint32_t days = seconds / 86400;
    seconds %= 86400;
    uint32_t minutes = seconds / 1440;
    seconds %= 1440;
    m_serial->printf(FSTR("%d days, %d minutes, %d seconds\r\n"), days, minutes, seconds);
}
    
    
    
    
#endif



} // end of "fdv" namespace

