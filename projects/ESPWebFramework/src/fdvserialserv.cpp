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



    //////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////
    // SerialConsole
        
#if (FDV_INCLUDE_SERIALCONSOLE == 1)


    typedef void (SerialConsole::*Handler)();

    struct Cmd
    {
        char const* cmd;
        char const* syntax;
        char const* description;
        Handler     handler;
    };


    Cmd const* FUNC_FLASHMEM cmdInfo(uint32_t i)
    {
        static const Cmd cmds[] =
        {
            // example:
            //   help
            //   help ifconfig
            {FSTR("help"),	     
             FSTR("[COMMAND]"), 
             FSTR("Show help"), 
             &SerialConsole::cmd_help},
             
             // example:
             //   reboot
             //   reboot 500
            {FSTR("reboot"),	 
             FSTR("[MS]"), 
             FSTR("Restart system in [MS] milliseconds"), 
             &SerialConsole::cmd_reboot},
             
            {FSTR("restore"),	 
             STR_,
             FSTR("Erase Flash stored settings"), 
             &SerialConsole::cmd_restore},
             
            {FSTR("free"),       
             STR_, 
             FSTR("Display amount of free and used memory"), 
             &SerialConsole::cmd_free},
             
             // example:
             //  ifconfig
             //  ifconfig static 192.168.1.99 255.255.255.0 192.168.1.1
             //  ifconfig dhcp
             //  ifconfig ap 192.168.5.1 255.255.255.0 192.168.5.1
             //  ifconfig dns 8.8.8.8 8.8.4.4
            {FSTR("ifconfig"),   
             FSTR("[static IP NETMASK GATEWAY] | [dhcp] | [ap IP NETMASK GATEWAY] | [dns DNS1 DNS2]"), 
             FSTR("No params: Display network info\r\n\tstatic: Set Client Mode static IP\r\n\tdhcp: Set Client Mode DHCP\r\n\tap: Set Access Point static IP\r\n\tdns: Set primary and seconday DNS server"), 
             &SerialConsole::cmd_ifconfig},
             
             // example:
             //   iwlist
             //   iwlist scan
            {FSTR("iwlist"),     
             FSTR("[scan]"), 
             FSTR("Display or scan for available wireless networks"), 
             &SerialConsole::cmd_iwlist},
             
            {STR_date,       
             STR_, 
             FSTR("Display current date/time"), 
             &SerialConsole::cmd_date},
             
             // example:
             //   ntpdate 192.168.1.10
             //   ntpdate ntp1.inrim.it
            {FSTR("ntpdate"),             
             FSTR("[SERVER]"), 
             FSTR("Display date/time from NTP server"), 
             &SerialConsole::cmd_ntpdate},
             
             // example:
             //   nslookup www.google.com
            {FSTR("nslookup"),   
             FSTR("NAME"), 
             FSTR("Query DNS"), 
             &SerialConsole::cmd_nslookup},    
             
            {STR_uptime,
             STR_, 
             FSTR("Display how long the system has been running"), 
             &SerialConsole::cmd_uptime},
             
            {FSTR("ping"),
             FSTR("SERVER"),
             FSTR("Sends ICMP ECHO_REQUEST and waits for ECHO_RESPONSE"),
             &SerialConsole::cmd_ping},
             
             // example:
             //   router on
             //   router off
            {FSTR("router"),
             FSTR("on | off"),
             FSTR("Enable/disable routing between networks"),
             &SerialConsole::cmd_router},
             
             // example:
             //   ls
             //   ls -l
            {STR_ls,
             FSTR("[-l]"), 
             FSTR("List flash directory contents"), 
             &SerialConsole::cmd_ls},

             // example:
             //   rm test.html
            {STR_rm,
             FSTR("FILENAME"), 
             FSTR("Remove a file"), 
             &SerialConsole::cmd_rm},             

             // example:
             //   cat test.html
            {STR_cat,
             FSTR("FILENAME"), 
             FSTR("Print a file"), 
             &SerialConsole::cmd_cat},             
             
             {FSTR("test"),       
             FSTR(""), FSTR(""), 
             &SerialConsole::cmd_test},
        };
        static uint32_t const cmdCount = sizeof(cmds) / sizeof(Cmd);
        if (i < cmdCount)
            return &cmds[i];
        else
            return NULL;
    }
        


        
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
        if (m_paramsCount > 0)
        {
            for (uint32_t i = 0; cmdInfo(i); ++i)
            {
                if (hasParameter(0, cmdInfo(i)->cmd))
                {
                    (this->*(cmdInfo(i)->handler))();
                    return;
                }
            }
            m_serial->writeln(FSTR("Unknown command"));
        }
    }
    
    
    bool MTD_FLASHMEM SerialConsole::hasParameter(uint32_t paramIndex, char const* str)
    {
        return t_strcmp(m_params[paramIndex], CharIterator(str)) == 0;
    }


    void MTD_FLASHMEM SerialConsole::cmd_help()
    {
        if (m_paramsCount == 1)
        {
            for (uint32_t i = 0; cmdInfo(i); ++i)
                m_serial->printf(FSTR("%s %s\r\n"), cmdInfo(i)->cmd, cmdInfo(i)->syntax);
        }
        else if (m_paramsCount == 2)
        {
            for (uint32_t i = 0; cmdInfo(i); ++i)
                if (hasParameter(1, cmdInfo(i)->cmd))
                {
                    m_serial->printf(FSTR("Syntax:\r\n\t%s %s\r\n"), cmdInfo(i)->cmd, cmdInfo(i)->syntax);
                    m_serial->printf(FSTR("Description:\r\n\t%s\r\n"), cmdInfo(i)->description);
                    break;
                }
        }
    }


    void MTD_FLASHMEM SerialConsole::cmd_restore()
    {
        m_serial->write(FSTR("Are you sure [y/N]? "));
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
        m_serial->writeln(FSTR("rebooting...\r\n"));
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
        if (m_paramsCount == 5 && hasParameter(1, FSTR("static")))
        {
            // set static IP
            APtr<char> strIP( t_strdup(m_params[2]) );
            APtr<char> strMSK( t_strdup(m_params[3]) );
            APtr<char> strGTY( t_strdup(m_params[4]) );
            ConfigurationManager::setClientIPParams(true, strIP.get(), strMSK.get(), strGTY.get());
            ConfigurationManager::applyClientIP();
        }
        else
        if (m_paramsCount == 2 && hasParameter(1, FSTR("dhcp")))
        {
            // set dyncamic IP (DHCP)
            ConfigurationManager::setClientIPParams(false, STR_, STR_, STR_);
            ConfigurationManager::applyClientIP();
        }
        else
        if (m_paramsCount == 5 && hasParameter(1, FSTR("ap")))
        {
            // set Access Point static IP
            APtr<char> strIP( t_strdup(m_params[2]) );
            APtr<char> strMSK( t_strdup(m_params[3]) );
            APtr<char> strGTY( t_strdup(m_params[4]) );
            ConfigurationManager::setAccessPointIPParams(strIP.get(), strMSK.get(), strGTY.get());
            ConfigurationManager::applyAccessPointIP();
        }        
        else
        if (m_paramsCount == 4 && hasParameter(1, FSTR("dns")))
        {
            // set DNS1 and DNS2
            APtr<char> strDNS1( t_strdup(m_params[2]) );
            APtr<char> strDNS2( t_strdup(m_params[3]) );
            ConfigurationManager::setDNSParams(IPAddress(strDNS1.get()), IPAddress(strDNS2.get()));
            ConfigurationManager::applyDNS();
        }        
        else
        {
            // show info
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
    }

        
    void MTD_FLASHMEM SerialConsole::cmd_iwlist()
    {
        m_serial->printf(FSTR("Cells found:\r\n"));
        uint32_t count = 0;
        bool scan = (m_paramsCount == 2 && hasParameter(1, FSTR("scan")));
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
        IPAddress serverIP; // default is 0.0.0.0, accepted by getFromNTPServer()
        
        // is there the SERVER parameter?
        if (m_paramsCount > 1)
        {
            APtr<char> server( t_strdup(m_params[1]) );
            serverIP = NSLookup::lookup(server.get());
        }
        
        char buf[30];
        DateTime dt;
        if (dt.getFromNTPServer(serverIP))
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
            m_serial->writeln(FSTR("Error\r\n"));
            return;
        }
        APtr<char> name( t_strdup(m_params[1]) );
        m_serial->writeln(NSLookup::lookup(name.get()).get_str());
    }
        
        
    void MTD_FLASHMEM SerialConsole::cmd_uptime()
    {
        char uptimeStr[22];
        ConfigurationManager::getUpTimeStr(uptimeStr);
        m_serial->write(uptimeStr);
    }
    
    
    void MTD_FLASHMEM SerialConsole::cmd_ping()
    {
        if (m_paramsCount != 2)
        {
            m_serial->writeln(FSTR("Error\r\n"));
            return;
        }
        APtr<char> server( t_strdup(m_params[1]) );
        IPAddress serverIP = NSLookup::lookup(server.get());
        ICMP icmp;
        while (true)
        {
            float r = icmp.ping(serverIP) / 1000.0;
            m_serial->printf(FSTR("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\r\n"), icmp.receivedBytes(), (char const*)serverIP.get_str(), icmp.receivedSeq(), icmp.receivedTTL(), r);
            
            if (m_serial->available() > 0 && m_serial->read() == 27)
                break;
            
            Task::delay(1000);
        }
    }

    
    void MTD_FLASHMEM SerialConsole::cmd_router()
    {
        if (m_paramsCount == 2)
        {
            ConfigurationManager::setRouting(hasParameter(1, FSTR("on")));
            ConfigurationManager::applyRouting();
        }
    }

            
    void MTD_FLASHMEM SerialConsole::cmd_ls()
    {
        bool longlist = (m_paramsCount == 2 && hasParameter(1, FSTR("-l")));
        FlashFileSystem::Item item;
        int16_t count = 0;
        while (FlashFileSystem::getNext(&item))
        {
            ++count;
            if (longlist)
            {
                m_serial->printf(FSTR("%5d %10s  %s\r\n"), item.datalength, item.mimetype, item.filename);
            }
            else
            {
                m_serial->printf(FSTR("%20s"), item.filename);
                if (count % 4 == 0)
                    m_serial->writeNewLine();
            }            
        }
        m_serial->writeNewLine();
    }


    void MTD_FLASHMEM SerialConsole::cmd_rm()
    {
        if (m_paramsCount == 2)
        {
            APtr<char> filename( t_strdup(m_params[1]) );
            if (!FlashFileSystem::remove(filename.get()))
                m_serial->writeln(STR_File_not_found);
        }
    }
    
    
    void MTD_FLASHMEM SerialConsole::cmd_cat()
    {
        if (m_paramsCount == 2)
        {
            APtr<char> filename( t_strdup(m_params[1]) );
            FlashFileSystem::Item item;
            if (FlashFileSystem::find(filename.get(), &item))
            {
                m_serial->write((uint8_t const*)item.data, item.datalength);
                m_serial->writeNewLine();
            }
            else
                m_serial->writeln(STR_File_not_found);
        }
    }

            
    void MTD_FLASHMEM SerialConsole::cmd_test()
    {
    }

        
        
