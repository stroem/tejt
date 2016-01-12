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

#ifndef TEXT__HPP
#define TEXT__HPP

#include "platform.hpp"
#include "letter.hpp"
#include "object.hpp"


struct Text
    : public Object
{
    explicit Text(const std::string& set_text = std::string(), const Letter& set_letter = Letter(), const Point& set_pos = Point(), const Size& set_size = Size(),
		 const Color& set_color = Color(), const Rotation& set_rotation = Rotation(), bool set_transparent = true)
		: Object(Text_Object, set_pos, set_size, set_color, set_rotation),
		  txt(set_text),
		  letter(set_letter),
		  transparent(set_transparent)
	{
		// Om storleken ej är satt, räknar vi ut den.
		if(size.width <= 0)
			size.width = (letter.size.width + letter.spacing)*(Length()-1) + letter.size.width*1.5 + MILLI;
		if(size.height <= 0)
			size.height = letter.size.height*(int(((letter.size.width + letter.spacing)*(Length()-1) + letter.size.width*1.5)/size.width)+1 + std::count(txt.begin(), txt.end(), '\n'))*1.5 + letter.size.height/2 + MILLI;
	}

	unsigned int Length()
	{
		return txt.size();
	}

	const char operator[] (unsigned int i)
	{
		return txt[i];
	}

	std::string txt;
	Letter letter;
	bool transparent;	// Bestämmer huruvida bakgrundsfärgen skall visas eller ej
};

#endif // TEXT__HPP
