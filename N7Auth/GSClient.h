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
#ifndef _GSCLIENT_H_
#define _GSCLIENT_H_

#include <MDK/MasterServerMDK.h>

class GSClient
{
public:
	GSClient(mdk_client mdk);
	~GSClient();
	
	char GetRetry() { return m_retry; }
	
	void Handle(const char*data, const char*gemid);
	
protected:
	bool ConnectToGPCM();
	void HandleAccountCreate(const char*data, const char*gemid);
	void HandleLogin(const char*data, const char*gemid);
	void DisconnectFromGPCM();
	
	char m_retry;
	mdk_client m_client;
	mdk_client m_connect;
	char server_chall[11];
	int server_id;

};

#endif
