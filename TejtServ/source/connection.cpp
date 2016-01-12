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

#include "connection.hpp"

connection::connection(socket_type* sock, const address_type& addr)
    : ttl(STDTTL),
      approved(false),
      socket(sock),
      address(addr)
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
    // Try to get an entire message from the buffer, discard the data
    // collected if it is possible
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

bool connection::is_approved()
{
    return approved;
}    

void connection::touch()
{
    // Called to make sure that unwanted connections are closed sooner rather
    // than later. If a socket hasn't been approved, the TTL reaches 0 and the
    // send buffer is empty (a kick/decline message could be in the send buffer)
    // the socket will be closed, which means kicked.
    if((approved == false) && (--ttl <= 0) && (send_buffer.empty() == true))
        socket->close();
}

void connection::approve()
{
    approved = true;
}

void connection::turn_down()
{
    ttl = 0;
}
