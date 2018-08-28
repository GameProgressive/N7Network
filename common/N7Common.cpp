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
#include "N7Common.h"

#include <string.h>

void get_param_data(const char *data, const char* what, const char* out, size_t out_len)
{
	size_t pos = 0, pos2 = 0;
	char* pch = NULL;
	
	if (out_len < 1)
		return;
	
	pch = strstr(data, what);
	if (!pch)
	{
		out[0] = '\0';
		return;
	}
	pos=pch-data;
	pos++;
	
	pch = strchr(&data[pos], '&');
	if (!pch)
	{
		out[0] = '\0';
		return;
	}
	pos2=pch-&data[pos];
	
	if ((pos2+1)>out_len)
	{
		out[0] = '\0';
		return;
	}
	
	strncpy(out, &data[pos], pos2);
	out[pos2] = '\0';
}
