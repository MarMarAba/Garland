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
 * Name        : Garland.h
 * Author      : MarMarAba
 * Version     : 0.5
 * Copyright   : Copyright (c) 2014 MarMarAba
 * Description : Header file for all the project. I contains the declaration of
 *               the main Garland class and all its nested classes.
 * ============================================================================
 */

#ifndef GARLAND_H_
#define GARLAND_H_

#include <evhttp.h>
#include <cstdlib>

/**
 * \class Garland
 *
 * \ingroup GarlandHTTPFramework
 *
 * \brief Main Framework class
 *
 * This class provides the general functionality for make Garland
 * working. It must be instantiated as an object, create the appropiate
 * callback functions, and assign it to the appropiate requests.
 *
 * \note Based in Bogart (C Framework), inspired in Sinatra (Ruby Framework)
 *
 * \author $Author: MarMarAba $
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 23/06/2014 14:25:07 $
 *
 * Contact: info@marmaraba.com
 *
 * $Id: Garland.h, v0.5, 23/06/2014 14:25:07, MarMarAba  $
 *
 *  <>
 */

class Garland
{
  public:
    /**
     * \class Response
     *
     * \ingroup GarlandHTTPFramework
     *
     * \brief HTTP Response class
     *
     * This class contains the information with information
     * of the response to be send to the client.
     *
     * \note Based in Bogart (C Framework), inspired in Sinatra (Ruby Framework)
     *
     * \author $Author: MarMarAba $
     *
     * \version $Revision: 0.5 $
     *
     * \date $Date: 23/06/2014 14:25:07 $
     *
     * Contact: info@marmaraba.com
     *
     * $Id: Garland.h, v0.5, 23/06/2014 14:25:07, MarMarAba  $
     *
     */

  public:
    class Response
    {
      public:
        Response ();
        Response (struct evbuffer * buffer);
        ~Response ();

        int code;
        struct evbuffer * local_buffer;

        void setBody (const char * pattern, ...);

      private:
        void init (struct evbuffer * buffer);
    };

    /**
     * \class Request
     *
     * \ingroup GarlandHTTPFramework
     *
     * \brief HTTP Request class
     *
     * This class contains the information about the request received
     * via HTTP.
     *
     * \note Based in Bogart (C Framework), inspired in Sinatra (Ruby Framework)
     *
     * \author $Author: MarMarAba $
     *
     * \version $Revision: 0.5 $
     *
     * \date $Date: 23/06/2014 14:25:07 $
     *
     * Contact: info@marmaraba.com
     *
     * $Id: Garland.h, v0.5, 23/06/2014 14:25:07, MarMarAba  $
     *
     */

  public:
    class Request
    {
      public:
        Request (struct evhttp_request * ev_req);
        ~Request ();

        struct evhttp_request * evHttpRequest;

        const char * uriString;
        const struct evhttp_uri * uriInfo;
        const char * uriInfoFragment;
        const char * uriInfoHost;
        const char * uriInfoPath;
        int uriInfoPort;
        const char * uriInfoQuery;
        const char * uriInfoScheme;
        const char * uriInfoUser;

      private:
        void init (struct evhttp_request * ev_req);

    };

  public:
    typedef void (*RequestHandler) (Request *, Response *);

  public:
    Garland (uint16_t port);
    Garland (const char * bind_address, uint16_t port);
    ~Garland ();

    bool blockingServer;

    void startServer ();
    void stopServer ();
    void addRequestHandler (RequestHandler, const char *,
        enum evhttp_cmd_type type = EVHTTP_REQ_GET);

  private:

    /**
     * \class Route
     *
     * \ingroup GarlandHTTPFramework
     *
     * \brief Route
     *
     * A route join the path received in the request with a callback handler
     * added by a final user.
     *
     * \note Based in Bogart (C Framework), inspired in Sinatra (Ruby Framework)
     *
     * \author $Author: MarMarAba $
     *
     * \version $Revision: 0.5 $
     *
     * \date $Date: 23/06/2014 14:25:07 $
     *
     * Contact: info@marmaraba.com
     *
     * $Id: Garland.h, v0.5, 23/06/2014 14:25:07, MarMarAba  $
     *
     */

    class Route
    {
      public:
        Route (const char * pattern, enum evhttp_cmd_type type);
        virtual ~Route ();

        Route * next;
        enum evhttp_cmd_type type;
        const char * pattern;
        RequestHandler handler;

        bool match_uri (const char * uri);
        Route * matching_route (Request * req);
    };

  private:
    typedef struct
    {
        uint16_t port;
        RequestHandler routeNotFound;
        Route * routes;
    } GarlandContext;

    bool serverRunning;
    GarlandContext currentContext;
    struct event_base * eventBase;
    struct evhttp * httpServer;

    void initializeGarland (const char * bindAddress, uint16_t port);
    void launchEventloop ();

    static void voidHandler (Request * request, Response * response);
    static void newRequestCB (struct evhttp_request * evReq, void * context);
};

#endif /* GARLAND_H_ */
