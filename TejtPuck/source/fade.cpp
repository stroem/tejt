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

#include "fade.hpp"

Fade::Fade(ActivityHandler* fade_to, const ObjectVector& set_world, const View& set_view)
	: ActivityHandler(set_world, set_view),
	  fade_in(false)
{
	next_activity = fade_to;
	fadetime = 500;
	distance.x = 10.0;

	target.x = eye.position.x + distance.x;

	fadespeed.x = distance.x/fadetime;
}

void Fade::Think(unsigned int elapsed_time)
{
	if(!fade_in)
	{
		if(eye.position.x >= target.x) 	// Om man bortfadningen nått mål-läget
		{
			if(next_activity == 0)
				done = true;
			else
			{
				fade_in = true;	// Nu ska vi fadea in nästa aktivitet

				// Byt ut den utfadeade världen mot den nya
				world = next_activity->GetWorld();
				eye = next_activity->GetView();

				// Flytta ögat så att vi inte ser den nya världen
				eye.position.x -= distance.x;

				fadespeed.x = distance.x/fadetime;

			}
		}
	}
	else
	{
		if(next_activity->GetView().position.x <= eye.position.x)	// om man är framme
			done = true;
	}

	eye.position.x += fadespeed.x*elapsed_time;
}
