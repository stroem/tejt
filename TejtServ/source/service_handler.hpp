/*
** The dedicated TejtPuck server
** Copyright (C) 2007 Erik Edlund [eitlund at gmail dot com]
** 
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License along
** with this program; if not, write to the Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef SERVICE_HANDLER__HPP
#define SERVICE_HANDLER__HPP

#include <map>
#include <string>
#include <memory>
#include <algorithm>

#include "player.hpp"
#include "version.hpp"
#include "platform.hpp"
#include "connection.hpp"

typedef std::map<connection_ptr, player, pointer_cmp> player_map;

/**
 * The server handler contains everything important, it implements
 * the service. The local port will specify which port the acceptor
 * will bind on, and set_passwd will set the admin password of the
 * server, it must be supplied to remotely shut down the server.
 */
class service_handler
    : private zinara::noncopyable
{
    public:
        explicit service_handler(int local_port, const std::string& set_passwd);
        virtual ~service_handler()throw();
        
        void run();
        
    protected:
        std::string passwd;
        
        acceptor_type acceptor;
        multiplexer_type multiplexer;
        
        void accept_connection(connection_list& connections);
        
        std::string get_news();
};

#endif // SERVICE_HANDLER__HPP
