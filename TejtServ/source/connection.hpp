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

#ifndef CONNECTION__HPP
#define CONNECTION__HPP

#include <list>
#include <algorithm>

#include "platform.hpp"

const int STDTTL(10);

/**
 * This class represents a stream socket, that is a connection oriented
 * socket. It will work using messages, collect and send data, using the
 * classical "\r\n" combo to preserver message boundaries.
 * 
 * A new connection must prove that it belongs on this server by stating
 * "IAM" (se server-client protocol), if it cant do that before the TTL
 * reaches zero it will be kicked.
 */
class connection
    : private zinara::noncopyable
{
    public:
        explicit connection(socket_type* sock, const address_type& addr);
        
        socket_type& get_socket();
        address_type& get_address();
        
        bool good();
        
        bool get_message(std::string& msg);
        void put_message(const std::string& msg);
        
        void process_io();
        
        bool want_write();
        bool is_approved();
        
        void touch();
        void approve();
        void turn_down();
        
    private:
        typedef std::auto_ptr<socket_type> socket_ptr;
        
        short ttl;
        bool approved;
        
        buffer_type send_buffer;
        buffer_type recv_buffer;
        
        socket_ptr socket;
        address_type address;
};

typedef zinara::shared_ptr<connection, zinara::single_threaded> connection_ptr;
typedef std::list<connection_ptr> connection_list;

struct pointer_cmp
{
    bool operator()(const connection_ptr& p1, const connection_ptr& p2)
    {
        return p1.get() < p2.get();
    }
};

#endif // CONNECTION__HPP
