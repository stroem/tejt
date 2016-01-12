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

#include "directip.hpp"

DirectIP::DirectIP()
{
	max_addr_len = 15;
	eye.position = Point(2.0, 2.0, 5.0);

	world.push_back(object_ptr(new Text()));

	world.push_back(object_ptr(new Body(Point(2, 3, 0.9), Size(0.9, 0.3, 0.2), Color(1,1,1), CUBE_BORDERED)));	// Övre rutan
	world.push_back(object_ptr(new Body(Point(2, 2, 0.9), Size(2.3, 0.3, 0.2), Color(1,1,1), CUBE_BORDERED)));	// Inputrutan
	world.push_back(object_ptr(new Body(Point(2, 1, 0.9), Size(0.9, 0.3, 0.2), Color(1,1,1), CUBE_BORDERED)));	// Undre rutan

	world.push_back(object_ptr(new Text("PLAYER 1", Letter(Size(0.07,0.15,0.0), 0.03, 2.5, Color(0,0,0)), Point(2, 3, 1.1+MILLI))));
	world.push_back(object_ptr(new Text("PLAYER 2", Letter(Size(0.07,0.15,0.0), 0.03, 2.5, Color(0,0,0)), Point(2, 1, 1.1+MILLI))));
	world.push_back(object_ptr(new Text("IP:", Letter(Size(0.07,0.15,0.0), 0.03, 2.5, Color(0,0,0)), Point(1.3, 2, 1+MILLI))));
}

DirectIP::~DirectIP()
{
}

void DirectIP::Think(unsigned int elapsed_time)
{
}

void DirectIP::OnKeyDown(const ::SDL_KeyboardEvent& key)
{
	switch(key.keysym.sym)
	{
		case SDLK_UP:
			if(!addr.empty())
				SetNextActivity(new Fade(new Game(true, addr, connection_ptr()), world, eye), true);
			break;
		case SDLK_DOWN:
			if(!addr.empty())
				SetNextActivity(new Fade(new Game(false, addr, connection_ptr()), world, eye), true);
			break;
		case SDLK_ESCAPE:
			SetNextActivity(new Fade(new Menu, world, eye), true);
			break;
		default:
			break;
	}
	// Hantera input, sortera bort oönskade tecken.
	HandleInput(key, addr);
	addr = StripCharacters(addr, "abcdefghijklmnopqrstuvwxyz,!?+-:/ =");

	if(addr.size() >= max_addr_len)
		addr = addr.substr(0, max_addr_len);

	world[0] = object_ptr(new Text(addr, Letter(Size(0.05,0.07,0.0), 0.03, 2.5, Color(0,0,0)),
		Point(2.4, 2, 1+MILLI), Size(1.3, 0.2,0), Color(0.3,0.3,0.3), Rotation(), false));
}
