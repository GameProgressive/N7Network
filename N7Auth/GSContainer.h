/*
    This file is part of N7Network.

    N7Network is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    N7Network is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with N7Network.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _GSCONTAINER_H_
#define _GSCONTAINER_H_

#include <MDK/MasterServerMDK.h>

#include "GSClient.h"

#include <map>

class GSContainer
{
public:
	static bool ConnectToGPCM();
	static void DisconnectFromGPCM();
	static bool IsConnectedToGPCM();
	
	static void SendToGPCM(const char* data);
	static void SendToGPCM(std::string string);
	static void SendToGPCM(void* data, int len);
	
	static GSClient* Get(int id);
	static GSClient* New(int id);
	static void Del(int id);
	static void DelAll(void);
	
protected:
	static Client* m_client;
	static std::map<int, GSClient*> m_map;
	
};

#endif
