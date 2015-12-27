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
	#include "esp8266/pin_mux_register.h"
	#include "esp8266/eagle_soc.h"
}


namespace fdv
{


	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// GPIO

    
    void MTD_FLASHMEM GPIO::init()
    {
        static uint32_t pinReg[16] = {PERIPHS_IO_MUX_GPIO0_U, PERIPHS_IO_MUX_U0TXD_U, PERIPHS_IO_MUX_GPIO2_U, PERIPHS_IO_MUX_U0RXD_U, 
                                      PERIPHS_IO_MUX_GPIO4_U, PERIPHS_IO_MUX_GPIO5_U, PERIPHS_IO_MUX_SD_CLK_U, PERIPHS_IO_MUX_SD_DATA0_U, 
                                      PERIPHS_IO_MUX_SD_DATA1_U, PERIPHS_IO_MUX_SD_DATA2_U, PERIPHS_IO_MUX_SD_DATA3_U, PERIPHS_IO_MUX_SD_CMD_U, 
                                      PERIPHS_IO_MUX_MTDI_U, PERIPHS_IO_MUX_MTCK_U, PERIPHS_IO_MUX_MTMS_U, PERIPHS_IO_MUX_MTDO_U};
        static uint8_t pinFunc[16] = {FUNC_GPIO0, FUNC_GPIO1, FUNC_GPIO2, FUNC_GPIO3, FUNC_GPIO4, FUNC_GPIO5, FUNC_GPIO6, FUNC_GPIO7, FUNC_GPIO8,
                                      FUNC_GPIO9, FUNC_GPIO10, FUNC_GPIO11, FUNC_GPIO12, FUNC_GPIO13, FUNC_GPIO14, FUNC_GPIO15};
        m_pinReg  = pinReg[m_gpioNum];
        m_pinFunc = pinFunc[m_gpioNum];
    }        
    
    
    void MTD_FLASHMEM GPIO::setupAsGPIO()
    {
        PIN_FUNC_SELECT(m_pinReg, m_pinFunc);
        enablePullUp(false);
    }
    
    
}

