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
#ifndef _N7_HTTPSERVER_H_
#define _N7_HTTPSERVER_H_

#include "N7Common.h"

#include <MDK/ThreadServer.h>

class CHTTPServer : public CThreadServer
{
public:
	CHTTPServer(int defaultport, bool udp);
	~CHTTPServer();
	
	virtual int Initialize();
	
	bool OnTCPNewConnection(mdk_socket client, int status);
	void OnTCPRead(mdk_socket client, const char *data, ssize_t size);
	void OnUDPRead(mdk_socket client, const struct sockaddr* addr, const char *data, ssize_t size);
	
	static void WriteHTTPResponse(mdk_socket client, const char* content, const char* content_type, int code = 200, const char *message = "OK", const char** extraheaders = NULL, size_t extraheaders_size = 0);

protected:
	virtual void HandleHTTPRequest(mdk_socket client, const char *action, const char *path, const char* content, const char **headers, size_t headers_size) = 0;

};

#endif
