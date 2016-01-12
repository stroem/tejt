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

#ifndef PLATFORM__HPP
#define PLATFORM__HPP

#include <zinara.hpp>

// Beloved typedefs

typedef zinara::ip::tcp::socket socket_type;
typedef zinara::ip::tcp::address address_type;
typedef zinara::ip::tcp::acceptor acceptor_type;
typedef zinara::ip::tcp::connector connector_type;

typedef zinara::basic_multiplexer<zinara::select_reactor> multiplexer_type;

typedef zinara::basic_stream_buffer<std::allocator> buffer_type;

using zinara::FD_READABLE;
using zinara::FD_WRITABLE;
using zinara::FD_ERRONEOUS;

#endif // PLATFORM__HPP
