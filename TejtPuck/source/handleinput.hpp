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

#ifndef HANDLEINPUT__HPP
#define HANDLEINPUT__HPP

#include "platform.hpp"

void HandleInput(const ::SDL_KeyboardEvent& key, std::string& Buffer);

struct no_unwanted_characters
{
	explicit no_unwanted_characters(const std::string& set_chars)
		: characters(set_chars)
	{
	}

	bool operator()(const char& ch)
	{
	    return characters.find(ch) == std::string::npos;
	}

	std::string characters;
};

std::string StripCharacters(const std::string& raw_data, const std::string& characters);

#endif	// HANDLEINPUT__HPP
