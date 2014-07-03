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
 * Description : Implementation of the functions for the class Request.
 * ============================================================================
 */

#include "include/Garland.h"

Garland::Request::Request (struct evhttp_request *ev_req)
{
  init(ev_req);
}

void Garland::Request::init (struct evhttp_request * ev_req)
{
  evHttpRequest = ev_req;

  uriInfo = evhttp_request_get_evhttp_uri(ev_req);

  query_params = (struct evkeyvalq *) malloc(sizeof(struct evkeyvalq));
  if (evhttp_parse_query_str(evhttp_uri_get_query(uriInfo), query_params))
    throw 1;

}

struct evhttp_request * Garland::Request::getEVRequest ()
{
  return evHttpRequest;
}

char * Garland::Request::getParam (const char * key)
{
  char * string_value;
  struct evkeyval * cur_param = NULL;

  TAILQ_FOREACH(cur_param, query_params, next)
  {
    if (!strcmp(key, cur_param->key))
    {
      string_value = cur_param->value;
      break;
    }
  }

  return string_value;
}

char * Garland::Request::getHeader (const char * key)
{
  char * string_value = nullptr;

  const char * str_ptr = evhttp_find_header(evHttpRequest->input_headers, key);

  if (str_ptr)
    string_value = strdup(str_ptr);

  return string_value;
}

Garland::Request::~Request ()
{
  struct evkeyval * evkv_ptr = query_params->tqh_first;

  TAILQ_FOREACH(evkv_ptr, query_params, next)
    free(evkv_ptr);

  free(query_params);
}

