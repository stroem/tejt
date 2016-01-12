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

#ifndef CLIENT__HPP
#define CLIENT__HPP

#include <vector>
#include <string>

struct Client
{
    explicit Client(const std::string& set_nick, const std::string& set_stat, const std::string& set_ip)
        : nickname(set_nick),
          status(set_stat),
          ip(set_ip)
    {
    }
    
    std::string nickname;
    std::string status;
    std::string ip;
};

typedef std::vector<Client> ClientVector;
ClientVector ParseServerList(const std::string& raw_list);

#endif // CLIENT__HPP
