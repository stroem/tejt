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

#ifndef PLAYER__HPP
#define PLAYER__HPP

#include <string>

/**
 * This is a very simple struct which keeps the most vital information
 * about a connection.
 */
struct player
{
    explicit player(const std::string& set_nickname, const std::string& set_ip)
        : busy(false),
          nickname(set_nickname),
          ip(set_ip)
    {
    }
    bool busy;
    std::string nickname;
    std::string ip;
};

#endif // PLAYER__HPP
