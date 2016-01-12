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

#ifndef SDL_EVENTHANDLER__HPP
#define SDL_EVENTHANDLER__HPP

#include <string>
#include <exception>
#include <stdexcept>

#include "platform.hpp"
#include "application.hpp"

typedef SDLKey SDL_Key;

/**
 * Basklass för alla event handlers. Den deklarerar alla funktioner som
 * applikation kan generera events för, vilka inte hanterar eventen på
 * något vis. Det är tänkt att man ska ärva en specifik event handler
 * från denna och sedan specifiera vilka events som man är intresserad av.
 */
class SDL_EventHandler
{
    public:
        virtual ~SDL_EventHandler()throw();

        virtual bool Running() = 0;
        virtual void Initialize(unsigned int width, unsigned int height) = 0;

        virtual void OnLogic(const ::SDL_LogicNotificationEvent& logic);
        virtual void OnRender(::SDL_RenderEvent& screen);

        virtual void OnKeyUp(const ::SDL_KeyboardEvent& key);
        virtual void OnKeyDown(const ::SDL_KeyboardEvent& key);
        virtual void OnMouseMove(const ::SDL_MouseMotionEvent& motion);
        virtual void OnMouseButtonUp(const ::SDL_MouseButtonEvent& button);
        virtual void OnMouseButtonDown(const ::SDL_MouseButtonEvent& button);
};

#endif // SDL_EVENTHANDLER__HPP
