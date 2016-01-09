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

#ifndef _FDVCOMMONSTR_H_
#define _FDVCOMMONSTR_H_



#include "fdv.h"





namespace fdv
{


	static char const STR_[] FLASHMEM               = "";
	static char const STR_WiFiMode[] FLASHMEM       = "WiFiMode";
	static char const STR_APSSID[] FLASHMEM         = "APSSID";
	static char const STR_APSECKEY[] FLASHMEM       = "APSECKEY";
	static char const STR_APCH[] FLASHMEM           = "APCH";
	static char const STR_APSP[] FLASHMEM           = "APSP";
	static char const STR_APHSSID[] FLASHMEM        = "APHSSID";
	static char const STR_CLSSID[] FLASHMEM         = "CLSSID";
	static char const STR_CLSECKEY[] FLASHMEM       = "CLSECKEY";
	static char const STR_CLSTATIC[] FLASHMEM       = "CLSTATIC";
	static char const STR_CLIP[] FLASHMEM           = "CLIP";
	static char const STR_CLNETMSK[] FLASHMEM       = "CLNETMSK";
	static char const STR_CLGTW[] FLASHMEM          = "CLGTW";
	static char const STR_APIP[] FLASHMEM           = "APIP";
	static char const STR_APNETMSK[] FLASHMEM       = "APNETMSK";
	static char const STR_APGTW[] FLASHMEM          = "APGTW";
	static char const STR_DHCPDEN[] FLASHMEM        = "DHCPDEN";
    static char const STR_DHCPD[] FLASHMEM          = "DHCPD";
	static char const STR_DHCPDIP1[] FLASHMEM       = "DHCPDIP1";
	static char const STR_DHCPDIP2[] FLASHMEM       = "DHCPDIP2";
	static char const STR_WEBPORT[] FLASHMEM        = "WEBPORT";
	static char const STR_BAUD[] FLASHMEM           = "BAUD";
	static char const STR_SYSOUT[] FLASHMEM         = "SYSOUT";
	static char const STR_UARTSRV[] FLASHMEM        = "UARTSRV";
	static char const STR_checked[] FLASHMEM        = "checked";
	static char const STR_selected[] FLASHMEM       = "selected"; 
	static char const STR_disabled[] FLASHMEM       = "disabled";
	static char const STR_Content_Type[] FLASHMEM   = "Content-Type";
	static char const STR_Content_Length[] FLASHMEM = "Content-Length";
	static char const STR_httpport[] FLASHMEM       = "httpport";
	static char const STR_baud[] FLASHMEM           = "baud";
	static char const STR_debugout[] FLASHMEM       = "debugout";
    static char const STR_Mode[] FLASHMEM           = "Mode";
    static char const STR_mode[] FLASHMEM           = "mode";
    static char const STR_pullup[] FLASHMEM         = "pullup";
	static char const STR_clientmode[] FLASHMEM     = "clientmode";
	static char const STR_apmode[] FLASHMEM         = "apmode";
    static char const STR_bothsmode[] FLASHMEM      = "bothsmode";
	static char const STR_HI[] FLASHMEM             = "HI";
	static char const STR_LO[] FLASHMEM             = "LO";
	static char const STR_BINPRORDY[] FLASHMEM      = "BINPRORDY";
    static char const STR_TZHH[] FLASHMEM           = "TZHH";
    static char const STR_TZMM[] FLASHMEM           = "TZMM";
    static char const STR_DEFNTPSRV[] FLASHMEM      = "DEFNTPSRV";
    static char const STR_date[] FLASHMEM           = "date";
    static char const STR_time[] FLASHMEM           = "time";
    static char const STR_tzh[] FLASHMEM            = "tzh";
    static char const STR_tzm[] FLASHMEM            = "tzm";
    static char const STR_stcIP[] FLASHMEM          = "stcIP";
    static char const STR_dynIP[] FLASHMEM          = "dynIP";
    static char const STR_CLIPMOD[] FLASHMEM        = "CLIPMOD";
	static char const STR_ntpsrv[] FLASHMEM         = "ntpsrv";
    static char const STR_now[] FLASHMEM            = "now";
    static char const STR_uptime[] FLASHMEM         = "uptime";
    static char const STR_DNS1[] FLASHMEM           = "DNS1";
    static char const STR_DNS2[] FLASHMEM           = "DNS2";
    static char const STR_ROUTING[] FLASHMEM        = "ROUTING";
    static char const STR_CLMSK[] FLASHMEM          = "CLMSK";
    static char const STR_APMSK[] FLASHMEM          = "APMSK";
    static char const STR_DISP_APIPCONF[] FLASHMEM  = "DISP_APIPCONF";
    static char const STR_DISP_CLIPCONF[] FLASHMEM  = "STR_DISP_CLIPCONF";
    static char const STR_startIP[] FLASHMEM        = "startIP";
    static char const STR_endIP[] FLASHMEM          = "endIP";    
    static char const STR_CHTIMEMAN[] FLASHMEM      = "CHTIMEMAN";
    static char const STR_CHTIMEAUT[] FLASHMEM      = "CHTIMEAUT";
    static char const STR_srv0[] FLASHMEM           = "srv0";
    static char const STR_srv1[] FLASHMEM           = "srv1";
    static char const STR_srv2[] FLASHMEM           = "srv2";
    static char const STR_wizdone[] FLASHMEM        = "wizdone";
    static char const STR_gpio[] FLASHMEM           = "gpio";
    static char const STR_0[] FLASHMEM              = "0";
    static char const STR_1[] FLASHMEM              = "1";
    static char const STR_store[] FLASHMEM          = "store";
    static char const STR_out[] FLASHMEM            = "out";
    static char const STR_ls[] FLASHMEM             = "ls";
    static char const STR_style_display_none[] FLASHMEM = "style='display:none'";
	static char const STR_200_OK[] FLASHMEM                = "200 OK";
	static char const STR_404_Not_Found[] FLASHMEM         = "404 Not Found";
    static char const STR_301_Moved_Permanently[] FLASHMEM = "301 Moved Permanently";
    static char const STR_302_Found[] FLASHMEM             = "302 Found";
    static char const STR_400_Bad_Request[] FLASHMEM       = "400 Bad Request";
    static char const STR_401_Unauthorized[] FLASHMEM      = "401 Unauthorized";
    static char const STR_403_Forbidden[] FLASHMEM         = "403 Forbidden";
    static char const STR_TEXTHTML[] FLASHMEM       = "text/html";
    static char const STR_TEXTHTML_UTF8[] FLASHMEM  = "text/html; charset=utf-8";
    static char const STR_APPJSON[] FLASHMEM        = "application/json";
    static char const STR_TEXTPLAIN[] FLASHMEM      = "text/plain";
    static char const STR_TEXTXML[] FLASHMEM        = "text/xml";
}

#endif

