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

#include "login.hpp"

Login::Login(int starting_player)
{
	max_nick_len = 10;
	eye.position = Point(2.0, 2.0, 5.0);

	world.push_back(object_ptr(new Text()));	// Reserverat för att skriva ut inputen i

	world.push_back(object_ptr(new Body(Point(2, 2, 0.9), Size(2.3, 0.3, 0.2), Color(1,1,1), CUBE_BORDERED)));	// Boxen som texten "står på"

	world.push_back(object_ptr(new Text("NICKNAME:", Letter(Size(0.07,0.15,0.0), 0.03, 2.5, Color(0,0,0)), Point(1.3, 2, 1+MILLI))));
}

Login::~Login()
{
}

void Login::Think(unsigned int elapsed_time)
{
}

void Login::OnKeyDown(const ::SDL_KeyboardEvent& key)
{
	switch(key.keysym.sym)
	{
		case SDLK_RETURN:
			if(nick.size() > 2)
				SetNextActivity(new Fade(new ServerInterface(nick), world, eye), true);
			break;
		case SDLK_ESCAPE:
			SetNextActivity(new Fade(new Menu, world, eye), true);
			break;
		default:
			break;
	}
	// Hantera input, ta bort oönskade tecken, se till att namnet är av rätt längd
	HandleInput(key, nick);
	nick = StripCharacters(nick, ".,!?+-:/ =");

	if(nick.size() >= max_nick_len)
		nick = nick.substr(0, max_nick_len);

	// Sätt style, position osv på texten, och uppdatera objektet.
	world[0] = object_ptr(new Text(nick, Letter(Size(0.07,0.09,0.0), 0.03, 2.5, Color(0,0,0)),
		Point(2.4, 2, 1+MILLI), Size(1.1, 0.2,0), Color(0.3,0.3,0.3), Rotation(), false));
}
