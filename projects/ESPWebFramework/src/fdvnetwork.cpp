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


extern "C"
{
	#include "lwip/ip_addr.h"
	#include "lwip/sockets.h"
	#include "lwip/dns.h"
	#include "lwip/netdb.h"
	#include "lwip/api.h"
	#include "lwip/netbuf.h"
    #include "lwip/inet.h"
    #include "lwip/netif/etharp.h"

	#include <stdarg.h>
}



namespace fdv
{


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
    // IPAddress

    
    void MTD_FLASHMEM IPAddress::operator=(IPAddress const& c)
    {
        address[0] = c.address[0];
        address[1] = c.address[1];
        address[2] = c.address[2];
        address[3] = c.address[3];            
    }
    
    
    void MTD_FLASHMEM IPAddress::operator=(in_addr inaddr)
    {
        address[0] = ((uint8_t*)&inaddr.s_addr)[0];
        address[1] = ((uint8_t*)&inaddr.s_addr)[1];
        address[2] = ((uint8_t*)&inaddr.s_addr)[2];
        address[3] = ((uint8_t*)&inaddr.s_addr)[3];
    }
    
    
    void MTD_FLASHMEM IPAddress::operator=(in_addr_t inaddr)
    {
        address[0] = ((uint8_t*)&inaddr)[0];
        address[1] = ((uint8_t*)&inaddr)[1];
        address[2] = ((uint8_t*)&inaddr)[2];
        address[3] = ((uint8_t*)&inaddr)[3];
    }
    
    
    void MTD_FLASHMEM IPAddress::operator=(ip_addr_t ipaddr)
    {
        address[0] = ((uint8_t*)&ipaddr)[0];
        address[1] = ((uint8_t*)&ipaddr)[1];
        address[2] = ((uint8_t*)&ipaddr)[2];
        address[3] = ((uint8_t*)&ipaddr)[3];
    }
    
    
    void MTD_FLASHMEM IPAddress::operator=(char const* str)
    {
        if (!str || f_strlen(str) == 0)
            *this = IPAddress(0, 0, 0, 0);
        else
            *this = IPAddress(ipaddr_addr(APtr<char>(f_strdup(str)).get()));
    }
    
    
    in_addr_t MTD_FLASHMEM IPAddress::get_in_addr_t() const
    {
        in_addr_t a;
        ((uint8_t*)&a)[0] = address[0];
        ((uint8_t*)&a)[1] = address[1];
        ((uint8_t*)&a)[2] = address[2];
        ((uint8_t*)&a)[3] = address[3];
        return a;
    }
    
    ip_addr_t MTD_FLASHMEM IPAddress::get_ip_addr_t() const
    {
        ip_addr_t a;
        ((uint8_t*)&a.addr)[0] = address[0];
        ((uint8_t*)&a.addr)[1] = address[1];
        ((uint8_t*)&a.addr)[2] = address[2];
        ((uint8_t*)&a.addr)[3] = address[3];
        return a;
    }
    
    uint32_t MTD_FLASHMEM IPAddress::get_uint32() const
    {
        uint32_t a;
        ((uint8_t*)&a)[0] = address[0];
        ((uint8_t*)&a)[1] = address[1];
        ((uint8_t*)&a)[2] = address[2];
        ((uint8_t*)&a)[3] = address[3];
        return a;
    }
    
    IPAddress::IPAddressStr MTD_FLASHMEM IPAddress::get_str() const
    {
        IPAddressStr str;
        ip_addr_t a = get_ip_addr_t();
        ipaddr_ntoa_r(&a, (char*)str, 16);
        return str;
    }
    
    bool MTD_FLASHMEM IPAddress::operator==(IPAddress const& rhs) const
    {
        return address[0] == rhs.address[0] && address[1] == rhs.address[1] &&
               address[2] == rhs.address[2] && address[3] == rhs.address[3];
    }
    
    bool MTD_FLASHMEM IPAddress::operator!=(IPAddress const& rhs) const
    {
        return !(*this == rhs);
    }
    


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// WiFi
	
    
    WiFi::Mode STC_FLASHMEM WiFi::setMode(Mode mode)
    {
        Critical critical;
        wifi_set_opmode(mode);
    }
    
    
    WiFi::Mode STC_FLASHMEM WiFi::getMode()
    {
        Mode mode = (Mode)wifi_get_opmode();
        return mode;
    }
    
    
    char const* STC_FLASHMEM WiFi::convSecurityProtocolToString(SecurityProtocol securityProtocol)
    {
        char const* authMode = STR_;
        switch (securityProtocol)
        {
            case WiFi::Open:
                authMode = FSTR("Open");
                break;
            case WiFi::WEP:
                authMode = FSTR("WEP");
                break;
            case WiFi::WPA_PSK:
                authMode = FSTR("WPA-PSK");
                break;
            case WiFi::WPA2_PSK:
                authMode = FSTR("WPA2-PSK");
                break;
            case WiFi::WPA_WPA2_PSK:
                authMode = FSTR("WPA-WPA2-PSK");
                break;
        }
        return authMode;
    }			

    
    // setMode must be called with AccessPoint or ClientAndAccessPoint
    // note: make sure there is enough stack space free otherwise mail cause reset (fatal exception)!
    // channel: 1..13
    void STC_FLASHMEM WiFi::configureAccessPoint(char const* SSID, char const* securityKey, uint8_t channel, SecurityProtocol securityProtocol, bool hiddenSSID)
    {						
        softap_config config = {0};
        wifi_softap_get_config(&config);
        f_strcpy((char *)config.ssid, SSID);
        config.ssid_len = f_strlen(SSID);
        f_strcpy((char *)config.password, securityKey);
        config.channel = channel;
        config.authmode = (AUTH_MODE)securityProtocol;
        config.ssid_hidden = (uint8)hiddenSSID;
        Critical critical;
        wifi_softap_set_config(&config);
    }
    
    
    // setMode must be called with Client or ClientAndAccessPoint
    void STC_FLASHMEM WiFi::configureClient(char const* SSID, char const* securityKey)
    {
        station_config config = {0};
        f_strcpy((char *)config.ssid, SSID);
        f_strcpy((char *)config.password, securityKey);
        Critical critical;
        wifi_station_disconnect();
        wifi_station_set_config(&config);
        wifi_station_connect();
    }
    
    
    // fills MAC with MAC address of the specified network
    // MAC must be a pointer to 6 bytes buffer
    void STC_FLASHMEM WiFi::getMACAddress(WiFi::Network network, uint8_t* MAC)
    {
        wifi_get_macaddr((uint8_t)network, MAC);
    }
    
    
    WiFi::ClientConnectionStatus STC_FLASHMEM WiFi::getClientConnectionStatus()
    {
        return (ClientConnectionStatus)wifi_station_get_connect_status();
    }
    
    
    // returns access point list
    WiFi::APInfo* STC_FLASHMEM WiFi::getAPList(uint32_t* count, bool rescan)
    {
        if (rescan)
        {
            if (getMode() == AccessPoint)
                setMode(ClientAndAccessPoint);
            wifi_station_scan(NULL, scanDoneCB);
            getAPInfo()->receive();	// wait for completion
        }
        APInfo* infos;
        getAPInfo(&infos, count);
        if (*count == 0)
        {
            // retry
            return getAPList(count, true);
        }
        return infos;
    }

    
    void STC_FLASHMEM WiFi::scanDoneCB(void* arg, STATUS status)
    {
        if (status == OK)
        {
            // count items
            uint32_t count = 0;
            for (bss_info* bss_link = ((bss_info*)arg)->next.stqe_next; bss_link; bss_link = bss_link->next.stqe_next)
                ++count;
            // fill items
            APInfo* infos;
            getAPInfo(&infos, &count, count);
            for (bss_info* bss_link = ((bss_info*)arg)->next.stqe_next; bss_link; bss_link = bss_link->next.stqe_next, ++infos)
            {
                memcpy(infos->BSSID, bss_link->bssid, 6);
                memset(infos->SSID, 0, 33);
                memcpy(infos->SSID, bss_link->ssid, 32);
                infos->Channel  = bss_link->channel;
                infos->RSSI     = bss_link->rssi;
                infos->AuthMode = (SecurityProtocol)bss_link->authmode;
                infos->isHidden = (bool)bss_link->is_hidden;
            }
            getAPInfo()->signal();
        }
    }
    
    
    // allocateCount >= 0 -> allocate (or reallocate or free) AP info
    // allocateCount < 0  -> get infos
    Queue<bool>* STC_FLASHMEM WiFi::getAPInfo(APInfo** infos, uint32_t* count, int32_t allocateCount)
    {
        static bool         s_init  = false;
        static APInfo*      s_infos = NULL;
        static uint32_t     s_count = 0;
        static Queue<bool>* s_queue;
        if (!s_init)
        {
            s_queue = new Queue<bool>(1);	// never deleted        
            s_init = true;
        }
        if (allocateCount >= 0)
        {
            if (s_infos != NULL)
                delete[] s_infos;
            s_infos = NULL;
            s_count = 0;
            if (allocateCount > 0)
            {
                s_infos = new APInfo[allocateCount];
                s_count = allocateCount;
            }
        }
        if (infos && count)
        {
            *infos = s_infos;
            *count = s_count;
        }
        return s_queue;
    }
		


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// IP
	