#endif




	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	// SerialBinary

#if (FDV_INCLUDE_SERIALBINARY == 1)
    



	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	// SerialBinary::Message


    MTD_FLASHMEM SerialBinary::Message::Message()
        : valid(false), ID(0), command(0), dataSize(0), data(NULL)
    {
    }
    
    
    MTD_FLASHMEM SerialBinary::Message::Message(uint8_t ID_, uint8_t command_, uint16_t dataSize_)
        : valid(true), ID(ID_), command(command_), dataSize(dataSize_), data(dataSize_? new uint8_t[dataSize_] : NULL)
    {
    }
    
    
    MTD_FLASHMEM SerialBinary::Message::Message(uint8_t ID_, uint8_t command_, uint8_t* data_, uint16_t dataSize_)
        : valid(true), ID(ID_), command(command_), data(data_), dataSize(dataSize_)
    {
    }
    

    void MTD_FLASHMEM SerialBinary::Message::freeData()
    {
        if (data != NULL)
        {
            delete[] data;
            data = NULL;
        }
    }
			           
       

	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
    
    MTD_FLASHMEM SerialBinary::SerialBinary()
        : m_serial(HardwareSerial::getSerial(0)), 
          m_recvID(255), 
          m_sendID(0), 
          m_recvACKQueue(ACKMSG_QUEUE_LENGTH), 
          m_receiveTask(this, false, 256),
          m_isReady(false),
          m_platform(PLATFORM_BASELINE),
          m_HTTPRoutes(NULL)
    {
        checkReady();
    }
    
    
    MTD_FLASHMEM SerialBinary::~SerialBinary()
    {
        m_receiveTask.terminate();
        delete m_HTTPRoutes;
        // todo: free pending messages
    }


    bool MTD_FLASHMEM SerialBinary::isReady()
    {
        MutexLock lock(&m_mutex);
        return m_isReady;
    }
    
    
    bool MTD_FLASHMEM SerialBinary::checkReady()
    {
        if (!isReady())
            send_CMD_READY();
        return isReady();
    }
    

    uint8_t MTD_FLASHMEM SerialBinary::getPlatform()
    {
        checkReady();
        MutexLock lock(&m_mutex);
        return m_platform;
    }
    
    
    StringList* MTD_FLASHMEM SerialBinary::getHTTPRoutes()
    {
        MutexLock lock(&m_himutex);
        if (m_HTTPRoutes == NULL)   // already requested?
        {
            // request handled pages
            m_HTTPRoutes = new StringList;
            if (!send_CMD_GETHTTPHANDLEDPAGES())
            {
                // get a chance to retry            
                delete m_HTTPRoutes;    
                m_HTTPRoutes = NULL;
            }
        }
        return m_HTTPRoutes;
    }
    
    
    SerialBinary::Message MTD_FLASHMEM SerialBinary::receive()
    {
        Message msg;
        SoftTimeOut timeout(WAIT_MSG_TIMEOUT);
        while (!timeout)
        {
            // ID
            int16_t r = m_serial->read(INTRA_MSG_TIMEOUT);
            if (r < 0)
                continue;
            msg.ID = r;

            // Command
            r = m_serial->read(INTRA_MSG_TIMEOUT);
            if (r < 0)
                continue;
            msg.command = r;

            // Data Size Low
            r = m_serial->read(INTRA_MSG_TIMEOUT);
            if (r < 0)
                continue;
            msg.dataSize = r;

            // Data Size High
            r = m_serial->read(INTRA_MSG_TIMEOUT);
            if (r < 0)
                continue;
            msg.dataSize |= r << 8;

            // Data			
            if (msg.dataSize > 0 && msg.dataSize < (Task::getFreeHeap() >> 1))
            {
                msg.data = new uint8_t[msg.dataSize];
                if (m_serial->read(msg.data, msg.dataSize, INTRA_MSG_TIMEOUT) < msg.dataSize)
                {
                    msg.freeData();
                    continue;
                }
            }
            
            // check ID
            if (msg.ID == m_recvID)
            {
                msg.freeData();
                continue;
            }
            m_recvID = msg.ID;
            
            msg.valid = true;
            return msg;
        }			
        return msg;
    }
    
    
    uint8_t MTD_FLASHMEM SerialBinary::getNextID()
    {
        MutexLock lock(&m_mutex);
        return ++m_sendID;
    }
    

    void MTD_FLASHMEM SerialBinary::send(Message const& msg)
    {
        MutexLock lock(&m_mutex);
        m_serial->write(msg.ID);
        m_serial->write(msg.command);
        m_serial->write(msg.dataSize & 0xFF);
        m_serial->write((msg.dataSize >> 8) & 0xFF);
        if (msg.dataSize > 0)
            m_serial->write(msg.data, msg.dataSize);
    }
    
    
    // send ACK without parameters
    void MTD_FLASHMEM SerialBinary::sendNoParamsACK(uint8_t ackID)
    {
        uint8_t data[1] = {ackID};
        send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
    }
    
    
    SerialBinary::Message MTD_FLASHMEM SerialBinary::waitACK(uint8_t ackID)
    {
        Message msg;
        SoftTimeOut timeout(GETACK_TIMEOUT);
        while (!timeout)
        {
            if (m_recvACKQueue.receive(&msg, GETACK_TIMEOUT))
            {
                uint8_t msgAckID = msg.data[0];
                if (msgAckID == ackID)
                    return msg;
                msg.freeData();	// discard this ACK
            }
        }
        msg.valid = false;
        return msg;
    }
    

    bool MTD_FLASHMEM SerialBinary::waitNoParamsACK(uint8_t ackID)
    {
        Message msg = waitACK(ackID);
        if (msg.valid)
        {
            msg.freeData();
            return true;
        }
        return false;
    }		
    
    
    void MTD_FLASHMEM SerialBinary::receiveTask()
    {
        while (true)
        {
            Message msg = receive();
            if (msg.valid)
            {
                if (msg.command == CMD_ACK)
                    // if message is an ACK then put it into the ACK message queue, another task will handle it
                    m_recvACKQueue.send(msg, PUTACK_TIMEOUT);
                else
                    processMessage(&msg);
            }
        }
    }
    
    
    // must not process CMD_ACK messages
    void MTD_FLASHMEM SerialBinary::processMessage(SerialBinary::Message* msg)
    {
        switch (msg->command)
        {
            case CMD_READY:
                handle_CMD_READY(msg);
                break;
            case CMD_IOCONF:
                handle_CMD_IOCONF(msg);
                break;
            case CMD_IOSET:
                handle_CMD_IOSET(msg);
                break;
            case CMD_IOGET:
                handle_CMD_IOGET(msg);
                break;
            case CMD_IOASET:
                handle_CMD_IOASET(msg);
                break;
            case CMD_STREAMSTART:
                handle_CMD_STREAMSTART(msg);
                break;
        }			
        msg->freeData();
    }
    
    
    void MTD_FLASHMEM SerialBinary::handle_CMD_READY(Message* msg)
    {
        // process message
        m_mutex.lock();
        uint8_t protocolVersion = msg->data[0];
        m_platform              = msg->data[1];
        char const* magicString = (char const*)msg->data + 2;
        m_isReady = (protocolVersion == PROTOCOL_VERSION && f_strcmp(magicString, STR_BINPRORDY) == 0);
        m_mutex.unlock();
        
        // send ACK with parameters
        uint8_t data[13] = {msg->ID, PROTOCOL_VERSION, PLATFORM_THIS};
        f_strcpy((char*)data + 3, STR_BINPRORDY);
        send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
    }
    
    
    void MTD_FLASHMEM SerialBinary::handle_CMD_STREAMSTART(Message* msg)
    {
        // send simple ACK
        sendNoParamsACK(msg->ID);
        // this is the main action of this message: suspend receive task.
        // The receive task (actually THIS task) must be activate manually when
        // all the stream has been received.
        m_receiveTask.suspend();        
    }
    
    
    void MTD_FLASHMEM SerialBinary::handle_CMD_IOCONF(Message* msg)
    {
        // process message
        uint8_t pin   = msg->data[0];
        uint8_t flags = msg->data[1];
        if (flags & PIN_CONF_OUTPUT)
            GPIOX(pin).modeOutput();
        else
            GPIOX(pin).modeInput();
        GPIOX(pin).enablePullUp(flags & PIN_CONF_PULLUP);
                    
        // send simple ACK
        sendNoParamsACK(msg->ID);
    }
    

    void MTD_FLASHMEM SerialBinary::handle_CMD_IOSET(Message* msg)
    {
        // process message
        uint8_t pin   = msg->data[0];
        uint8_t state = msg->data[1];
        GPIOX(pin).write(state);
        
        // send simple ACK
        sendNoParamsACK(msg->ID);
    }
    
    
    void MTD_FLASHMEM SerialBinary::handle_CMD_IOGET(Message* msg)
    {
        // process message
        uint8_t pin = msg->data[0];
        bool state = GPIOX(pin).read();
        
        // send ACK with parameters
        uint8_t data[2] = {msg->ID, state};
        send(Message(getNextID(), CMD_ACK, data, sizeof(data)));
    }
    
    
    // not implemented
    void MTD_FLASHMEM SerialBinary::handle_CMD_IOASET(Message* msg)
    {
        // process message
        // not implemented
        
        // send simple ACK
        sendNoParamsACK(msg->ID);
    }
    
    
    bool MTD_FLASHMEM SerialBinary::send_CMD_READY()
    {
        m_isReady = false;
        for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
        {
            // send message            
            uint8_t data[12] = {PROTOCOL_VERSION, PLATFORM_THIS};
            f_strcpy((char*)data + 2, STR_BINPRORDY);
            uint8_t msgID = getNextID();
            send(Message(msgID, CMD_READY, data, sizeof(data)));            
            
            // wait for ACK
            Message msg = waitACK(msgID);
            if (msg.valid)
            {
                MutexLock lock(&m_mutex);
                uint8_t protocolVersion = msg.data[1];
                m_platform = msg.data[2];
                char const* magicString = (char const*)msg.data + 3;
                m_isReady = (protocolVersion == PROTOCOL_VERSION && f_strcmp(magicString, STR_BINPRORDY) == 0);
                msg.freeData();
                return true;
            }
        }
        return false;
    }
    
    
    bool MTD_FLASHMEM SerialBinary::send_CMD_IOCONF(uint8_t pin, uint8_t flags)
    {
        if (checkReady())
        {
            for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
            {
                // send message                
                uint8_t data[2] = {pin, flags};
                uint8_t msgID = getNextID();
                send(Message(msgID, CMD_IOCONF, data, sizeof(data)));
                
                // wait for ACK
                if (waitNoParamsACK(msgID))
                    return true;
            }
            m_isReady = false;	// no more ready
        }
        return false;
    }
    
    
    bool MTD_FLASHMEM SerialBinary::send_CMD_IOSET(uint8_t pin, uint8_t state)
    {
        if (checkReady())
        {
            for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
            {
                // send message                
                uint8_t data[2] = {pin, state};                
                uint8_t msgID = getNextID();
                send(Message(msgID, CMD_IOSET, data, sizeof(data)));
                
                // wait for ACK
                if (waitNoParamsACK(msgID))
                    return true;
            }
            m_isReady = false;	// no more ready
        }
        return false;
    }
    
    
    bool MTD_FLASHMEM SerialBinary::send_CMD_IOGET(uint8_t pin, uint8_t* state)
    {
        if (checkReady())
        {
            for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
            {
                // send message
                uint8_t data[1] = {pin};
                uint8_t msgID = getNextID();
                send(Message(msgID, CMD_IOGET, data, sizeof(data)));
                
                // wait for ACK
                Message msg = waitACK(msgID);
                if (msg.valid)
                {
                    *state = msg.data[1];
                    msg.freeData();
                    return true;
                }
            }
            m_isReady = false;	// no more ready
        }
        return false;
    }

    
    bool MTD_FLASHMEM SerialBinary::send_CMD_IOASET(uint8_t pin, uint16_t state)
    {
        if (checkReady())
        {
            for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
            {
                // send message
                uint8_t data[3] = {pin, state & 0xFF, state >> 8};
                uint8_t msgID = getNextID();
                send(Message(msgID, CMD_IOASET, data, sizeof(data)));
                
                // wait for ACK
                if (waitNoParamsACK(msgID))
                    return true;
            }
            m_isReady = false;	// no more ready
        }
        return false;
    }
    
    
    bool MTD_FLASHMEM SerialBinary::send_CMD_IOAGET(uint8_t pin, uint16_t* state)
    {
        if (checkReady())
        {
            for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
            {
                // send message
                uint8_t data[1] = {pin};
                uint8_t msgID = getNextID();
                send(Message(msgID, CMD_IOAGET, data, sizeof(data)));
                
                // wait for ACK
                Message msg = waitACK(msgID);
                if (msg.valid)
                {
                    *state = msg.data[1] + (msg.data[2] << 8);
                    msg.freeData();
                    return true;
                }
            }
            m_isReady = false;	// no more ready
        }
        return false;
    }
    
    
    bool MTD_FLASHMEM SerialBinary::send_CMD_GETHTTPHANDLEDPAGES()
    {
        m_HTTPRoutes->clear();
        if (checkReady())
        {
            for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
            {
                // send message
                uint8_t msgID = getNextID();
                send(Message(msgID, CMD_GETHTTPHANDLEDPAGES, NULL, 0));
                
                // wait for ACK
                Message msg = waitACK(msgID);
                if (msg.valid)
                {
                    uint8_t const* rpos = msg.data + 1;
                    uint8_t itemsCount = *rpos++;
                    for (uint8_t j = 0; j != itemsCount; ++j)
                    {
                        m_HTTPRoutes->add((char const*)rpos, StringList::Heap);
                        rpos += strlen((char const*)rpos) + 1;
                    }
                    msg.freeData();
                    return true;
                }
            }
            m_isReady = false;	// no more ready
        }
        return false;        
    }
    
    
    // wpos can be NULL (to just calculate total length)
    // return copied bytes
    uint32_t FUNC_FLASHMEM copyFields(HTTPHandler::Fields& fields, uint8_t** wpos)
    {
        uint32_t len = 0;
        for (uint32_t i = 0; i != fields.getItemsCount(); ++i)
        {
            uint32_t keylen = t_strlen(fields[i]->key) + 1;
            uint32_t vallen = t_strlen(fields[i]->value) + 1;
            len += keylen + vallen;
            if (wpos)
            {
                t_strcpy((char*)*wpos, fields[i]->key);
                *wpos += keylen;
                t_strcpy((char*)*wpos, fields[i]->value);
                *wpos += vallen;
            }
        }
        return len;
    }
    
    
    bool MTD_FLASHMEM SerialBinary::send_CMD_HTTPREQUEST(uint8_t pageIndex, HTTPHandler* handler)
    {
        MutexLock lock(&m_himutex);
        if (checkReady())
        {
            for (uint32_t i = 0; i != MAX_RESEND_COUNT; ++i)
            {                
                uint8_t msgID = getNextID();
             
                // calculate message payload length
                uint32_t msglen = 5;    // (1) method, (1) page index, (1) headers fields count, (1) query fields count, (1) form fields count
                msglen += t_strlen(handler->getRequest().requestedPage) + 1;    // page len
                msglen += copyFields(handler->getRequest().headers, NULL);      // headers len
                msglen += copyFields(handler->getRequest().query, NULL);        // query len
                msglen += copyFields(handler->getRequest().form , NULL);        // form len
                
                //// prepare message
                Message msg(msgID, CMD_HTTPREQUEST, msglen);
                uint8_t* wpos = msg.data;
                
                // method
                *wpos++ = (uint8_t)handler->getRequest().method;
                
                // page index
                *wpos++ = pageIndex;
                
                // page (zero terminated string)
                t_strcpy((char*)wpos, handler->getRequest().requestedPage);
                wpos += t_strlen(handler->getRequest().requestedPage) + 1;
                
                // header fields
                *wpos++ = handler->getRequest().headers.getItemsCount();
                copyFields(handler->getRequest().headers, &wpos);
                
                // query fields
                *wpos++ = handler->getRequest().query.getItemsCount();
                copyFields(handler->getRequest().query, &wpos);
                
                // form fields
                *wpos++ = handler->getRequest().form.getItemsCount();
                copyFields(handler->getRequest().form, &wpos);
                
                // send message
                send(msg);
                msg.freeData();
                
                // wait for ACK
                msg = waitACK(msgID);
                if (msg.valid)
                {
                    uint8_t const* rpos = msg.data + 1;
                    
                    // read status and initialize response object
                    uint8_t status = *rpos++;
                    char const* statusStr = STR_200_OK; 
                    switch (status)
                    {
                        case HTTPSTATUS_301:
                            statusStr = STR_301_Moved_Permanently;
                            break;
                        case HTTPSTATUS_302:
                            statusStr = STR_302_Found;
                            break;
                        case HTTPSTATUS_400:
                            statusStr = STR_400_Bad_Request;
                            break;
                        case HTTPSTATUS_401:
                            statusStr = STR_401_Unauthorized;
                            break;
                        case HTTPSTATUS_403:
                            statusStr = STR_403_Forbidden;
                            break;
                        case HTTPSTATUS_404:
                            statusStr = STR_404_Not_Found;
                            break;
                    }
                    HTTPResponse response(handler, statusStr);
                    
                    // read and add additional headers
                    uint8_t headersCount = *rpos++;
                    for (uint8_t i = 0; i != headersCount; ++i)
                    {
                        char const* headerKey = (char const*)rpos;
                        rpos += t_strlen(headerKey) + 1;
                        char const* headerValue = (char const*)rpos;
                        rpos += t_strlen(headerValue) + 1;
                        response.addHeader(headerKey, headerValue);
                    }
                    
                    // content-type header (if not unspecified)
                    uint8_t contentType = *rpos++;
                    switch (contentType)
                    {
                        case HTTPCONTENTTYPE_TEXTHTML:
                            response.addHeader(STR_Content_Type, STR_TEXTHTML);
                            break;
                        case HTTPCONTENTTYPE_TEXTHTML_UTF8:
                            response.addHeader(STR_Content_Type, STR_TEXTHTML_UTF8);
                            break;
                        case HTTPCONTENTTYPE_APPJSON:
                            response.addHeader(STR_Content_Type, STR_APPJSON);
                            break;
                        case HTTPCONTENTTYPE_TEXTPLAIN:
                            response.addHeader(STR_Content_Type, STR_TEXTPLAIN);
                            break;
                        case HTTPCONTENTTYPE_TEXTXML:
                            response.addHeader(STR_Content_Type, STR_TEXTXML);
                            break;
                    }
                    
                    uint8_t contentMode = *rpos++;
                    
                    switch (contentMode)
                    {
                        case 0:
                        {
                            ///// Content embedded in the ACK message
                            
                            // Content length and content data
                            uint16_t contentLen = *rpos + (*(rpos + 1) << 8);
                            rpos += 2;
                            response.addContent(rpos, contentLen);
                            
                            // flush headers and content
                            response.flush();
                            break;
                        }
                            
                        case 1:
                        {
                            ///// Content not embedded in the ACK, known size
                                                                           
                            // flush headers only
                            uint16_t contentLen = *rpos + (*(rpos + 1) << 8);
                            response.flushHeaders(contentLen);
                            
                            // wait for CMD_STREAMSTART
                            SoftTimeOut timeout(WAIT_MSG_TIMEOUT);
                            while (!timeout && !m_receiveTask.suspended())
                                Task::delay(5);
                            if (m_receiveTask.suspended())
                            {
                                // receiver task correctly suspended, now process content stream
                                MutexLock lock(&m_mutex);                            
                                
                                // get content from serial and put into the socket                            
                                // todo: transfer using blocks instead of byte by byte
                                for (uint16_t i = 0; i != contentLen; ++i)
                                {
                                    int16_t r = m_serial->read(INTRA_MSG_TIMEOUT);
                                    if (r < 0)
                                        break;
                                    uint8_t b = r;
                                    handler->getSocket()->write(&b, 1);
                                }
                                m_receiveTask.resume();
                            }
                            break;
                        }
                            
                        case 2:
                        {
                            ///// Content not embedded in the ACK, unknown size
                            // wait for CMD_STREAMSTART
                            SoftTimeOut timeout(WAIT_MSG_TIMEOUT);
                            while (!timeout && !m_receiveTask.suspended())
                                Task::delay(5);
                            if (m_receiveTask.suspended())
                            {
                                // receiver task correctly suspended, now process content stream
                                MutexLock lock(&m_mutex);                            
                                
                                LinkedCharChunks chunks;
                                while (true)
                                {
                                    int16_t r = m_serial->read(INTRA_MSG_TIMEOUT);
                                    if (r <= 0) // -1 or 0x00 interrupt
                                        break;
                                    chunks.append((char)r, 32); // todo: increase?
                                }
                                m_receiveTask.resume();
                                response.addContent(&chunks);
                                response.flush();                                
                            }
                            break;
                        }
                    }
                    
                    msg.freeData();
                    return true;
                }
            }
            m_isReady = false; // no more ready            
        }
        return false;
    }
    
    



#endif


} // end of "fdv" namespace

