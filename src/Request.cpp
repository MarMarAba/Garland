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

#include <cstdlib>

#include "include/Garland.h"

Garland::Request::Request (struct evhttp_request *ev_req)
{
	init(ev_req);
}

void Garland::Request::init (struct evhttp_request * ev_req)
{
	evHttpRequest = ev_req;

	uriInfo = evhttp_request_get_evhttp_uri(ev_req);

	uriString = evhttp_request_get_uri(ev_req);
//	uriInfoScheme = evhttp_request_get_uri(uriInfo);
	uriInfoScheme = "\0";
	uriInfoUser = evhttp_uri_get_userinfo(uriInfo);
	uriInfoHost = ev_req->remote_host;
	uriInfoPort = ev_req->remote_port;
	uriInfoPath = evhttp_uri_get_path(uriInfo);
	uriInfoQuery = evhttp_uri_get_query(uriInfo);
	uriInfoFragment = evhttp_uri_get_fragment(uriInfo);
}

Garland::Request::~Request ()
{
	if (evHttpRequest)
		free(evHttpRequest);
}

