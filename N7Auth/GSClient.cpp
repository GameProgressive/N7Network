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
#include "GSClient.h"
#include "GSContainer.h"
#include <Base64.h>

GSClient::GSClient(mdk_client client)
{
	m_client = client;
	m_connect = NULL;
	m_retry = 0;
	server_chall[0] = '\0';
	server_id = 0;
}

GSClient::~GSClient()
{
	DisconnectFromGPCM();
	m_connect = NULL;
}

void GSClient::Handle(const char*data, const char*gemid)
{
	char buffer[1025];
	char* action=NULL;
	buffer[0] = '\0';
	size_t bsize = 0;
	
	if (!m_connect)
	{
		if (!GSContainer::IsConnectedToGPCM())
		{
			Server::Close(m_client);
			return;
		}
	}
	
	get_param_data(data, "action", buffer, sizeof(buffer));
	
	bsize = B64DecodeLen(buffer);
	
	action = (char*)malloc(sizeof(char)*(bsize+1));
	action[bsize] = '\0';
	
	B64Decode(buffer, action, sizeof(action));
	
	if (strcmp(action, "acctcreate") == 0)
		HandleAccountCreate(data, gemid);
	else if (strcmp(action, "login") == 0)
		HandleLogin(data, gemid);
	else
		puts(action);
}

void GSClient::HandleAccountCreate(const char*data, const char*gemid)
{
	puts(data);
	//??
}

void GSClient::HandleLogin(const char*data, const char*gemid)
{
	char buff[2049];
	char user[31];
	char sdkversion[16];
	char challenge[65];
	user[0] = buff[0] = sdkversion[0] = challenge[0] = '\0';
	
	get_param_data(data, "sdkver=", buff, sizeof(buff), NULL);
	B64Decode(buff, sdkversion, sizeof(sdkversion));
	
	strrnd(challenge, sizeof(challenge), "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	
	get_param_data(data, "userid=", buff, sizeof(buff), NULL);
	
	
	_snprintf_s(buff, sizeof(buff), 2048, "\\login\\challenge\\%s\\partnerid\\11\\user\\%s@%s@nds\\port\\-10\\sdkversion\\%s\\final\\",
		challenge, user, user, sdkversion);
		
}
