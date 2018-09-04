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
#include "N7Server.h"

#include <string.h>

#include <Base64.h>
#include <Utility.h>

#include <MDK/Utility.h>

#define CHECK_ACTION(x) strcmp(action, x) == 0

N7AuthServer::N7AuthServer() {}
N7AuthServer::~N7AuthServer() {}

void N7AuthServer::HandleHTTPRequest(mdk_socket client, const char *http_action, const char *path, const char* content, const char **headers, size_t headers_len)
{
	char action[23];
	action[0] = 0;
	size_t pos = 0;

	if (strcmp(path, "/ac") != 0)
	{
		LOG_ERROR("N7Auth", "Unknown path: %s", path);
		return;
	}
	
	pos = get_n7_action(content, action, 22);
	if (pos == 0)
		return;
	
	if (CHECK_ACTION("acctcreate"))
	{
		HandleAcctCreate(client, &content[pos]);
	}
	else
	{
		LOG_ERROR("N7Auth", "Unknown action: %s", action);
	}
}

void N7AuthServer::HandleAcctCreate(mdk_socket client, const char* content)
{
	char buffer[1024], user[GP_NICK_LEN];
	int sdk_version = 0;
	buffer[0] = user[0] = '\0';
	
	if (!get_n7_data(content, "sdkver", buffer, 1024))
		return;
	
	sdk_version = atoi(buffer);
	
	if (!get_n7_data(content, "userid", user, GP_NICK_LEN))
		return;
		
	// email is user@nds
	
	
}
