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

#include "stringutility.hpp"

void split_string(std::vector<std::string>& out, const std::string& str, const std::string& delim)
{
    std::string::size_type first_pos(0);
    std::string::size_type second_pos(str.find_first_of(delim));
    out.push_back(str.substr(first_pos, second_pos));
    while(second_pos != std::string::npos)
    {
        first_pos = second_pos + 1;
        second_pos = str.find_first_of(delim, first_pos);
        out.push_back(str.substr(first_pos, second_pos - first_pos));
    }
}
