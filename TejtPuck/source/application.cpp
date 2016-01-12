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

#include "application.hpp"
#include "eventhandler.hpp"

bool SDL_Application::initialized = false;

SDL_Application::SDL_Application(SDL_EventHandler& set_handler, unsigned int set_width, unsigned int set_height, unsigned int depth)
    : application_handler(set_handler),
      width(set_width),
      height(set_height),
      last_tick(0),
      time_lock(100),
      screen(0)
{
    if(initialized)
        throw std::logic_error("SDL_Application: There can only be one instance, initialized one time");

    if(::SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("SDL_Application: Failed to initialize SDL");

    std::atexit(::SDL_Quit);
    if((this->screen = ::SDL_SetVideoMode(this->width, this->height, depth, SDL_OPENGL | SDL_FULLSCREEN)) == 0)
        throw std::runtime_error("SDL_Application: Failed to set viedeo mode");

	SDL_WM_SetCaption("Tejtpuck", NULL);

    application_handler.Initialize(this->width, this->height);

    initialized = true;
}

SDL_Application::~SDL_Application()throw()
{
}

int SDL_Application::GetWidth()const
{
    return this->width;
}

int SDL_Application::GetHeight()const
{
    return this->height;
}

void SDL_Application::Run()
{
    ::SDL_Event event;

    while(application_handler.Running())
    {
        while(::SDL_PollEvent(&event) && ::SDL_GetTicks() - this->last_tick < this->time_lock)
        {
            switch(event.type)
            {
                case SDL_MOUSEMOTION:
                    application_handler.OnMouseMove(event.motion);
                break;

                case SDL_MOUSEBUTTONUP:
                    application_handler.OnMouseButtonUp(event.button);
                break;

                case SDL_MOUSEBUTTONDOWN:
                    application_handler.OnMouseButtonDown(event.button);
                break;

                case SDL_KEYUP:
                    application_handler.OnKeyUp(event.key);
                break;

                case SDL_KEYDOWN:
                    application_handler.OnKeyDown(event.key);
                break;

                default:
                    break;
            }
        }


        SDL_LogicNotificationEvent logic_evt(::SDL_GetTicks() - this->last_tick, this->time_lock);
        this->last_tick = ::SDL_GetTicks();

        application_handler.OnLogic(logic_evt);

        SDL_RenderEvent render_evt(*this->screen, this->width, this->height);
        application_handler.OnRender(render_evt);
    }
}