    void STC_FLASHMEM IP::configureStatic(WiFi::Network network, char const* IP, char const* netmask, char const* gateway)
    {
        ip_info info;
        info.ip.addr      = ipaddr_addr(APtr<char>(f_strdup(IP)).get());
        info.netmask.addr = ipaddr_addr(APtr<char>(f_strdup(netmask)).get());
        info.gw.addr      = ipaddr_addr(APtr<char>(f_strdup(gateway)).get());
        
        Critical critical;
        wifi_station_dhcpc_stop();
        wifi_softap_dhcps_stop();
        wifi_set_ip_info(network, &info);
    }
    
    
    // applies only to ClientNetwork
    void STC_FLASHMEM IP::configureDHCP(WiFi::Network network)
    {
        if (network == WiFi::ClientNetwork)
        {
            Critical critical;
            wifi_station_dhcpc_start();
        }
    }
    
    
    // fills IP with IP address of the specified network
    // IP, netmask, gateway must be a pointer to 4 bytes buffer
    void STC_FLASHMEM IP::getIPInfo(WiFi::Network network, uint8_t* IP, uint8_t* netmask, uint8_t* gateway)
    {
        ip_info info;
        wifi_get_ip_info(network, &info);
        for (uint32_t i = 0; i != 4; ++i)
        {
            IP[i]      = ((uint8_t*)&info.ip.addr)[i];
            netmask[i] = ((uint8_t*)&info.netmask.addr)[i];
            gateway[i] = ((uint8_t*)&info.gw.addr)[i];
        }
    }
		
        
        
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// DHCPServer
	
    // warn: each IP in the range requires memory!
    void STC_FLASHMEM DHCPServer::configure(char const* startIP, char const* endIP)
    {		
        wifi_softap_dhcps_stop();
        
        dhcps_lease lease;
        lease.start_ip = IPAddress(startIP).get_ip_addr_t();
        lease.end_ip   = IPAddress(endIP).get_ip_addr_t();
        wifi_softap_set_dhcps_lease(&lease);
        
        uint8_t mode = 1;
        wifi_softap_set_dhcps_offer_option(OFFER_ROUTER, &mode);
        
        wifi_softap_dhcps_start();
    }    
        
        

   	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
    // NSLookup (DNS client)
    
    
    MTD_FLASHMEM NSLookup::NSLookup(char const* hostname)
    {    
        m_ipaddr = lookup(hostname);
    }
    
    
    // returns IPAddress(0, 0, 0, 0) on fail
    IPAddress MTD_FLASHMEM NSLookup::lookup(char const* hostname)
    {
        APtr<char> memHostName( f_strdup(hostname) );
        addrinfo* addrinfo;
        if (lwip_getaddrinfo(memHostName.get(), NULL, NULL, &addrinfo) == 0 && addrinfo)
        {
            // according to lwip documentation uses only first item of "addrinfo"
            sockaddr_in* sa = (sockaddr_in*)(addrinfo->ai_addr);
            in_addr_t addr = sa->sin_addr.s_addr;
            lwip_freeaddrinfo(addrinfo);
            return IPAddress(addr);
        }
        return IPAddress(0, 0, 0, 0);   // fail!
    }
    
    
    IPAddress MTD_FLASHMEM NSLookup::get()
    {
        return m_ipaddr;
    }
    
    
    void MTD_FLASHMEM NSLookup::setDNSServer(uint32_t num, IPAddress server)
    {
        ip_addr_t a = server.get_ip_addr_t();
        dns_setserver(num, &a);
    }
    
    
    IPAddress MTD_FLASHMEM NSLookup::getDNSServer(uint32_t num)
    {
        return IPAddress(dns_getserver(num));
    }
    

        

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
    // Socket

    
    // ret -1 = error, ret 0 = disconnected
    int32_t MTD_FLASHMEM Socket::read(void* buffer, uint32_t maxLength)
    {
        int32_t bytesRecv = lwip_recv(m_socket, buffer, maxLength, 0);
        if (maxLength > 0)
            m_connected = (bytesRecv > 0);
        return bytesRecv;
    }
    
    // ret 1 = error
    int32_t MTD_FLASHMEM Socket::read(void* buffer, uint32_t maxLength, IPAddress* sourceAddress, uint16_t* sourcePort)
    {
        sockaddr_in from;
        int fromlen;
        int32_t bytesRecv = lwip_recvfrom(m_socket, buffer, maxLength, 0, (sockaddr*)&from, (socklen_t*)&fromlen);
        if (bytesRecv > 0)
        {
            *sourceAddress = IPAddress(from.sin_addr.s_addr);
            *sourcePort    = ntohs(from.sin_port);
        }
        return bytesRecv;
    }
    
