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

#ifndef BODY__HPP
#define BODY__HPP

#include "platform.hpp"

#include "object.hpp"
#include "area.hpp"
#include "speed.hpp"

struct Body
    : public Object
{
	explicit Body(const Point& set_pos = Point(), const Size& set_size = Size(), const Color& set_color = Color(), Object_Style set_style = NO_STYLE, const Speed& set_v = Speed())
		: Object(Body_Object, set_pos, set_size, set_color, Rotation(), set_style),
		  velocity(set_v)
	{
	}

    Speed velocity;
};

#endif // BODY__HPP
