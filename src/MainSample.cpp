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
 *                framework based on Bogart, inspired by Sinatra, and written
 *                in C++.
 * ============================================================================
 */

#include <cstdlib>
#include <cstdio>
#include <string>
#include "include/Garland.h"

using namespace std;

void get_hello (Garland::Request * request, Garland::Response * response)
{
  response->code = HTTP_OK;
  response->setBody("Received Hello via GET.");
  return;
}

void post_hello (Garland::Request * request, Garland::Response * response)
{
  response->code = HTTP_OK;
  response->setBody("Received Hello via POST.");
  return;
}

int main (void)
{

  Garland newServer("localhost", 3333);

  // scheme://[[userinfo]@]foo.com[:port]]/[path][?query][#fragment]
  newServer.addRequestHandler(get_hello, "/hello");
  newServer.addRequestHandler(post_hello, "/hello", EVHTTP_REQ_POST);

  newServer.blockingServer = false;
  newServer.startServer();

  while (true)
  {
    switch (getc(stdin))
    {
      case 'r': // run
        newServer.startServer();
        break;
      case 's': // stop
        newServer.stopServer();
        break;
      case 'q': // quit
        newServer.stopServer();
        return 0;
      default:
        break;
    }
  }

  return 0;
}
