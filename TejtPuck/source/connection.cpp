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

#include "connection.hpp"

connection::connection(socket_type* sock, const address_type& addr, const std::string& set_nickname)
    : socket(sock),
      address(addr),
      nickname(set_nickname)
{
}

socket_type& connection::get_socket()
{
    return *socket;
}

address_type& connection::get_address()
{
    return address;
}

bool connection::good()
{
    return socket->good();
}

bool connection::get_message(std::string& msg)
{
    std::string data(recv_buffer.bptr(), recv_buffer.size());
    std::string::size_type terminator(data.find("\r\n"));
    if(terminator != std::string::npos)
    {
        msg.clear();
        msg.append(data, 0, terminator);
        recv_buffer.discard(0, terminator + 2);
    }
    return terminator != std::string::npos;
}

void connection::put_message(const std::string& msg)
{
    send_buffer.putn(msg.c_str(), msg.size());
}

void connection::process_io()
{
    if(socket->writable())
        send_buffer.discard(0, socket->send(send_buffer));

    if(socket->readable())
        socket->recv(recv_buffer);
}

bool connection::want_write()
{
    return send_buffer.size() > 0;
}

bool connection::is_erroneous()
{
    return erroneous;
}

void connection::set_erroneous()
{
    erroneous = true;
}

void connection::set_nickname(const std::string& nick)
{
    nickname = true;
}
