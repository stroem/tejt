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

#include "artist.hpp"

OpenGL_Artist::OpenGL_Artist()
{
    ::glEnable(GL_LINE_SMOOTH);

    float LightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float LightAmbient1[] = {  1.0f, 0.0f, 0.0f, 1.0f };
    float LightAmbient2[] = {  0.0f, 1.0f, 0.0f, 1.0f };
    float LightAmbient3[] = {  0.0f, 0.0f, 1.0f, 1.0f };
    float LightPosition1[] = {  0.5f, 2.0f, -7.0f, 1.0f };
    float LightPosition2[] = {  1.0f, 2.0f, -3.0f, 1.0f };
    float LightPosition3[] = { -1.0f, 2.0f, -3.0f, 1.0f };

    // Rigga ljuset
    ::glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient1);
    ::glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient2);
    ::glLightfv(GL_LIGHT3, GL_AMBIENT, LightAmbient3);
    ::glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    ::glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
    ::glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
    ::glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
    ::glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);
    ::glLightfv(GL_LIGHT3, GL_POSITION, LightPosition3);

    ::glEnable(GL_LIGHT1);
    ::glEnable(GL_LIGHT2);
    ::glEnable(GL_LIGHT3);
    ::glEnable(GL_LIGHTING);
    ::glEnable(GL_COLOR_MATERIAL);
}

void OpenGL_Artist::SetCanvas(int width, int height)
{
    ::glViewport(0, 0, width, height);
    ::glClearColor(0.6f, 0.7f, 0.8f, 0.0f);
    ::glClearDepth(1.0f);

    ::glDepthFunc(GL_LESS);
    ::glEnable(GL_DEPTH_TEST);
    ::glShadeModel(GL_SMOOTH);

    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();

    ::gluPerspective(45.0f, (GLfloat)width / static_cast<GLfloat>(height), 0.1f, 100.0f);

    ::glMatrixMode(GL_MODELVIEW);
}

void OpenGL_Artist::Render(const ObjectVector& world, View eye)
{
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ::glLoadIdentity();

    ::glPushMatrix();
        ::glRotatef(eye.rotation.x, 1.0f, 0.0f, 0.0f);
        ::glRotatef(eye.rotation.y, 0.0f, 1.0f, 0.0f);
        ::glRotatef(eye.rotation.z, 0.0f, 0.0f, 1.0f);

        ::glTranslatef(-eye.position.x, -eye.position.y, -eye.position.z);

        ::glColor3f(1.0f, 1.0f, 1.0f);

        for(unsigned int i(0); i < world.size(); ++i)
        {
        	switch(world[i]->type)
        	{
				case Body_Object:
					if(world[i]->style == NO_STYLE)
						DrawCube((const Body&)(*world[i]));
					else if(world[i]->style == CUBE_BORDERED)
						DrawBorderedCube((const Body&)(*world[i]));
					break;
				case Text_Object:
					{
						GLFont((const Text&)(*world[i])).Draw();
					}
					break;
				default:
					break;
        	}
        }

    ::glPopMatrix();

    ::SDL_GL_SwapBuffers();
}

