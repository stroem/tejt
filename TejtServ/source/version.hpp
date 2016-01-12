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

#ifndef VERSION__HPP
#define VERSION__HPP

#include <string>

const std::string server_version = "0.1";

// This string contains client versions that are currently supported
// by the server. Unsupported clients will be booted.
// Format "0.1 0.2 0.3 [...]"
const std::string compatible_versions = "0.1";

#endif
