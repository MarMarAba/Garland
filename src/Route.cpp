/*
 *
 * Garland HTTP Framework
 *
 * Copyright (C)  2014  MarMarAba   info@marmaraba.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * ============================================================================
 * Name        : Garland.cpp
 * Author      : MarMarAba
 * Version     : 0.5
 * Copyright   : Copyright (c) 2014 MarMarAba
 * Description : Simple free and open source web application mini REST
 * 							 framework based on Bogart, inspired by Sinatra, and written
 * 							 in C++.
 * ============================================================================
 */

#include <string.h>

#include "include/Garland.h"

Garland::Route::Route (const char * new_pattern, enum evhttp_cmd_type new_type)
{
	pattern = strdup(new_pattern);
	type = new_type;
	handler = nullptr;
	next = nullptr;
}

Garland::Route::~Route ()
{
	if (next)
		delete next;
}


bool Garland::Route::match_uri (const char * uri)
{
	while (*pattern && *uri)
	{
		if (*pattern == *uri)
		{
			pattern++;
			uri++;
		}
		else
			if (*pattern == '*')
			{
				if (*uri == '/' || !*(uri + 1))
				{
					pattern++;
				}
				else
				{
					uri++;
				}
			}
			else
			{
				return false;
			}
	}
	return (!*pattern && !*uri) || (!*pattern && *uri);
}