void OpenGL_Artist::DrawCube(const Body& cube)
{
    ::glBegin(GL_QUADS);
        ::glColor3f(cube.color.R, cube.color.G, cube.color.B);

        // Left
        ::glNormal3f( 1.0f, 0.0f, 0.0f);
        ::glVertex3f( cube.size.width/2 + cube.position.x, (cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);
        ::glVertex3f( cube.size.width/2 + cube.position.x,-(cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);
        ::glVertex3f( cube.size.width/2 + cube.position.x,-(cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);
        ::glVertex3f( cube.size.width/2 + cube.position.x, (cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);

        // Front
        ::glNormal3f( 0.0f, 0.0f, -1.0f);
        ::glVertex3f( (cube.size.width/2) + cube.position.x, (cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);
        ::glVertex3f( (cube.size.width/2) + cube.position.x,-(cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x,-(cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x, (cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);

        // Right
        ::glNormal3f( -1.0f, 0.0f, 0.0f);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x, (cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x,-(cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x,-(cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x, (cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);

        // Back
        ::glNormal3f( 0.0f, 0.0f, 1.0f);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x, (cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x,-(cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);
        ::glVertex3f( (cube.size.width/2) + cube.position.x,-(cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);
        ::glVertex3f( (cube.size.width/2) + cube.position.x, (cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);

        // Up
        ::glNormal3f( 0.0f, 1.0f, 0.0f);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x, (cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x, (cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);
        ::glVertex3f( (cube.size.width/2) + cube.position.x, (cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);
        ::glVertex3f( (cube.size.width/2) + cube.position.x, (cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);

        // Down
        ::glNormal3f( 0.0f, -1.0f, 0.0f);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x, -(cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);
        ::glVertex3f(-(cube.size.width/2) + cube.position.x, -(cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);
        ::glVertex3f( (cube.size.width/2) + cube.position.x, -(cube.size.height/2) + cube.position.y,-(cube.size.depth/2) + cube.position.z);
        ::glVertex3f( (cube.size.width/2) + cube.position.x, -(cube.size.height/2) + cube.position.y, (cube.size.depth/2) + cube.position.z);
    ::glEnd();
}

void OpenGL_Artist::DrawBorderedCube(const Body& cube)
{

	DrawCube(cube);

	Size line_size(0.02);

    DrawCube(Body(Point(cube.position.x - cube.size.width/2 - line_size.width/2, cube.position.y - cube.size.height/2 - line_size.width/2, cube.position.z),
						 Size(line_size.width, line_size.width, cube.size.depth), Color(0,0,0)));
	DrawCube(Body(Point(cube.position.x - cube.size.width/2 - line_size.width/2, cube.position.y + cube.size.height/2 + line_size.width/2, cube.position.z),
						 Size(line_size.width, line_size.width, cube.size.depth), Color(0,0,0)));
	DrawCube(Body(Point(cube.position.x + cube.size.width/2 + line_size.width/2, cube.position.y - cube.size.height/2 - line_size.width/2, cube.position.z),
						 Size(line_size.width, line_size.width, cube.size.depth), Color(0,0,0)));
	DrawCube(Body(Point(cube.position.x + cube.size.width/2 + line_size.width/2, cube.position.y + cube.size.height/2 + line_size.width/2, cube.position.z),
						 Size(line_size.width, line_size.width, cube.size.depth), Color(0,0,0)));

	DrawCube(Body(Point(cube.position.x, cube.position.y - cube.size.height/2 - line_size.width/2, cube.position.z - cube.size.depth/2 - line_size.width/2),
						 Size(cube.size.width, line_size.width, line_size.width), Color(0,0,0)));
	DrawCube(Body(Point(cube.position.x, cube.position.y - cube.size.height/2 - line_size.width/2, cube.position.z + cube.size.depth/2 + line_size.width/2),
						 Size(cube.size.width, line_size.width, line_size.width), Color(0,0,0)));
	DrawCube(Body(Point(cube.position.x, cube.position.y + cube.size.height/2 + line_size.width/2, cube.position.z - cube.size.depth/2 - line_size.width/2),
						 Size(cube.size.width, line_size.width, line_size.width), Color(0,0,0)));
	DrawCube(Body(Point(cube.position.x, cube.position.y + cube.size.height/2 + line_size.width/2, cube.position.z + cube.size.depth/2 + line_size.width/2),
						 Size(cube.size.width, line_size.width, line_size.width), Color(0,0,0)));

	DrawCube(Body(Point(cube.position.x + cube.size.width/2 + line_size.width/2, cube.position.y, cube.position.z + cube.size.depth/2 + line_size.width/2),
						 Size(line_size.width, cube.size.height, line_size.width), Color(0,0,0)));
	DrawCube(Body(Point(cube.position.x + cube.size.width/2 + line_size.width/2, cube.position.y, cube.position.z - cube.size.depth/2 - line_size.width/2),
						 Size(line_size.width, cube.size.height, line_size.width), Color(0,0,0)));
	DrawCube(Body(Point(cube.position.x - cube.size.width/2 - line_size.width/2, cube.position.y, cube.position.z - cube.size.depth/2 - line_size.width/2),
						 Size(line_size.width, cube.size.height, line_size.width), Color(0,0,0)));
	DrawCube(Body(Point(cube.position.x - cube.size.width/2 - line_size.width/2, cube.position.y, cube.position.z + cube.size.depth/2 + line_size.width/2),
						 Size(line_size.width, cube.size.height, line_size.width), Color(0,0,0)));
}
