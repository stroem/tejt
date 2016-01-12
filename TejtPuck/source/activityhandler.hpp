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

#ifndef ACTIVITYHANDLER_HPP
#define ACTIVITYHANDLER_HPP

#include "platform.hpp"
#include "body.hpp"
#include "view.hpp"

class ActivityHandler
{
	public:
		ActivityHandler(const ObjectVector& set_world, const View& set_eye)
		{
			world = set_world;
			eye = set_eye;

			done = false;
			next_activity = NULL;
		}
		ActivityHandler()
		{
			done = false;
			next_activity = NULL;
		}
		virtual ~ActivityHandler()
		{ }

		virtual const ObjectVector& GetWorld();
		virtual const View& GetView();

		virtual void Think(unsigned int elapsed_time);
        virtual void OnKeyDown(const ::SDL_KeyboardEvent& key);
        virtual void OnMouseMove(const ::SDL_MouseMotionEvent& motion);

		bool Done()
		{
			return done;
		}
		ActivityHandler* NextActivity()
		{
			return next_activity;
		}

	protected:
		void SetNextActivity(ActivityHandler* set_activity, bool set_done = false)
		{
			next_activity = set_activity;
			done = set_done;
		}

		bool done;
		ActivityHandler* next_activity;

		ObjectVector world;
		View eye;
};

#endif
