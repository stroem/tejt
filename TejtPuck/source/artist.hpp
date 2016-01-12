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

#ifndef OPENGL_ARTIST__HPP
#define OPENGL_ARTIST__HPP

#include "platform.hpp"

#include "view.hpp"
#include "body.hpp"

#include "glfont.hpp"

class OpenGL_Artist
{
    public:
        OpenGL_Artist();

        void SetCanvas(int width, int height);
        void Render(const ObjectVector& world, View eye);

    private:
        void DrawCube(const Body& cube);
        void DrawBorderedCube(const Body& cube);
};

#endif // OPENGL_ARTIST__HPP
