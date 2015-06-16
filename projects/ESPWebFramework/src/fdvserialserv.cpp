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


void MTD_FLASHMEM SerialConsole::exec()
{
    m_serial = HardwareSerial::getSerial(0);
    cmd_help();
    m_serial->writeNewLine();
    while (true)
    {
        m_receivedChunks.clear();
        m_serial->write(FSTR("$ "));
        if (m_serial->readLine(true, &m_receivedChunks))
        {
            m_serial->writeNewLine();
            separateParameters();
            routeCommand();
            /*
            debug("params = %d\r\n", m_paramsCount);
            for (int32_t i = 0; i != m_paramsCount; ++i)
            {
                debug("  %d = ", i);
                for (CharChunksIterator it = m_params[i]; *it; ++it)
                    debug(*it);
                debug("   ");
                for (CharChunksIterator it = m_params[i]; *it; ++it)
                    debug("%x ", (int)*it);
                debug("\r\n");
            }
            */
        }
    }
}


void MTD_FLASHMEM SerialConsole::separateParameters()
{
    m_paramsCount = 0;
    bool quote = false;
    CharChunksIterator start = m_receivedChunks.getIterator();
    for (CharChunksIterator it = start; it.isValid(); ++it)
    {
        if (!quote && *it == '"')
        {
            quote = true;
        }
        else if (quote && *it == '"')
        {
            m_params[m_paramsCount++] = start + 1;
            *it = 0x00;
            ++it;
            start = it + 1;
            quote = false;
            
        }
        else if ((!quote && *it == ' ') || *it == 0x00 || it.isLast())
        {
            if (it != start)
            {
                *it = 0x00;
                m_params[m_paramsCount++] = start;
            }
            start = it + 1;
        }
    }			
}


void MTD_FLASHMEM SerialConsole::routeCommand()
{
    typedef void (SerialConsole::*Handler)();
    struct Cmd
    {
        char const* cmd;
        Handler     handler;
    };
    static const Cmd cmds[] =
    {
        {FSTR("help"),	     &SerialConsole::cmd_help},
        {FSTR("reboot"),	 &SerialConsole::cmd_reboot},
        {FSTR("restore"),	 &SerialConsole::cmd_restore},
        {FSTR("free"),       &SerialConsole::cmd_free},
        {FSTR("ifconfig"),   &SerialConsole::cmd_ifconfig},
        {FSTR("iwlist"),     &SerialConsole::cmd_iwlist},
        {FSTR("date"),       &SerialConsole::cmd_date},
        {FSTR("ntpdate"),    &SerialConsole::cmd_ntpdate},
        {FSTR("nslookup"),   &SerialConsole::cmd_nslookup},
        {FSTR("test"),       &SerialConsole::cmd_test},
        {FSTR("uptime"),     &SerialConsole::cmd_uptime},
    };
    static uint32_t const cmdCount = sizeof(cmds) / sizeof(Cmd);
    
    if (m_paramsCount > 0)
    {
        for (uint32_t i = 0; i != cmdCount; ++i)
        {
            if (t_strcmp(m_params[0], CharIterator(cmds[i].cmd)) == 0)
            {
                (this->*cmds[i].handler)();
                return;
            }
        }
        m_serial->writeln(FSTR("Unknown command"));
    }
}


void MTD_FLASHMEM SerialConsole::cmd_help()
{
    m_serial->writeln(FSTR("\r\nESP Console"));
    m_serial->writeln(FSTR("help          : Show this help"));
    m_serial->writeln(FSTR("reboot [ms]   : Restart system in [ms] milliseconds"));
    m_serial->writeln(FSTR("restore       : Erase Flash stored settings"));
    m_serial->writeln(FSTR("free          : Display amount of free and used memory"));
    m_serial->writeln(FSTR("ifconfig      : Display network info"));
    m_serial->writeln(FSTR("iwlist [scan] : Display or scan for available wireless networks"));
    m_serial->writeln(FSTR("date          : Display current date/time"));
    m_serial->writeln(FSTR("ntpdate       : Display date/time from NTP server"));
    m_serial->writeln(FSTR("nslookup NAME : Query DNS"));
    m_serial->writeln(FSTR("uptime        : Display how long the system has been running"));
}


void MTD_FLASHMEM SerialConsole::cmd_restore()
{
    m_serial->write(FSTR("\r\nAre you sure [y/N]? "));
    m_receivedChunks.clear();
    if (m_serial->readLine(true, &m_receivedChunks))
    {
        if (*m_receivedChunks.getIterator() == 'y')
        {
            FlashDictionary::eraseContent();
            m_serial->write(FSTR("\r\nFlash settings restored"));
        }
    }
    m_serial->writeNewLine();
}


void MTD_FLASHMEM SerialConsole::cmd_reboot()
{
    uint32_t ms = 50;
    if (m_paramsCount == 2)
        ms = t_strtol(m_params[1], 10);
    reboot(ms);
    m_serial->writeln(FSTR("\r\nrebooting...\r\n"));
}


void MTD_FLASHMEM SerialConsole::cmd_free()
{
    uint32_t const totHeap  = 0x14000;
    uint32_t const freeHeap = getFreeHeap();
    uint32_t const flashDictUsedSpace = FlashDictionary::getUsedSpace();
    m_serial->printf(FSTR("                      total        used        free\r\n"));
    m_serial->printf(FSTR("Heap           :    %7d     %7d     %7d\r\n"), totHeap, totHeap - freeHeap, freeHeap);
    m_serial->printf(FSTR("Flash          :    %7d\r\n"), getFlashSize());
    m_serial->printf(FSTR("Flash settings :    %7d     %7d     %7d\r\n"), 4096, flashDictUsedSpace, 4096 - flashDictUsedSpace);
}