    // ret -1 = error, ret 0 = disconnected
    int32_t MTD_FLASHMEM Socket::peek(void* buffer, uint32_t maxLength, bool nowait)
    {
        int32_t flags = MSG_PEEK | (nowait? MSG_DONTWAIT : 0);
        int32_t bytesRecv = lwip_recv(m_socket, buffer, maxLength, flags);
        if (maxLength > 0 && !nowait)
            m_connected = (bytesRecv > 0);
        return bytesRecv;
    }
    
    
    bool MTD_FLASHMEM Socket::checkConnection()
    {
        uint8_t b;
        peek(&b, 1, true);
        int32_t lr = getLastError();
        return (lr == 0 || lr == EAGAIN) && isConnected();
    }
    
    
    // buffer can stay in RAM of Flash
    // ret -1 = error, ret 0 = disconnected
    int32_t MTD_FLASHMEM Socket::write(void const* buffer, uint32_t length)
    {
        static uint32_t const MAXCHUNKSIZE = 128;
        
        if (!checkConnection())
            return -1;
        
        int32_t bytesSent = 0;
        // send in chunks of up to MAXCHUNKSIZE bytes
        uint8_t rambuf[min(length, MAXCHUNKSIZE)];
        uint8_t const* src = (uint8_t const*)buffer;
        while (bytesSent < length)
        {
            uint32_t bytesToSend = min(MAXCHUNKSIZE, length - bytesSent);
            f_memcpy(rambuf, src, bytesToSend);
            int32_t chunkBytesSent = m_remoteAddress.sin_len == 0? lwip_send(m_socket, rambuf, bytesToSend, MSG_DONTWAIT) :
                                                                   lwip_sendto(m_socket, rambuf, bytesToSend, 0, (sockaddr*)&m_remoteAddress, sizeof(m_remoteAddress));
            int32_t lasterr = getLastError();                
            if (lasterr == EAGAIN || lasterr == EWOULDBLOCK)
            {
                chunkBytesSent = 0;
            }
            else if (chunkBytesSent <= 0 || lasterr != 0)
            {
                // error
                bytesSent = -1;
                break;
            }
            bytesSent += chunkBytesSent;
            src += chunkBytesSent;
        }
        if (length > 0)
            m_connected = (bytesSent > 0);
        return bytesSent;
    }
    
    
    // str can stay in RAM of Flash
    // ret -1 = error, ret 0 = disconnected
    int32_t MTD_FLASHMEM Socket::write(char const* str)
    {
        return write((uint8_t const*)str, f_strlen(str));
    }
    
    
    // like printf
    // buf can stay in RAM or Flash
    // "strings" of args can stay in RAM or Flash
    uint16_t MTD_FLASHMEM Socket::writeFmt(char const *fmt, ...)
    {
        va_list args;
        
        va_start(args, fmt);
        uint16_t len = vsprintf(NULL, fmt, args);
        va_end(args);

        char buf[len + 1];
        
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        va_end(args);
        
        write(buf, len);

        return len;
    }
    
    
    void MTD_FLASHMEM Socket::close()
    {        
        if (m_socket > 0)
        {            
            lwip_shutdown(m_socket, SHUT_RDWR);
            lwip_close(m_socket);
            m_socket = 0;
        }
        m_connected = false;
    }
    

