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
 * Description : Implementation of the functions for the class Response.
 * ============================================================================
 */

#include "include/Garland.h"

Garland::Response::Response (struct evhttp_request * req)
{
  code = 200;
  request = req;
  buffer = evbuffer_new();
}

Garland::Response::~Response ()
{
  if (buffer)
    evbuffer_free (buffer);
}

void Garland::Response::sendReply ()
{
  evhttp_send_reply(request, code, brief.c_str(), buffer);
}

int Garland::Response::setHeader (const char * key, const char * value)
{
  return evhttp_add_header(evhttp_request_get_output_headers(request), key,
      value);
}

int Garland::Response::setBody (const char * pattern, ...)
{
  va_list ap;
  va_start(ap, pattern);
  return evbuffer_add_vprintf(buffer, pattern, ap);
}