void MTD_FLASHMEM SerialConsole::cmd_ifconfig()
{
    m_serial->writeNewLine();
    for (int32_t i = 0; i < 2; ++i)
    {
        m_serial->printf(i == 0? FSTR("Client Network:\r\n") : FSTR("Access Point Network:\r\n"));
        uint8_t mac[6];
        WiFi::getMACAddress((WiFi::Network)i, mac);
        m_serial->printf(FSTR("   ether %02x:%02x:%02x:%02x:%02x:%02x\r\n"), mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        uint8_t IP[4];
        uint8_t netmask[4];
        uint8_t gateway[4];
        IP::getIPInfo((WiFi::Network)i, IP, netmask, gateway);
        m_serial->printf(FSTR("   inet %d.%d.%d.%d netmask %d.%d.%d.%d gateway %d.%d.%d.%d\r\n"), 
                         IP[0], IP[1], IP[2], IP[3],
                         netmask[0], netmask[1], netmask[2], netmask[3],
                         gateway[0], gateway[1], gateway[2], gateway[3]);
        if (i == 0)
        {
            // In client mode show status
            char const* connectionStatus = FSTR("");
            switch (WiFi::getClientConnectionStatus())
            {
                case WiFi::ClientConnectionStatus_Idle:
                    connectionStatus = FSTR("Idle");
                    break;
                case WiFi::ClientConnectionStatus_Connecting:
                    connectionStatus = FSTR("Connecting");
                    break;
                case WiFi::ClientConnectionStatus_WrongPassword:
                    connectionStatus = FSTR("Wrong Password");
                    break;
                case WiFi::ClientConnectionStatus_NoAPFound:
                    connectionStatus = FSTR("No AP Found");
                    break;
                case WiFi::ClientConnectionStatus_Fail:
                    connectionStatus = FSTR("Fail");
                    break;
                case WiFi::ClientConnectionStatus_GotIP:
                    connectionStatus = FSTR("Connected");
                    break;
            }
            m_serial->printf(FSTR("   status <%s>\r\n"), connectionStatus);
        }
    }
    m_serial->printf(FSTR("DNS1 %s DNS2 %s\r\n"), (char const*)NSLookup::getDNSServer(0).get_str(), 
                                                  (char const*)NSLookup::getDNSServer(1).get_str());
}

	
void MTD_FLASHMEM SerialConsole::cmd_iwlist()
{
    m_serial->printf(FSTR("\r\nCells found:\r\n"));
    uint32_t count = 0;
    bool scan = (m_paramsCount == 2 && t_strcmp(m_params[1], CharIterator(FSTR("scan"))) == 0);
    WiFi::APInfo* infos = WiFi::getAPList(&count, scan);
    for (uint32_t i = 0; i != count; ++i)
    {
        m_serial->printf(FSTR("  %2d - Address: %02X:%02X:%02X:%02X:%02X:%02X\r\n"), i, infos[i].BSSID[0], infos[i].BSSID[1], infos[i].BSSID[2], infos[i].BSSID[3], infos[i].BSSID[4], infos[i].BSSID[5]);
        m_serial->printf(FSTR("       SSID: %s\r\n"), infos[i].SSID);
        m_serial->printf(FSTR("       Channel: %d\r\n"), infos[i].Channel);
        m_serial->printf(FSTR("       RSSI: %d\r\n"), infos[i].RSSI);
        m_serial->printf(FSTR("       Security: %s\r\n"), WiFi::convSecurityProtocolToString(infos[i].AuthMode));
    }
}
    
    
void MTD_FLASHMEM SerialConsole::cmd_date()
{
    char buf[30];
    DateTime::now().format(buf, FSTR("%c"));
    m_serial->writeln(buf);
}


void MTD_FLASHMEM SerialConsole::cmd_ntpdate()
{
    char buf[30];
    DateTime dt;
    if (dt.getFromNTPServer())
    {                
        dt.format(buf, FSTR("%c"));
        m_serial->writeln(buf);
    }
    else
        m_serial->printf(FSTR("fail\r\n"));
}

    
void MTD_FLASHMEM SerialConsole::cmd_nslookup()
{
    if (m_paramsCount != 2)
    {
        m_serial->writeln(FSTR("NAME missing\r\n"));
        return;
    }
    APtr<char> name( t_strdup(m_params[1]) );
    m_serial->writeln(NSLookup::lookup(name.get()).get_str());
}
    
    
void MTD_FLASHMEM SerialConsole::cmd_uptime()
{
    int32_t seconds = DateTime::now() - ConfigurationManager::getBootDateTime();
    uint32_t days = seconds / 86400;
    seconds %= 86400;
    uint32_t hours = seconds / 3600;
    seconds %= 3600;
    uint32_t minutes = seconds / 60;
    seconds %= 60;
    m_serial->printf(FSTR("%d days, %02d:%02d:%02d\r\n"), days, hours, minutes, seconds);
}


void MTD_FLASHMEM SerialConsole::cmd_test()
{
}

    
    
    
    
#endif



} // end of "fdv" namespace

