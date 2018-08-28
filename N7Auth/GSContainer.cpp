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
#include "GSContainer.h"

GSClient* GSContainer::Get(int id)
{
	if (m_map.find(id) != m_map.end())
	{
		if (m_map[id])
			return m_map[id];
	}

	return NULL;
}

GSClient* GSContainer::New(int id)
{
	GSClient* gsc = new GSClient();
	 m_map[id] = gsc;
	return gsc;
}

void GSContainer::Del(int id)
{
	if (m_map.find(id) != m_map.end())
	{
		if (m_map[id])
			delete m_map[id];

		m_map.erase(id);
	}
}

void GSContainer::DelAll(void)
{
	std::map<int, GSClient*>::iterator it = m_map.begin();
	while (it != m_map.end())
	{
		if (it->second)
			delete it->second;
	}

	m_map.clear();
}

std::map<int, GSClient*> GSContainer::m_map;
