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
#include "GSContainer.h"
#include "Base64.h"

N7AuthServer::N7AuthServer() {}
N7AuthServer::~N7AuthServer() {}

void N7AuthServer::HandleHTTPRequest(mdk_client client, const char *action, const char *path, const char* content, const char **headers, size_t headers_len)
{
	char* real_action = NULL, *pch = NULL;
	char buffer[1024];
	size_t pos1 = 0, pos2 = 0;

	//REQ: action=YWNjdGNyZWF0ZQ**&sdkver=MDA1MDAz&userid=ODU1Mjk3ODYxMjM3Mg**&passwd=OTE3&bssid=OTRmZTIyYWYzODAz&apinfo=MDA6MDAwMDAwMC0wMA**&gamecd=SVJBSQ**&makercd=MDE*&unitcd=MA**&macadr=NDBkMjhhMjZmZjg3&lang=MDQ*&birth=MDIxMw**&devtime=MTgwNzA4MTY0NDMw&devname=QwBoAHIAeQA*
	//RES: challenge=Njg3VEYwRUc*&locator=Z2FtZXNweS5jb20*&retry=MA**&returncd=MDA*&token=dDIzamc4OWhmN2dxd2ZvMHdlNGY3OHEyZ3Q3Zg**&datetime=MjAxNDAyMjgyMTA0NTI*

	pch = (char*)strstr(content, "action=");
	pos1 = pch - content;
	pos1 += 7;
	pch = (char*)strstr(&content[pos1], "&");
	pos2 = pch - &content[pos1];

	strncpy(buffer, &content[pos1], pos2);

	pos1 = B64DecodeLen(buffer);
	

	Write(client, action);
}
