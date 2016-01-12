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

#ifndef SDL_APPLICATION__HPP
#define SDL_APPLICATION__HPP

#include <string>
#include <exception>
#include <stdexcept>

#include "platform.hpp"

/**
 * Det finns ingen event for logik i event, men det behöver
 * vi med den nuvarande event handler designen.
 */
typedef struct SDL_LogicNotificationEvent
{
    explicit SDL_LogicNotificationEvent(unsigned int set_tick, unsigned int set_lock)
        : elapsed_time(set_tick),
          time_lock(set_lock)
    {
    }

    unsigned int elapsed_time;
    unsigned int time_lock;

} SDL_LogicNotificationEvent;

/**
 * En render event dyker upp när det är dags att rita något.
 */
typedef struct SDL_RenderEvent
{
    explicit SDL_RenderEvent(::SDL_Surface& set_screen, int set_w, int set_h)
        : screen(set_screen),
          width(set_w),
          height(set_h)
    {
    }

    ::SDL_Surface& screen;

    int width;
    int height;

} SDL_RenderEvent;

class SDL_EventHandler;

/**
 * Applikationen är givetvis grunden, den är ansvarig för att hämta events
 * genererade av SDL och ge dem till den satta event handlern.
 *
 * Det kan bara finnas en applikation, och eftersom den är svår att anpassa
 * till singleton mönstret använder vi ett litet hack med en statisk bool.
 */
class SDL_Application
{
    public:

        explicit SDL_Application(SDL_EventHandler& set_handler, unsigned int set_width, unsigned int set_height, unsigned int depth);

        virtual ~SDL_Application()throw();

        void Run();

        int GetWidth()const;
        int GetHeight()const;

    private:
        SDL_EventHandler& application_handler;

        unsigned int width;
        unsigned int height;

        unsigned int last_tick;
        unsigned int time_lock;

        ::SDL_Surface* screen;

        static bool initialized;
};

#endif // SDL_APPLICATION__HPP
