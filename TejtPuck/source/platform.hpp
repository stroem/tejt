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

#ifndef PLATFORM__HPP
#define PLATFORM__HPP

#include <zinara.hpp>
#include <SDL/SDL.h>

#if WINDOWS
#include <windows.h>

const double MILLI(1.0e-2);

#else

#if defined(__APPLE__) && defined(__MACH__)

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#else

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

const double MILLI(1.0e-3);

#endif

#endif

// Standard libraries
#include <string>
#include <vector>
#include <cmath>

typedef zinara::basic_stream_buffer<std::allocator> buffer_type;
typedef zinara::basic_multiplexer<zinara::select_reactor> multiplexer_type;

using zinara::FD_READABLE;
using zinara::FD_WRITABLE;
using zinara::FD_ERRONEOUS;
using zinara::SOCKET_ERROR;

const int SERVER_PORT(7317);
const std::string VERSION("0.1");

#endif // PLATFORM__HPP
