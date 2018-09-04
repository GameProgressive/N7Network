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
#include <string.h>

#include "Utility.h"

#include "Base64.h"

#include <MDK/Utility.h>

size_t get_n7_action(const char *buffer, char* out, size_t out_len)
{
	size_t pos1 = 0, pos2 = 0;
	int len = 0;
	char *pch = NULL;
	
	if (out_len < 0)
		return 0;
	
	out[0] = '\0';
	
	pch = (char*)strstr(buffer, "action=");
	if (!pch)
		return 0;
	
	pos1 = pch - buffer;
	
	pos1 += 7;

	pch = (char*)strstr(&buffer[pos1], "&");
	if (pch)
		pos2 = pch - buffer;

	if (!pch)
		pos2 = (out_len-pos1);

	pch = (char*)malloc(sizeof(char)*(pos2+1));
	strncpy(pch, &buffer[pos1], pos2);
	
	len = B64DecodeLen(pch);
	if (len < 1)
	{
		free(pch);
		return 0;
	}
	
	if (len > out_len)
	{
		free(pch);
		return 0;
	}
	
	B64Decode(pch, out, pos2, &len);
	out[len] =  '\0';
	
	free(pch);
	return pos2+1;
}

bool get_n7_data(const char *buffer, const char *name, char* out, size_t out_len)
{
	size_t pos1 = 0, pos2 = 0;
	int len = 0;
	char *pch = NULL;
	
	if (out_len < 0)
		return false;
	
	out[0] = '\0';
	
	pch = (char*)strstr(buffer, name);
	if (!pch)
		return false;
	
	pos1 = pch - buffer;
	
	pos1 += 1 + strlen(name);
	
	pch = (char*)strstr(&buffer[pos1], "&");
	if (pch)
		pos2 = pch - &buffer[pos1];

	if (!pch)
		pos2 = (out_len-pos1);
	
	pch = (char*)malloc(sizeof(char)*(pos2+1));
	strncpy(pch, &buffer[pos1], pos2);
	
	len = B64DecodeLen(pch);
	if (len < 1)
	{
		free(pch);
		return false;
	}
	
	if (len > out_len)
	{
		free(pch);
		return false;
	}
	
	B64Decode(pch, out, pos2, &len);
	out[len] =  '\0';
	
	free(pch);
	return true;
}
