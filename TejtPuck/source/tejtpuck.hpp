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

#ifndef TEJTPUCK__HPP
#define TEJTPUCK__HPP

#include "artist.hpp"
#include "eventhandler.hpp"
#include "menu.hpp"

class Tejtpuck
    : public SDL_EventHandler
{
    public:

        Tejtpuck();

        virtual ~Tejtpuck()throw();

        virtual bool Running();
        virtual void Initialize(unsigned int width, unsigned int height);

        virtual void OnLogic(const ::SDL_LogicNotificationEvent& logic);
        virtual void OnRender(::SDL_RenderEvent& screen);

        virtual void OnKeyDown(const ::SDL_KeyboardEvent& key);
        virtual void OnMouseMove(const ::SDL_MouseMotionEvent& motion);

    protected:
        bool running;
        std::auto_ptr<ActivityHandler> activity;
        std::auto_ptr<OpenGL_Artist> artist;
};

#endif // TEJTPUCK__HPP
