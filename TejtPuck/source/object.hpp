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

#ifndef OBJECT__HPP
#define OBJECT__HPP

#include "size.hpp"
#include "point.hpp"
#include "color.hpp"
#include "rotation.hpp"

enum Object_Type
{
	Body_Object = 0,
	Text_Object,
	Line_Object
};

enum Object_Style
{
	NO_STYLE = 0,
	CUBE_BORDERED
};

struct Object
{
    explicit Object(Object_Type set_type, const Point& set_pos = Point(), const Size& set_size = Size(), const Color& set_color = Color(),
					const Rotation& set_rotation = Rotation(), Object_Style set_style = NO_STYLE)
		: size(set_size),
		  position(set_pos),
		  color(set_color),
		  rotation(set_rotation),
		  type(set_type),
		  style(set_style)
    {
    }

    Size size;
    Point position;
    Color color;
    Rotation rotation;
    Object_Type type;
	Object_Style style;
};

typedef zinara::shared_ptr<Object, zinara::single_threaded> object_ptr;

typedef std::vector<object_ptr> ObjectVector;

#endif	// OBJECT__HPP
