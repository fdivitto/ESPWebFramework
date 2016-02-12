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

#ifndef _FDVSERIALCONSOLE_H_
#define _FDVSERIALCONSOLE_H_

#include "fdv.h"

namespace fdv {

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// SerialConsole

#if (FDV_INCLUDE_SERIALCONSOLE == 1)

class SerialConsole : public Task {

public:
  SerialConsole() : Task(false, 300) {}

  // destructor must be called outside This task
  ~SerialConsole() { terminate(); }

private:
  static uint32_t const MAX_PARAMETERS = 6; // including command name

  void exec();
  void separateParameters();
  void routeCommand();
  bool hasParameter(uint32_t paramIndex, char const *str);

public:
  void cmd_help();
  void cmd_reboot();
  void cmd_restore();
  void cmd_free();
  void cmd_ifconfig();
  void cmd_iwconfig();
  void cmd_iwlist();
  void cmd_date();
  void cmd_ntpdate();
  void cmd_nslookup();
  void cmd_uptime();
  void cmd_ping();
  void cmd_router();
  void cmd_ls();
  void cmd_rm();
  void cmd_cat();
  void cmd_fixflash();
  void cmd_test();

private:
  Serial *m_serial;
  LinkedCharChunks m_receivedChunks;
  uint32_t m_paramsCount;
  CharChunksIterator m_params[MAX_PARAMETERS];
  DateTime m_bootTime; // actually SerialConsole uptime!
};

#endif // FDV_INCLUDE_SERIALCONSOLE

} // end of "fdv" namespace

#endif	// _FDVSERIALCONSOLE_H_