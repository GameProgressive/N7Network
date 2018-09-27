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
#include "HTTPServer.h"

#include <time.h>
#include <string.h>

#include <MDK/Utility.h>

const char* _GetMon(int i);
const char* _GetDay(int i);

CHTTPServer::CHTTPServer(int defaultport, bool udp) : CThreadServer(defaultport, udp)
{}

CHTTPServer::~CHTTPServer()
{}

int CHTTPServer::Initialize() { return 0; }

bool CHTTPServer::OnTCPNewConnection(mdk_socket, int) { return true; }

void CHTTPServer::OnTCPRead(mdk_socket client, const char *data, ssize_t size)
{
	const char *action = NULL;
	char path[1024];
	char* pch = NULL, **headers = NULL;
	std::string cnt = "";
	size_t pos = 0, xpos = 0, headers_size=0;
	
	if (strstartswith(data, "GET "))
		action = "GET";
	else if (strstartswith(data, "POST "))
		action = "POST";
	else
		return;
	
	xpos = strlen(action)+1;
	
	pch = (char*)strstr(&data[xpos], " ");
	pos = pch-&data[xpos];
	
	if (pos < 1)
		return;
	
	if (pos > 1023)
	{
		// Truncated...
		strncpy(path, &data[xpos], 1024);
		path[1024] = '\0';
	}
	else
	{
		strncpy(path, &data[xpos], pos);
		path[pos] = '\0';
	}
	
	pch = (char*)strstr(data, "\n");
	xpos = pch-data;
	
	if (pos < 1)
		return;
	
	xpos++;
	
	pch = (char*)strstr(&data[xpos], "\r\n\r\n");
	pos = pch-&data[xpos];

	char* xdata = (char*)&data[xpos];
	
	if (pos > 2)
	{
		char** tmpmov = NULL;
		while (true)
		{
			pch = (char*)strstr(xdata, "\r\n");
			
			if (!pch)
				break;

			xpos = pch-xdata;

			if (xpos < 1)
				break;
			
			headers_size++;
			if (!headers)
			{
				headers = (char**)malloc(headers_size*1024*sizeof(char));
				if (!headers)
					break;
			}
			else
			{
				tmpmov=(char**)realloc(headers, headers_size*1024*sizeof(char));
				if (!tmpmov)
					break;
				headers=tmpmov;
			}

			headers[headers_size - 1] = (char*)malloc(sizeof(char) * 1023);
			
			strncpy(headers[headers_size-1], xdata, xpos);
			
			xpos += 2;
			xdata = &xdata[xpos];
		}
	}

	char* pdata = (char*)data;
	pdata[size] = '\0';

	pch = (char*)strstr(pdata, "\r\n\r\n");
	pos = pch - pdata;
	if (pch)
	{
		cnt = &pdata[pos + 4];
	}
	
	HandleHTTPRequest(client, action, path, cnt.c_str(), (const char**)headers, headers_size);

	size_t i = 0;

	for (; i < headers_size; i++)
		free(headers[i]);
	
	if (headers)
		free(headers);

	// Conection: close
	Close(client);
}

void CHTTPServer::HandleHTTPRequest(mdk_socket, const char *, const char *,const char*, const char **, size_t) {}

void CHTTPServer::WriteHTTPResponse(mdk_socket client, const char*content, const char *content_type, int code, const char *message, const char** headers, size_t headers_size)
{
	std::string string = "HTTP/1.1 ";
	char buffer[1024];
	size_t i = 0;
	struct tm* tm;
	time_t t = time(NULL);
	buffer[0] = '\0';
	
	tm = localtime(&t);
	
	// Status code
	snprintf(buffer, sizeof(buffer)-1, "%d", code);
	
	string += buffer;
	string += " ";
	string += message;
	string += "\r\n";
	
	// Default headers
	snprintf(buffer, sizeof(buffer)-1, "%s, %d %s %d %d:%d:%d GMT", _GetDay(tm->tm_wday),
		tm->tm_mday, _GetMon(tm->tm_mon+1), tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);

	string += "Date: ";
	string += buffer;
	string += "\r\n";
	string += "Connection: close\r\n";
	string += "Server: N7Network/1.0\r\n";
	string += "Content-Type: ";
	string += content_type;
	string += "\r\n";
	
	for (; i < headers_size; i++)
	{
		string += headers[i];
		string += "\r\n";
	}
	
	string += "Content-Length: ";
#ifdef __64BIT__
	snprintf(buffer, sizeof(buffer)-1, "%ld", strlen(content));
#else
	snprintf(buffer, sizeof(buffer)-1, "%d", strlen(content));
#endif
	string += buffer;
	string += "\r\n";
	
	// Content
	string += "\r\n";
	string += content;
	string += "\r\n";
		
	// Write to the client
	WriteTCP(client, string);
}

const char* _GetMon(int i)
{
	switch (i)
	{
	case 1:
		return "Jan";
	case 2:
		return "Feb";
	case 3:
		return "Mar";
	case 4:
		return "Apr";
	case 5:
		return "May";
	case 6:
		return "Jun";
	case 7:
		return "Jul";
	case 8:
		return "Aug";
	case 9:
		return "Sep";
	case 10:
		return "Oct";
	case 11:
		return "Nov";
	case 12:
		return "Dec";
	default:
		break;
	}
	
	return "Jan";
}

const char* _GetDay(int i)
{
	switch (i)
	{
	case 0:
		return "Sun";
	case 1:
		return "Mon";
	case 2:
		return "Tue";
	case 3:
		return "Wed";
	case 4:
		return "Thu";
	case 5:
		return "Fri";
	case 6:
		return "Sat";
	default:
		break;
	}
	
	return "Sun";
}