    void MTD_FLASHMEM Socket::setNoDelay(bool value)
    {
        int32_t one = (int32_t)value;
        lwip_setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));
    }

    
    
    // from now Socket will use "sendto" instead of "send"
    void MTD_FLASHMEM Socket::setRemoteAddress(IPAddress remoteAddress, uint16_t remotePort)
    {
        memset(&m_remoteAddress, 0, sizeof(sockaddr_in));
        m_remoteAddress.sin_family      = AF_INET;
        m_remoteAddress.sin_len         = sizeof(sockaddr_in);
        m_remoteAddress.sin_addr.s_addr = remoteAddress.get_in_addr_t();
        m_remoteAddress.sin_port        = htons(remotePort);
    }
    
    
    // timeOut in ms (0 = no timeout)
    void MTD_FLASHMEM Socket::setTimeOut(uint32_t timeOut)
    {
        lwip_setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (void *)&timeOut, sizeof(timeOut));
    }
    
    
    int32_t MTD_FLASHMEM Socket::getLastError()
    {
        int32_t r = 0;
        socklen_t l = sizeof(int32_t);
        lwip_getsockopt(m_socket, SOL_SOCKET, SO_ERROR, (void *)&r, &l);
        return r;
    }
    
    
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPResponse
	
    MTD_FLASHMEM HTTPResponse::HTTPResponse(HTTPHandler* httpHandler, char const* status, char const* content)
        : m_httpHandler(httpHandler), m_status(status), m_headersFlushed(false)
    {
        // content (if present, otherwise use addContent())
        if (content)
            addContent(content);
    }
    
    
    HTTPHandler::Request& MTD_FLASHMEM HTTPResponse::getRequest()
    {
        return m_httpHandler->getRequest();
    }
    
    
    // accept RAM or Flash strings
    void MTD_FLASHMEM HTTPResponse::addHeader(char const* key, char const* value)
    {
        m_headers.add(key, value);
    }
    
    
    // accept RAM or Flash data
    void MTD_FLASHMEM HTTPResponse::addContent(void const* data, uint32_t length, bool freeOnDestroy)
    {
        m_content.addChunk((char*)data, length, freeOnDestroy);
    }
    
    
    // accept RAM or Flash strings
    // WARN: data is not copied! Just a pointer is stored
    // can be called many times
    void MTD_FLASHMEM HTTPResponse::addContent(char const* str, bool freeOnDestroy)
    {
        addContent(str, f_strlen(str), freeOnDestroy);
    }
      
      
    // can be called many times
    // WARN: src content is not copied! Just data pointers are stored
    void MTD_FLASHMEM HTTPResponse::addContent(LinkedCharChunks* src)
    {
        m_content.addChunks(src);
    }
            
            
    void MTD_FLASHMEM HTTPResponse::flushHeaders(uint32_t contentLength)
    {
        if (!m_headersFlushed)
        {
            // status line
            m_httpHandler->getSocket()->writeFmt(FSTR("HTTP/1.1 %s\r\n"), m_status);

            // HTTPResponse headers
            addHeader(FSTR("Connection"), FSTR("close"));			

            // user headers
            for (uint32_t i = 0; i != m_headers.getItemsCount(); ++i)
            {
                Fields::Item* item = m_headers[i];
                m_httpHandler->getSocket()->writeFmt(FSTR("%s: %s\r\n"), APtr<char>(t_strdup(item->key)).get(), APtr<char>(t_strdup(item->value)).get());
            }

            // content length header
            m_httpHandler->getSocket()->writeFmt(FSTR("%s: %d\r\n\r\n"), STR_Content_Length, contentLength);

            m_headersFlushed = true;
        }
    }
    
            
    // should be called only after setStatus, addHeader and addContent
    void MTD_FLASHMEM HTTPResponse::flush()
    {
        // headers
        flushHeaders(m_content.getItemsCount());
        
        // actual content
        if (m_content.getItemsCount() > 0)
        {			
            CharChunksIterator iter = m_content.getIterator();
            CharChunkBase* chunk = iter.getCurrentChunk();
            while (chunk)
            {
                if (m_httpHandler->getSocket()->write((uint8_t const*)chunk->data, chunk->getItems()) < 0)
                    break;
                chunk = iter.moveToNextChunk();
            }
            m_content.clear();
        }
    }
    
    

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// ParameterReplacer

    MTD_FLASHMEM ParameterReplacer::ParameterReplacer()
        : m_params(NULL), m_blockParams(NULL), m_strStart(NULL), m_strEnd(NULL)
    {
        m_results.add(new LinkedCharChunks);
    }
    
    
    MTD_FLASHMEM ParameterReplacer::~ParameterReplacer()
    {
        for (uint32_t i = 0; i != m_results.size(); ++i)
            delete m_results[i];
    }
    
	
    void MTD_FLASHMEM ParameterReplacer::start(char const* strStart, char const* strEnd, Params* params, BlockParams* blockParams)
    {
        m_params      = params;
        m_blockParams = blockParams;
        m_strStart    = strStart;
        m_strEnd      = strEnd;
        processInput();
    }
    
    
	void MTD_FLASHMEM ParameterReplacer::processInput()
	{
		char const* curc  = m_strStart;
		char const* start = curc;
		char const* curBlockKey      = NULL;
		char const* curBlockKeyEnd   = NULL;
		while (curc != m_strEnd)
		{
			char c0 = getChar(curc);
			if (c0 == '{')
			{
				char c1 = getChar(curc + 1);
				if (c1 == '{')
				{
					// found "{{"
					// push previous content
					m_results.last()->addChunk(start, curc - start, false);
					// process parameter tag
					start = curc = replaceTag(curc);
					continue;
				}
				else if (c1 == '%')
				{
					// found "{%"
					// push previous content
					if (curBlockKey && curBlockKeyEnd)
					{
						m_results.last()->addChunk(start, curc - start, false);
						m_blocks.add(curBlockKey, curBlockKeyEnd, m_results.last());
                        m_results.add(new LinkedCharChunks);
					}
					// process block tag
					curBlockKey = extractTagStr(curc, &curBlockKeyEnd);
					start = curc = curBlockKeyEnd + 2;	// bypass "%}"
					// if this is the first block tag then this is the template file name
					if (m_template.get() == NULL)
					{
						m_template.reset(f_strdup(curBlockKey, curBlockKeyEnd));
						curBlockKey = NULL;
						curBlockKeyEnd = NULL;
					}
					continue;
				}
			}
			++curc;
		}
		m_results.last()->addChunk(start, m_strEnd - start, false);
		if (curBlockKey && curBlockKeyEnd)
		{
			m_blocks.add(curBlockKey, curBlockKeyEnd, m_results.last());
		}			
	}
	

	char const* MTD_FLASHMEM ParameterReplacer::replaceTag(char const* curc)
	{
		char const* tagEnd;
		char const* tagStart = extractTagStr(curc, &tagEnd);
		if (getChar(tagStart) == '#')
		{
			// replace multiple parameters ('0param', '1param', ...)
			++tagStart;			
			uint32_t tagLen = tagEnd - tagStart;
			char tag[tagLen];
			f_memcpy(tag, tagStart, tagLen);
			tag[tagLen] = 0;
			for (uint32_t index = 0; ; ++index)
			{
				char const* fulltagname = f_printf(FSTR("%d%s"), index, tag);
				Params::Item* item = m_params->getItem(fulltagname);
				if (item)
					m_results.last()->addChunks(&item->value); // push parameter content
				else
					break;
			}
		}
		else
		{
			// replace one parameter
			Params::Item* item = m_params->getItem(tagStart, tagEnd);
			if (item)				
				m_results.last()->addChunks(&item->value); // push parameter content
            else if(m_blockParams)
            {
                BlockParams::Item* item = m_blockParams->getItem(tagStart, tagEnd);
                if (item)
                    m_results.last()->addChunks(item->value);   // push block parameter content
            }
		}
		return tagEnd + 2;	// bypass "}}"
	}
	
	
	char const* MTD_FLASHMEM ParameterReplacer::extractTagStr(char const* curc, char const** tagEnd)
	{
		char const* tagStart = curc + 2; // by pass "{{" or "{%"
		*tagEnd = tagStart;
		while (*tagEnd < m_strEnd && getChar(*tagEnd) != '}' && getChar(*tagEnd) != '%')
			++*tagEnd;
		return tagStart;
	}
	

    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPTemplateResponse

    
    MTD_FLASHMEM HTTPTemplateResponse::HTTPTemplateResponse(HTTPHandler* httpHandler, char const* filename)
        : HTTPResponse(httpHandler, NULL), m_filename(filename)
    {			
    }
    

    void MTD_FLASHMEM HTTPTemplateResponse::addParamStr(char const* key, char const* value)
    {
        LinkedCharChunks* linkedCharChunks = m_params.add(key);
        linkedCharChunks->addChunk(value);
    }
    
    
    void MTD_FLASHMEM HTTPTemplateResponse::addParamInt(char const* key, int32_t value)
    {
        char* valueStr = f_printf(FSTR("%d"), value);
        LinkedCharChunks* linkedCharChunks = m_params.add(key);
        linkedCharChunks->addChunk(valueStr, f_strlen(valueStr), true);	// true = need to free
    }
    
    
    void MTD_FLASHMEM HTTPTemplateResponse::addParamFmt(char const* key, char const *fmt, ...)
    {
        va_list args;			
        va_start(args, fmt);
        uint16_t len = vsprintf(NULL, fmt, args);
        va_end(args);
        char* buf = new char[len + 1];
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        va_end(args);
        
        LinkedCharChunks* linkedCharChunks = m_params.add(key);
        linkedCharChunks->addChunk(buf, len, true);	// true = need to free
    }
    
    
    LinkedCharChunks* MTD_FLASHMEM HTTPTemplateResponse::addParamCharChunks(char const* key)
    {
        return m_params.add(key);
    }
    
    
    HTTPTemplateResponse::Params* MTD_FLASHMEM HTTPTemplateResponse::getParams()
    {
        return &m_params;
    }
    
    
    void MTD_FLASHMEM HTTPTemplateResponse::flush()
    {        
        // {{now}} predefined parameter : display date/time
        char datetimeStr[34];
        DateTime::now().format(datetimeStr, FSTR("%c"));
        addParamStr(STR_now, datetimeStr);
        
        // {{uptime}} predefined parameter : display uptime
        char uptimeStr[22];
        ConfigurationManager::getUpTimeStr(uptimeStr);
        addParamStr(STR_uptime, uptimeStr);

        processFileRequest();
        HTTPResponse::flush();
    }
    

    void MTD_FLASHMEM HTTPTemplateResponse::processFileRequest()
    {
        FlashFileSystem::Item file;
        if (m_filename && FlashFileSystem::find(m_filename, &file))
        {
            // found
            setStatus(STR_200_OK);
            addHeader(STR_Content_Type, FSTR("text/html"));
            
            // replace parameters
            m_replacer.start((char const*)file.data, (char const*)file.data + file.datalength, &m_params, NULL);
            
            // is this a specialized file (contains {%..%} blocks)?
            if (m_replacer.getBlocks()->getItemsCount() > 0 && m_replacer.getTemplateFilename() != NULL)
            {
                // this is a specialized file
                // load template file
                file.reset();
                if (FlashFileSystem::find(m_replacer.getTemplateFilename(), &file))
                {
                    // replace parameters and blocks of template file
                    m_templateReplacer.start((char const*)file.data, (char const*)file.data + file.datalength, &m_params, m_replacer.getBlocks());
                    // flush resulting content
                    addContent(m_templateReplacer.getResult());
                    return;
                }
            }
            else
            {
                // just flush this file (contains only {{...}} blocks)
                addContent(m_replacer.getResult());
                return;
            }
        }
        // not found
        setStatus(STR_404_Not_Found);
    }
    
    
    
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// UDPClient
    
    MTD_FLASHMEM UDPClient::UDPClient(IPAddress remoteAddress, uint16_t remotePort)
    {
        init(remoteAddress, remotePort);
    }
    
    
    MTD_FLASHMEM UDPClient::~UDPClient()
    {
        m_socket.close();
    }
    
    
    void MTD_FLASHMEM UDPClient::init(IPAddress remoteAddress, uint16_t remotePort)
    {
        m_socket = lwip_socket(AF_INET, SOCK_DGRAM, 0);
        
        sockaddr_in localAddress     = {0};
        localAddress.sin_family      = AF_INET;
        localAddress.sin_len         = sizeof(sockaddr_in);
        localAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        localAddress.sin_port        = htons(getUDPPort());
        lwip_bind(m_socket.getSocket(), (sockaddr*)&localAddress, sizeof(sockaddr_in));			
        
        m_socket.setRemoteAddress(remoteAddress, remotePort);
    }

    
    uint16_t MTD_FLASHMEM UDPClient::getUDPPort()
    {
        static uint16_t s_port = 59999;
        s_port = (++s_port == 0? 60000 : s_port);
        return s_port;
    }
    
    
    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    // SNTPClient

    // serverIP is a uint8_t[4] IP address or NULL
    MTD_FLASHMEM SNTPClient::SNTPClient(IPAddress serverIP, uint16_t port)
        : m_server(serverIP), m_port(port)
    {
    }
    
    
    bool MTD_FLASHMEM SNTPClient::query(uint64_t* outValue) const
    {
      // send req (mode 3), unicast, version 4
      uint8_t const MODE_CLIENT   = 3;
      uint8_t const VERSION       = 4;
      uint8_t const BUFLEN        = 48;
      uint32_t const REPLYTIMEOUT = 3000;
      uint8_t buf[BUFLEN];
      memset(&buf[0], 0, BUFLEN);
      buf[0] = MODE_CLIENT | (VERSION << 3);
      
      UDPClient UDP(m_server, m_port);
      Socket* socket = UDP.getSocket();
      socket->setTimeOut(REPLYTIMEOUT);
      
      if (socket->write(&buf[0], BUFLEN))
      {
        // get reply
        if (socket->read(&buf[0], BUFLEN) == BUFLEN)
        {
          memcpy(outValue, &buf[40], sizeof(uint64_t));
          return true;  // ok
        }
      }

      return false;  // error
    }

    
 
    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    // ICMP
    
    MTD_FLASHMEM ICMP::ICMP()
        : m_waitingID(rand() & 0xFFFF), m_waitingSeq(0), m_queue(1)
    {
    }
    
    
    int32_t MTD_FLASHMEM ICMP::ping(IPAddress const& dest)
    {       
        static uint32_t const TIMEOUT        = 4000;
        static int32_t const TIMEOUT_RESULT  = -1;
    
        uint32_t result = TIMEOUT_RESULT;
                
        // generate seq
        m_waitingSeq++;
        
        // prepare packet to send
        pbuf* hdrbuf = pbuf_alloc(PBUF_IP, sizeof(icmp_echo_hdr), PBUF_RAM);
        icmp_echo_hdr* hdr = (icmp_echo_hdr*)hdrbuf->payload;
        hdr->type   = ICMP_ECHO;
        hdr->code   = 0;
        hdr->chksum = 0;
        hdr->id     = htons(m_waitingID);
        hdr->seqno  = htons(m_waitingSeq);
        hdr->chksum = inet_chksum((uint16_t*)hdr, sizeof(icmp_echo_hdr));
        
        // send Echo request
        raw_pcb* pcb = raw_new(IP_PROTO_ICMP);
        raw_recv(pcb, ICMP::raw_recv_fn, this);
        raw_bind(pcb, IP_ADDR_ANY);            
        
        ip_addr_t addr = dest.get_ip_addr_t();
        raw_sendto(pcb, hdrbuf, &addr);
        pbuf_free(hdrbuf);
        
        uint32_t t1 = micros();
        if (m_queue.receive(TIMEOUT))
            result = (micros() - t1);
                
        raw_remove(pcb);
        
        return result;            
    }

    
    uint8_t STC_FLASHMEM ICMP::raw_recv_fn(void *arg, raw_pcb *pcb, pbuf *p, ip_addr_t *addr)
    {
        ICMP* this_ = (ICMP*)arg;
        
        ip_hdr *iphdr = (ip_hdr*)p->payload;
        
        uint16_t ttl = IPH_TTL(iphdr);
        
        if (p->tot_len >= PBUF_IP_HLEN + sizeof(icmp_echo_hdr) && pbuf_header(p, -PBUF_IP_HLEN) == 0)
        {
            icmp_echo_hdr* hdr = (icmp_echo_hdr*)p->payload;
            if (ntohs(hdr->id) == this_->m_waitingID && ntohs(hdr->seqno) == this_->m_waitingSeq)
            {
                this_->m_receivedBytes = p->tot_len;
                this_->m_receivedTTL   = ttl;
                this_->m_queue.signal();
                pbuf_free(p);
                return 1;
            }
        }
        
        return 0;
    }    



    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    // NetInterface
    
    netif* NetInterface::get(uint32_t index)
    {
        char name[4] = "enX";
        name[2] = '0' + index;
        return netif_find(name);
    }

        

    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    // Router
    
    netif_input_fn Router::s_prevInput[INTFCOUNT];
    
    bool Router::s_enabled = false;
    
    
    void MTD_FLASHMEM Router::enable()
    {
        if (!s_enabled)
        {
            Critical critical;
            for (uint32_t i = 0; i != INTFCOUNT; ++i)
            {
                netif* en = NetInterface::get(i);
                if (en)
                {
                    s_prevInput[i] = en->input;
                    en->input = Router::netif_input;
                }
                else
                    s_prevInput[i] = NULL;
            }
            s_enabled = true;
        }
    }
    
    
    void MTD_FLASHMEM Router::disable()
    {
        if (s_enabled)
        {
            Critical critical;
            for (uint32_t i = 0; i != INTFCOUNT; ++i)
            {
                netif* en = NetInterface::get(i);
                if (en && s_prevInput[i])
                    en->input = s_prevInput[i];
            }
            s_enabled = false;
        }
    }
    
    
    // remove MTD_FLASHMEM to speedup routing
    err_t MTD_FLASHMEM Router::netif_input(pbuf *p, netif *inp)
    {
        eth_hdr* ethdr = (eth_hdr*)p->payload;
        
        if (ntohs(ethdr->type) == ETHTYPE_IP)
        {

            // move buffer pointer to start of IP header
            pbuf_header(p, -sizeof(eth_hdr));
            ip_hdr* iphdr = (ip_hdr*)(p->payload);
            
            // needs to route?
            // 1. check match of source interface IP/netmask and destination IP
            bool route = ((iphdr->dest.addr & inp->netmask.addr) != (inp->ip_addr.addr & inp->netmask.addr));
            // 2. check if not multicast or broadcast (>=224.0.0.0 up to 255.255.255.255)
            route = route && ((iphdr->dest.addr & 0xE0) != 0xE0);
            
            if (route)
            {
                /*
                debug("netif_input intf=%d len=%d id=%d prot=%d src=%s dst=%s route?=%c\r\n", 
                      inp->num, p->tot_len, IPH_ID(iphdr), IPH_PROTO(iphdr),
                      (char const*)IPAddress(iphdr->src.addr).get_str(),
                      (char const*)IPAddress(iphdr->dest.addr).get_str(),
                      route?'Y':'N');
                */
                
                // find destination interface
                ip_addr_t ipdest;
                ipdest.addr = iphdr->dest.addr;
                netif* destIntf = ip_route(&ipdest);
                
                // decrement TTL
                IPH_TTL_SET(iphdr, IPH_TTL(iphdr) - 1);
                
                if (IPH_TTL(iphdr) > 0)
                {
                    // update IP checksum
                    if (IPH_CHKSUM(iphdr) >= PP_HTONS(0xffffU - 0x100))
                        IPH_CHKSUM_SET(iphdr, IPH_CHKSUM(iphdr) + PP_HTONS(0x100) + 1);
                    else
                        IPH_CHKSUM_SET(iphdr, IPH_CHKSUM(iphdr) + PP_HTONS(0x100));
                
                    // send the packet
                    ip_output_if(p, NULL, IP_HDRINCL, 0, 0, 0, destIntf);
                }
                      
                pbuf_free(p);
                return ERR_OK;
            }

            // restore buffer pointer to start of Ethernet header
            pbuf_header(p, +sizeof(eth_hdr));
        }
              
        return (Router::s_prevInput[inp->num])(p, inp);
    }
    
    
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// TCPConnectionHandler
    
    void MTD_FLASHMEM TCPConnectionHandler::exec()
    {
        while (true)
        {
            if (m_socketQueue->receive(&m_socket))
            {
                connectionHandler();
                m_socket.close();
            }
        }
    }
    
    

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
    // MultipartFormDataProcessor
    
    class MultipartFormDataProcessor
    {
        public:
            // Sequence is: WaitingForFirstBoundary -> {BoundaryFound -> DecodingHeaders -> (GettingValue | GettingFile)} -> EndOfContent
            enum States {WaitingForFirstBoundary, BoundaryFound, DecodingHeaders, GettingValue, GettingFile, EndOfContent};
            
            static uint32_t const HEADERS_CHUNK_SIZE = 16;
            static uint32_t const FORM_CHUNK_SIZE    = 16;
            
            char const*            boundary;
            int32_t                boundarylen;
            States                 state;
            int32_t                substate;
            LinkedCharChunks*      headers;
            HTTPHandler::Fields*   formfields;    
            LinkedCharChunks*      valueStorage;
            CharChunksIterator     nameBegin, nameEnd;
            FlashFile              file;
            List<LinkedCharChunks> chunksFactory;   // handles creation and destruction of "headers" and "valueStorage" multiple instances
            
            MultipartFormDataProcessor(char const* boundary_, HTTPHandler::Fields* formfields_);
            void push(char c);
            
        private:
            void handle_WaitingForFirstBoundary(char c);
            void handle_BoundaryFound(char c);
            void handle_DecodingHeaders(char c);
            void handle_GettingFile_GettingValue(char c);
            bool extractParameter(char const* name, CharChunksIterator curpos, CharChunksIterator* nameBegin, CharChunksIterator* begin, CharChunksIterator* end);
            CharChunksIterator getFilename(CharChunksIterator fullpathBegin, CharChunksIterator fullpathEnd);
    };
        
    MTD_FLASHMEM MultipartFormDataProcessor::MultipartFormDataProcessor(char const* boundary_, HTTPHandler::Fields* formfields_)
        : boundary(boundary_), boundarylen(f_strlen(boundary)), state(WaitingForFirstBoundary), substate(0), formfields(formfields_)
    {
    }
    
    MTD_FLASHMEM bool MultipartFormDataProcessor::extractParameter(char const* name, CharChunksIterator curpos, CharChunksIterator* nameBegin, CharChunksIterator* begin, CharChunksIterator* end)
    {
        *nameBegin = t_strstr(curpos, CharIterator(name));
        if (*nameBegin != CharChunksIterator())
        {
            // bypass "name"
            CharChunksIterator it = *nameBegin + f_strlen(name);    
            
            // bypass spaces and a quote
            bool hasQuote = false;
            for (; it != CharChunksIterator() && (isspace(*it) || *it == '"'); ++it)
                if (*it == '"')
                    hasQuote = true;
            *begin = it;
            
            // look for spaces or a quote
            while (it != CharChunksIterator() && ((!hasQuote && !isspace(*it)) || (hasQuote && *it != '"')))
                ++it;
            *end = it;

            return true;
        }
        return false;
    }
    
    // returns filename, bypassing the file path
    CharChunksIterator MTD_FLASHMEM MultipartFormDataProcessor::getFilename(CharChunksIterator fullpathBegin, CharChunksIterator fullpathEnd)
    {
        CharChunksIterator filenameBegin = fullpathBegin;
        while (fullpathBegin != fullpathEnd)
        {
            if (*fullpathBegin == '\\' | *fullpathBegin == '/')
                filenameBegin = fullpathBegin + 1;
            ++fullpathBegin;
        }
        return filenameBegin;
    }
    
    void MTD_FLASHMEM MultipartFormDataProcessor::handle_WaitingForFirstBoundary(char c)
    {
        if (substate < 2)
        {
            // bypass first "--"
            ++substate;
        }
        else if (c == boundary[substate - 2])
        {
            ++substate;
            if (substate - 2 == boundarylen)
            {
                // found initial boundary
                state = BoundaryFound;
                substate = 0;
            }
        }
        else
        {
            // reset boundary matching (this should not happen)
            substate = 0;
        }
    }
    
    void MTD_FLASHMEM MultipartFormDataProcessor::handle_BoundaryFound(char c)
    {
        static char const EOL[2] = {0x0D, 0x0A};
        static char const EOE[4] = {'-', '-', 0x0D, 0x0A};  // end of content (just after the ending boundary)
        if (c == EOL[substate])
        {
            ++substate;
            if (substate == 2)
            {
                // found \r\n after boundary
                state = DecodingHeaders;
                substate = 0;
                headers = chunksFactory.add();
            }
        }
        else if (c == EOE[substate])
        {
            ++substate;
            if (substate == 4)
            {
                // found "--\r\n" after boundary
                state = EndOfContent;
                substate = 0;
            }
        }
    }
    
    void MTD_FLASHMEM MultipartFormDataProcessor::handle_DecodingHeaders(char c)
    {
        static char const EOH[4] = {0x0D, 0x0A, 0x0D, 0x0A};
        if (c == EOH[substate])
        {
            ++substate;
            if (substate == 2)
            {
                // useful if this is not an EOH to separate headers
                headers->append(0x0D, 1);
            }
            else if (substate == 4)
            {
                // end of headers
                headers->append(0, 1);   // add string terminating zero
                
                // look for "name" parameter
                CharChunksIterator keyBegin;
                extractParameter(FSTR(" name="), headers->getIterator(), &keyBegin, &nameBegin, &nameEnd);
                
                // look for "filename" parameter
                CharChunksIterator filenameBegin, filenameEnd;
                
                if (extractParameter(FSTR(" filename="), headers->getIterator(), &keyBegin, &filenameBegin, &filenameEnd))
                {
                    //// this is a file
                    
                    // add "filename" to form fields
                    filenameBegin = getFilename(filenameBegin, filenameEnd);    // some browsers send a full path instead of a simple file name (IE)
                    formfields->add(keyBegin + 1, keyBegin + 9, filenameBegin, filenameEnd);
                    
                    // extract Content-Type parameter
                    CharChunksIterator contentTypeBegin, contentTypeEnd;
                    extractParameter(FSTR("Content-Type:"), filenameEnd, &keyBegin, &contentTypeBegin, &contentTypeEnd);                    
                    
                    // add "Content-Type" to form fields
                    formfields->add(keyBegin, keyBegin + 12, contentTypeBegin, contentTypeEnd);

                    // create file
                    file.create(APtr<char>(t_strdup(filenameBegin, filenameEnd)).get(), APtr<char>(t_strdup(contentTypeBegin, contentTypeEnd)).get());
                    
                    state = GettingFile;                    
                }
                else
                {
                    //// this is a normal field
                    valueStorage = chunksFactory.add();
                    state = GettingValue;
                }
                substate = 0;
            }
        }
        else
        {
            // add to headers buffer
            headers->append(c, HEADERS_CHUNK_SIZE);
            substate = 0;
        }
    }
    
    void MTD_FLASHMEM MultipartFormDataProcessor::handle_GettingFile_GettingValue(char c)
    {
        static char const BOB[4] = {0x0D, 0x0A, '-', '-'};  // begin of boundary (just before every boundary)
        if (substate < 4 && c == BOB[substate])
        {
            ++substate;
        }
        else if (substate >= 4 && c == boundary[substate - 4])
        {
            ++substate;
            if (substate - 4 == boundarylen)
            {
                // found boundary, end file or value
                if (state == GettingFile)
                    file.close();
                else
                    formfields->add(nameBegin, nameEnd, valueStorage->getIterator(), CharChunksIterator());
                state = BoundaryFound;
                substate = 0;
            }
        }
        else
        {
            if (substate > 0)
            {
                // first "substate" bytes seemed the BOB or Boundary, but they were not!
                int32_t cnt = substate;
                substate = 0;
                if (state == GettingFile)
                    file.write(BOB, 1);
                else
                    valueStorage->append(BOB[0], FORM_CHUNK_SIZE);
                for (int32_t i = 1; i != cnt; ++i)
                    push( i < 4? BOB[i] : boundary[i - 4] );
                push(c);
            }
            else
            {
                if (state == GettingFile)
                    file.write(&c, 1);
                else
                    valueStorage->append(c, FORM_CHUNK_SIZE);
            }
        }
    }
    
    void MTD_FLASHMEM MultipartFormDataProcessor::push(char c)
    {                
        switch (state)
        {
            case WaitingForFirstBoundary:
                handle_WaitingForFirstBoundary(c);
                break;
            case BoundaryFound:
                handle_BoundaryFound(c);
                break;
            case DecodingHeaders:
                handle_DecodingHeaders(c);
                break;
            case GettingFile:
            case GettingValue:
                handle_GettingFile_GettingValue(c);
                break;
        }
    }
    

    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPHandler
    
    void MTD_FLASHMEM HTTPHandler::connectionHandler()
    {			
        getSocket()->setTimeOut(TIMEOUT);
        while (getSocket()->isConnected())
        {
            CharChunkBase* chunk = m_receivedData.addChunk(CHUNK_CAPACITY);
            int32_t bytesRecv = getSocket()->read(chunk->data, CHUNK_CAPACITY);
            if (bytesRecv <= 0)
                break;
            chunk->setItems(bytesRecv);
            if (processRequest())
                break;
        }
        m_receivedData.clear();
        m_request.query.clear();
        m_request.headers.clear();
        m_request.form.clear();
    }
    
    
    bool MTD_FLASHMEM HTTPHandler::processRequest()
    {			
        // look for 0x0D 0x0A 0x0D 0x0A
        CharChunksIterator headerEnd = t_strstr(m_receivedData.getIterator(), CharChunksIterator(), CharIterator(FSTR("\x0D\x0A\x0D\x0A")));
        if (headerEnd.isValid())
        {
            // move header end after CRLFCRLF
            headerEnd += 4;
            
            CharChunksIterator curc = m_receivedData.getIterator();
            
            // extract method (GET, POST, etc..)				
            CharChunksIterator method = curc;
            while (curc != headerEnd && *curc != ' ')
                ++curc;
            *curc++ = 0;	// ends method
            if (t_strcmp(method, CharIterator(FSTR("GET"))) == 0)
                m_request.method = Get;
            else if (t_strcmp(method, CharIterator(FSTR("POST"))) == 0)
                m_request.method = Post;
            else if (t_strcmp(method, CharIterator(FSTR("HEAD"))) == 0)
                m_request.method = Head;
            else
                m_request.method = Unsupported;
            
            // extract requested page and query parameters
            m_request.requestedPage = curc;
            while (curc != headerEnd)
            {
                if (*curc == '?')
                {
                    *curc++ = 0;	// ends requestedPage
                    curc = extractURLEncodedFields(curc, headerEnd, &m_request.query);
                    break;
                }
                else if (*curc == ' ')
                {
                    *curc++ = 0;	// ends requestedPage
                    break;
                }
                ++curc;
            }					
            
            // bypass HTTP version
            while (curc != headerEnd && *curc != 0x0D)
                ++curc;
                            
            // extract headers
            curc = extractHeaders(curc, headerEnd, &m_request.headers);
            
            // get content length (may be NULL)
            char const* contentLengthStr = m_request.headers[STR_Content_Length];
            int32_t contentLength = contentLengthStr? strtol(contentLengthStr, NULL, 10) : 0;
            
            // check content type
            char const* contentType = m_request.headers[STR_Content_Type];
            if (contentType && f_strstr(contentType, FSTR("multipart/form-data")))
            {
                //// content type is multipart/form-data
                processMultipartFormData(headerEnd, contentLength, contentType);
            }            
            else if (contentType == NULL || (contentType && f_strstr(contentType, FSTR("application/x-www-form-urlencoded"))))
            {
                //// content type is application/x-www-form-urlencoded
                processXWWWFormUrlEncoded(headerEnd, contentLength);
            }
            
            return true;
        }
        else
        {
            // header is not complete
            return false;
        }
    }
    
    
    void MTD_FLASHMEM HTTPHandler::processMultipartFormData(CharChunksIterator headerEnd, int32_t contentLength, char const* contentType)
    {
        char const* boundary = f_strstr(contentType, FSTR("boundary="));
        if (boundary)
        {
            // go to begin of boundary string
            boundary += 9;
            
            MultipartFormDataProcessor proc(boundary, &m_request.form);
            
            // consume already received data
            CharChunksIterator contentStart = headerEnd;
            while (contentStart != CharChunksIterator())
                proc.push(*contentStart++);

            // consume new data
            while (getSocket()->isConnected() && proc.state != MultipartFormDataProcessor::EndOfContent)
            {
                char c;
                int32_t bytesRecv = getSocket()->read(&c, 1);
                if (bytesRecv <= 0)
                    break;
                proc.push(c);
            }
            
            dispatch();
        }
    }
    
    
    void MTD_FLASHMEM HTTPHandler::processXWWWFormUrlEncoded(CharChunksIterator headerEnd, int32_t contentLength)
    {
        // look for data (maybe POST data)                
        if (contentLength > 0)
        {
            // download additional content                    
            int32_t missingBytes = headerEnd.getPosition() + contentLength - m_receivedData.getItemsCount();
            while (getSocket()->isConnected() && missingBytes > 0)
            {
                int32_t bytesToRead = (CHUNK_CAPACITY < missingBytes? CHUNK_CAPACITY : missingBytes);
                CharChunkBase* chunk = m_receivedData.addChunk(bytesToRead);
                int32_t bytesRecv = getSocket()->read(chunk->data, bytesToRead);
                if (bytesRecv <= 0)
                    break;
                chunk->setItems(bytesRecv);
                missingBytes -= chunk->getItems();
            }
            m_receivedData.append(0);	// add additional terminating "0"

            CharChunksIterator contentStart = m_receivedData.getIterator();	// cannot use directly headerEnd because added data
            contentStart += headerEnd.getPosition();
            extractURLEncodedFields(contentStart, CharChunksIterator(), &m_request.form);
        }
        
        dispatch();                
    }
    
    
    CharChunksIterator MTD_FLASHMEM HTTPHandler::extractURLEncodedFields(CharChunksIterator begin, CharChunksIterator end, Fields* fields)
    {
        fields->setUrlDecode(true);
        CharChunksIterator curc = begin;
        CharChunksIterator key = curc;
        CharChunksIterator value;
        while (curc != end)
        {
            if (*curc == '=')
            {
                *curc = 0;	// ends key
                value = curc;
                ++value;	// bypass '='
            }
            else if (*curc == '&' || *curc == ' ' || curc.isLast())
            {
                bool endLoop = (*curc == ' ' || curc.isLast());
                *curc++ = 0; // zero-ends value
                if (key.isValid() && value.isValid())
                {		
                    fields->add(key, value);	        // store parameter
                    key = value = CharChunksIterator(); // reset
                }
                if (endLoop)
                    break;
                key = curc;
            }
            else
                ++curc;
        }
        return curc;
    }
    
    
    CharChunksIterator MTD_FLASHMEM HTTPHandler::extractHeaders(CharChunksIterator begin, CharChunksIterator end, Fields* fields)
    {		
        CharChunksIterator curc = begin;
        CharChunksIterator key;
        CharChunksIterator value;
        while (curc != end)
        {
            if (*curc == 0x0D && key.isValid() && value.isValid())  // CR?
            {
                *curc = 0;	// ends key
                // store header
                fields->add(key, value);
                key = value = CharChunksIterator(); // reset
            }					
            else if (!isspace(*curc) && !key.isValid())
            {
                // bookmark "key"
                key = curc;
            }
            else if (!value.isValid() && *curc == ':')
            {
                *curc++ = 0;	// ends value
                // bypass spaces
                while (curc != end && isspace(*curc))
                    ++curc;
                // bookmark value
                value = curc;
            }
            ++curc;					
        }
        return curc;
    }
    
    
    void MTD_FLASHMEM HTTPHandler::dispatch()
    {
        for (uint32_t i = 0; i != m_routesCount; ++i)
        {
            if (f_strcmp(FSTR("*"), m_routes[i].page) == 0 || t_strcmp(m_request.requestedPage, CharIterator(m_routes[i].page)) == 0)
            {
                (this->*m_routes[i].pageHandler)();
                return;
            }
        }
        // not found (routes should always have route "*" to handle 404 not found)
    }
    
    
    void MTD_FLASHMEM HTTPHandler::setRoutes(Route const* routes, uint32_t routesCount)
    {
        m_routes      = routes;
        m_routesCount = routesCount;
    }
    
    
    
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	// HTTPStaticFileResponse
    
    void MTD_FLASHMEM HTTPStaticFileResponse::flush()
    {
        FlashFileSystem::Item file;
        if (FlashFileSystem::find(m_filename.get(), &file))
        {
            // found				
            setStatus(STR_200_OK);
            addHeader(STR_Content_Type, file.mimetype);
            addContent(file.data, file.datalength);
        }
        else
        {
            // not found
            setStatus(STR_404_Not_Found);
        }
        HTTPResponse::flush();
    }
    
	
}	// fdv namespace








