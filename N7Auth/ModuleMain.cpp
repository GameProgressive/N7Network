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
#include <N7Common.h>
#include "N7Server.h"

#define DEFAULT_PORT 30000

N7ModuleStart
	ModuleMain *mm = (ModuleMain*)data;
	N7AuthServer *Server = NULL;

	if (mm->port == -1)
		mm->port = DEFAULT_PORT;
	
	/*if (mm->mysql == NULL)
	{
		LOG_ERROR("N7Auth", "Unable to retrive MySQL connection!");
		return ERROR_MYSQL_POINTER;
	}*/

	Server = new N7AuthServer(/*mm->mysql*/);

	if (!Server->Bind(mm->ip, mm->port, false))
		return ERROR_BIND_ERROR;

	LOG_INFO("N7Auth", "Server started on %s:%d!", mm->ip, mm->port);

N7ModuleEnd
