/*
** Tejtpuck
** Copyright (C) 2007
** Erik Edlund [eitlund at gmail dot com]
** Per Hallgren [per dot zut at gmail dot com]
** Jonathan Ström [gaffelspiken at hotmail dot com]
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
#include "stringutility.hpp"

typedef zinara::ip::tcp::socket socket_type;
typedef zinara::ip::tcp::address address_type;

/**
 * Representerar en TCP (stream) anslutning, används framför allt för att
 * kommunicera med servern. Den arbetar med meddelanden där varje meddelande
 * är avslutat med "\r\n", se server protokollet för mer inormation.
 */
class connection
    : private zinara::noncopyable
{
    public:
        explicit connection(socket_type* sock, const address_type& addr, const std::string& set_nickname);

        socket_type& get_socket();
        address_type& get_address();

        bool good();

        bool get_message(std::string& msg);
        void put_message(const std::string& msg);

        void set_nickname(const std::string& nick);

        void process_io();
        bool want_write();
        bool is_erroneous();
        void set_erroneous();

        std::string get_nickname()
        { return nickname; }

    private:
        typedef std::auto_ptr<socket_type> socket_ptr;

        bool erroneous;
        buffer_type send_buffer;
        buffer_type recv_buffer;

        socket_ptr socket;
        address_type address;

        std::string nickname;
};

typedef zinara::shared_ptr<connection, zinara::single_threaded> connection_ptr;

#endif // CONNECTION__HPP
