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
 * Name        : MainSample.cpp
 * Author      : MarMarAba
 * Version     : 0.5
 * Copyright   : Copyright (c) 2014 MarMarAba
 * Description : Simple free and open source web application mini REST
 * 							 framework based on Bogart, inspired by Sinatra, and written
 * 							 in C++.
 * ============================================================================
 */

#include <cstdlib>
#include <stdlib.h>
#include <cstdio>
#include <string>
#include "include/Garland.h"

using namespace std;

void get_hello (Garland::Request * request, Garland::Response * response)
{
	response->code = HTTP_OK;

	// scheme://[[userinfo]@]foo.com[:port]]/[path][?query][#fragment]

	response->setBody("uri: ");
	response->setBody(request->uriString);
	response->setBody("scheme: ");
	response->setBody(evhttp_uri_get_scheme(request->uriInfo));
	response->setBody("\nuser: ");
	response->setBody(request->uriInfoUser);
	response->setBody("\nhost: ");
	response->setBody(request->uriInfoHost);
	response->setBody("\n\nport: ");
	response->setBody(reinterpret_cast<char*>(&request->uriInfoPort));
	response->setBody("\npath: ");
	response->setBody(request->uriInfoPath);
	response->setBody("\nquery: ");
	response->setBody(request->uriInfoQuery);
	response->setBody("\nfragment: ");
	response->setBody(request->uriInfoFragment);

	return;
}

int main (void)
{

	Garland newServer(3333);

	newServer.addRequestHandler(get_hello, "/hel*");

	newServer.blockingServer = true;
	newServer.startGarland();

	return 0;
}
