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
#ifndef _N7N_SERVER_H_
#define _N7N_SERVER_H_

#include <HTTPServer.h>

class N7AuthServer : public CHTTPServer
{
public:
	N7AuthServer();
	~N7AuthServer();
	
protected:
	void HandleHTTPRequest(mdk_client client, const char *action, const char *path, const char* content, const char **headers, size_t headers_len);

};

#endif
