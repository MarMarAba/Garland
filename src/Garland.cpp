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
 * Description : Implementation of the functions for the class Garland.
 * ============================================================================
 */

#include <cstdio>
#include <thread>

#include "include/Garland.h"

Garland::Garland (uint16_t port)
{
  initializeGarland("0.0.0.0", port);
}

Garland::Garland (const char * bind_address, uint16_t port)
{
  initializeGarland(bind_address, port);
}

Garland::~Garland ()
{
  stopServer();

  // Free routes
  while (currentContext.routes != NULL)
  {
    Route * prev_route = currentContext.routes;
    currentContext.routes = currentContext.routes->next;
    delete prev_route;
  }

  evhttp_free(httpServer);
  event_base_free(eventBase);
}

void Garland::startServer ()
{
  if (!serverRunning)
  {
    serverRunning = true;

    if (blockingServer)
    {
      launchEventloop();
    }
    else
    {
      std::thread loop_thread(&Garland::launchEventloop, this);
      loop_thread.detach();
    }
  }
}

void Garland::stopServer ()
{
  if (serverRunning)
  {
    event_base_loopbreak(eventBase);
    serverRunning = false;
  }
}

void Garland::initializeGarland (const char * bind_address, uint16_t port)
{
  blockingServer = true;
  serverRunning = false;

  currentContext.port = port;
  currentContext.routes = NULL;
  RequestHandler voidHandler_ptr = voidHandler;

  currentContext.routeNotFound = *voidHandler_ptr;

  eventBase = event_base_new();
  httpServer = evhttp_new(eventBase);

  evhttp_bind_socket(httpServer, bind_address, currentContext.port);
  evhttp_set_gencb(httpServer, newRequestCB, &currentContext);
}

void Garland::launchEventloop ()
{
  event_base_loop(eventBase, 0);
}

void Garland::voidHandler (Request * request, Response * response)
{
  response->code = HTTP_NOTFOUND;
  response->brief = "Not found";
  response->setBody("Not found");
}

void Garland::newRequestCB (struct evhttp_request * ev_req, void * context)
{
  struct timeval t0, t1, tr;

  GarlandContext * inUseContext = (GarlandContext *) context;

  gettimeofday(&t0, NULL);

  Request * request = new Request(ev_req);
  Response * response = new Response(request->getEVRequest());

  Route * matched_route = inUseContext->routes->matching_route(request);

  if (matched_route)
  {
    matched_route->handler(request, response);
    response->sendReply();
  }
  else
  {
    inUseContext->routeNotFound(request, response);
    response->sendReply();
  }

  delete (request);
  delete (response);

  gettimeofday(&t1, NULL);
  timersub(&t1, &t0, &tr);
//  printf("Request processed in: %ld secs, %d usecs\n", tr.tv_sec, tr.tv_usec);
}

Garland::Route * Garland::Route::matching_route (Request * req)
{
  Route * cur_route = this;

  while (cur_route)
  {
    if (req->getEVRequest()->type == cur_route->type)
      if (cur_route->match_uri(req->getEVRequest()->uri))
        return cur_route;
    cur_route = cur_route->next;
  }

  return NULL;
}

void Garland::addRequestHandler (RequestHandler newHandler, const char * path,
    enum evhttp_cmd_type type)
{
  Route * new_route = new Route(path, type);

  if (currentContext.routes)
  {
    Route * cursor = currentContext.routes;
    while (cursor->next)
      cursor = cursor->next;
    cursor->next = new_route;
  }
  else
  {
    currentContext.routes = new_route;
  }

  new_route->handler = newHandler;
}
