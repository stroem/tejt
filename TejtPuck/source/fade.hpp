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

#ifndef FADE__HPP
#define FADE__HPP

#include "platform.hpp"
#include "activityhandler.hpp"

class Fade
	: public ActivityHandler
{
	public:
		Fade(ActivityHandler* fade_to, const ObjectVector& set_world, const View& set_view);

		virtual void Think(unsigned int elapsed_time);
	private:
		Color fade_to;
		unsigned int fadetime;
		bool fade_in;
		Speed fadespeed;
		Point target, distance;
};

#endif	// FADE__HPP
