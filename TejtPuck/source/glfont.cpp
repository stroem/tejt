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

#include "glfont.hpp"

void GLFont::Draw()
{
	::glPushMatrix();
		::glLineWidth(text.letter.line_width);

		::glRotatef(text.rotation.x, 1.0f, 0.0f, 0.0f);
		::glRotatef(text.rotation.y, 0.0f, 1.0f, 0.0f);
		::glRotatef(text.rotation.z, 0.0f, 0.0f, 1.0f);

		if(!text.transparent)
		{
			::glBegin(GL_QUADS);
				::glColor3f(text.color.R, text.color.G, text.color.B);

				::glNormal3f( 0.0f, 0.0f, 1.0f);

				::glVertex3f( text.position.x - text.size.width/2, text.position.y + text.size.height/2, text.position.z -MILLI/2);		// Övre vänstra
				::glVertex3f( text.position.x + text.size.width/2, text.position.y + text.size.height/2, text.position.z -MILLI/2);		// Övre högra
				::glVertex3f( text.position.x + text.size.width/2, text.position.y - text.size.height/2, text.position.z -MILLI/2);		// Nedre vänstra
				::glVertex3f( text.position.x - text.size.width/2, text.position.y - text.size.height/2, text.position.z -MILLI/2);		// Nedre högra
			::glEnd();
		}

		::glBegin(GL_LINES);

			::glColor3f(text.letter.color.R, text.letter.color.G, text.letter.color.B);

			::glNormal3f( 0.0f, 0.0f, 1.0f);
			unsigned int line = 0;
			for(unsigned int i = 0, j = 0; i < text.Length(); i++, j++)
			{
				if((text.letter.size.width + text.letter.spacing)*j + text.letter.size.width*1.5 > text.size.width || text[i] == '\n')
				{
					if(text[i] == '\n')
						i++;

					line++;
					j = 0;

					if(text[i] == ' ')
						i++;
				}

				if(text.letter.size.height*(line+1)*1.5 + text.letter.size.height/2 > text.size.height)
					break;

				Point cur_letter_pos(text.position.x-text.size.width/2 + text.letter.size.width +(text.letter.size.width+text.letter.spacing)*j, text.position.y + text.size.height/2 - text.letter.size.height -(line* text.letter.size.height*1.5), text.position.z);

				switch(text[i])
				{
					case 'A':
						A(cur_letter_pos, text.letter.size);
						break;
					case 'B':
						B(cur_letter_pos, text.letter.size);
						break;
					case 'C':
						C(cur_letter_pos, text.letter.size);
						break;
					case 'D':
						D(cur_letter_pos, text.letter.size);
						break;
					case 'E':
						E(cur_letter_pos, text.letter.size);
						break;
					case 'F':
						F(cur_letter_pos, text.letter.size);
						break;
					case 'G':
						G(cur_letter_pos, text.letter.size);
						break;
					case 'H':
						H(cur_letter_pos, text.letter.size);
						break;
					case 'I':
						I(cur_letter_pos, text.letter.size);
						break;
					case 'J':
						J(cur_letter_pos, text.letter.size);
						break;
					case 'K':
						K(cur_letter_pos, text.letter.size);
						break;
					case 'L':
						L(cur_letter_pos, text.letter.size);
						break;
					case 'M':
						M(cur_letter_pos, text.letter.size);
						break;
					case 'N':
						N(cur_letter_pos, text.letter.size);
						break;
					case 'O':
						O(cur_letter_pos, text.letter.size);
						break;
					case 'P':
						P(cur_letter_pos, text.letter.size);
						break;
					case 'Q':
						Q(cur_letter_pos, text.letter.size);
						break;
					case 'R':
						R(cur_letter_pos, text.letter.size);
						break;
					case 'S':
						S(cur_letter_pos, text.letter.size);
						break;
					case 'T':
						T(cur_letter_pos, text.letter.size);
						break;
					case 'U':
						U(cur_letter_pos, text.letter.size);
						break;
					case 'V':
						V(cur_letter_pos, text.letter.size);
						break;
					case 'W':
						W(cur_letter_pos, text.letter.size);
						break;
					case 'X':
						X(cur_letter_pos, text.letter.size);
						break;
					case 'Y':
						Y(cur_letter_pos, text.letter.size);
						break;
					case 'Z':
						Z(cur_letter_pos, text.letter.size);
						break;

					case '0':
						Num0(cur_letter_pos, text.letter.size);
						break;
					case '1':
						Num1(cur_letter_pos, text.letter.size);
						break;
					case '2':
						Num2(cur_letter_pos, text.letter.size);
						break;
					case '3':
						Num3(cur_letter_pos, text.letter.size);
						break;
					case '4':
						Num4(cur_letter_pos, text.letter.size);
						break;
					case '5':
						Num5(cur_letter_pos, text.letter.size);
						break;
					case '6':
						Num6(cur_letter_pos, text.letter.size);
						break;
					case '7':
						Num7(cur_letter_pos, text.letter.size);
						break;
					case '8':
						Num8(cur_letter_pos, text.letter.size);
						break;
					case '9':
						Num9(cur_letter_pos, text.letter.size);
						break;

					case '!':
						ExclamationMark(cur_letter_pos, text.letter.size);
						break;
					case '?':
						QuestionMark(cur_letter_pos, text.letter.size);
						break;
					case '.':
						Period(cur_letter_pos, text.letter.size);
						break;
					case ',':
						Comma(cur_letter_pos, text.letter.size);
						break;
					case ':':
						Colon(cur_letter_pos, text.letter.size);
						break;
					case '/':
						Slash(cur_letter_pos, text.letter.size);
						break;
					case '=':
						Equality_Sign(cur_letter_pos, text.letter.size);
						break;
					case '+':
						Plus(cur_letter_pos, text.letter.size);
						break;
					case '-':
						Minus(cur_letter_pos, text.letter.size);
						break;

					default:
						break;
				}
			}
		::glEnd();
	::glPopMatrix();
}

void GLFont::A(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra
	::glVertex3f( pos.x, pos.y + size.height/2, pos.z );					// Toppen ^

	::glVertex3f( pos.x, pos.y + size.height/2, pos.z );					// Toppen ^
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Nedre högra

	::glVertex3f( pos.x - 5*size.width/16, pos.y - size.height/8, pos.z );	// 5/16 (exakt uträknat) av mitten, vänsterifrån
	::glVertex3f( pos.x + 5*size.width/16, pos.y - size.height/8, pos.z );	// 5/16 av mitten, högerifrån
}

void GLFont::B(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänstra

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänster
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// vänster mitt

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av högra, nerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Botten-vänster
}

void GLFont::C(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån

	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av höger, uppifrån
}

void GLFont::D(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Vänster uppe
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av höger, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av höger, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Vänster nere

	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Vänster nere
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Vänster uppe
}

void GLFont::E(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänstra

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Top-vänster
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Top-höger

	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// Mellan-vänster
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// Mellan- 3höger/4

	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Botten-vänster
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// botten-höger
}

void GLFont::F(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänstra

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Top-vänster
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Top-höger

	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// Mellan-vänster
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// Mellan- 3höger/4
}

void GLFont::G(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av höger, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av höger, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av höger, nerifråns
	::glVertex3f( pos.x + size.width/2, pos.y, pos.z );						// Höger mitt

	::glVertex3f( pos.x + size.width/2, pos.y, pos.z );						// Höger mitt
	::glVertex3f( pos.x, pos.y, pos.z );									// Mitt
}

void GLFont::H(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Vänster nere
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Vänster uppe

	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// Vänster mitt
	::glVertex3f( pos.x + size.width/2, pos.y, pos.z );						// Höger mitt

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Mitt nere
	::glVertex3f( pos.x +  size.width/2, pos.y + size.height/2, pos.z );	// Mitt uppe
}

void GLFont::I(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x, pos.y - size.height/2, pos.z );					// Mitt nere
	::glVertex3f( pos.x, pos.y + size.height/2, pos.z );					// Mitt uppe
}

void GLFont::J(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av höger, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av höger, nerifrån
	::glVertex3f( pos.x + size.width/2, pos.y, pos.z );						// Höger mitt

	::glVertex3f( pos.x + size.width/2, pos.y, pos.z );						// Höger mitt
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Höger topp
}

void GLFont::K(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänstra
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra

	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// Vänster mitt
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Nedre högra

	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// Vänster mitt
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Övre högra
}

void GLFont::L(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänstra
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra

	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Botten-vänster
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// botten-höger
}

void GLFont::M(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra
	::glVertex3f( pos.x - 3*size.width/8, pos.y + size.height/2, pos.z );		// Vänstra toppen

	::glVertex3f( pos.x - 3*size.width/8, pos.y + size.height/2, pos.z );		// Vänstra toppen
	::glVertex3f( pos.x, pos.y, pos.z );									// Mitten

	::glVertex3f( pos.x, pos.y, pos.z );									// Mitten
	::glVertex3f( pos.x + 3*size.width/8, pos.y + size.height/2, pos.z );		// Högra toppen

	::glVertex3f( pos.x + 3*size.width/8, pos.y + size.height/2, pos.z );		// Högra toppen
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Nedre högra
}

void GLFont::N(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Vänstra toppen

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Vänstra toppen
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Nedre högra

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Nedre högra
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Högra toppen
}

void GLFont::O(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av höger, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av höger, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån
}

void GLFont::P(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänstra

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänster
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// vänster mitt
}

void GLFont::Q(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av höger, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av höger, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån


	::glVertex3f( pos.x, pos.y - size.height/4, pos.z );					// en 1/4 ifrån Mitt
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Nedre högra hörnet
}

void GLFont::R(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänstra

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänster
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// vänster mitt

	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// vänster mitt
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// högre nere
}

void GLFont::S(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån
	::glVertex3f( pos.x - size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/4, pos.y, pos.z );						// 1/4 från vänster mitt

	::glVertex3f( pos.x - size.width/4, pos.y, pos.z );						// 1/4 från vänster mitt
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 från höger mitt

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 från höger mitt
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av höger, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av höger, nerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av höger, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av höger, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av bot, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av bot, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av bot, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av bot, vänsterifrån
	::glVertex3f( pos.x - size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av vänstra, nerifrån
}

void GLFont::T(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Top-vänster
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Top-höger

	::glVertex3f( pos.x, pos.y - size.height/2, pos.z );					// Mitt nere
	::glVertex3f( pos.x, pos.y + size.height/2, pos.z );					// Mitt uppe
}

void GLFont::U(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Top höger
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån

	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Top vänster
}

void GLFont::V(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Top-vänster
	::glVertex3f( pos.x, pos.y - size.height/2, pos.z );					// Mitt nere

	::glVertex3f( pos.x, pos.y - size.height/2, pos.z );					// Mitt nere
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Top-höger
}

void GLFont::W(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänstra
	::glVertex3f( pos.x - 3*size.width/8, pos.y - size.height/2, pos.z );		// Vänstra botten

	::glVertex3f( pos.x - 3*size.width/8, pos.y - size.height/2, pos.z );		// Vänstra botten
	::glVertex3f( pos.x, pos.y, pos.z );									// Mitten

	::glVertex3f( pos.x, pos.y, pos.z );									// Mitten
	::glVertex3f( pos.x + 3*size.width/8, pos.y - size.height/2, pos.z );		// Högra botten

	::glVertex3f( pos.x + 3*size.width/8, pos.y - size.height/2, pos.z );		// Högra botten
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Övre högra
}

void GLFont::X(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Top-höger
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Bott-vänster

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Top-vänster
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Bott-högre
}

void GLFont::Y(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x, pos.y - size.height/2, pos.z );					// Mitt-nere
	::glVertex3f( pos.x, pos.y, pos.z );									// Mitt

	::glVertex3f( pos.x, pos.y, pos.z );									// Mitt
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Top-höger

	::glVertex3f( pos.x, pos.y, pos.z );									// Mitt
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Top-vänster
}

void GLFont::Z(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Top-vänster
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Top-höger

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Top-höger
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Bott-vänster

	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Botten-vänster
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Botten-höger
}

// ---------------------------- \\ NUMBERS // ----------------------------

void GLFont::Num0(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av höger, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av höger, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån
	::glVertex3f( pos.x - size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av vänstra, nerifrån
}

void GLFont::Num1(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån

	::glVertex3f( pos.x, pos.y - size.height/2, pos.z );					// Mitt nere
	::glVertex3f( pos.x, pos.y + size.height/2, pos.z );					// Mitt uppe

	::glVertex3f( pos.x, pos.y + size.height/2, pos.z );					// Mitt uppe
	::glVertex3f( pos.x - size.width/4, pos.y + size.height/4, pos.z );		// somewhere out in space
}

void GLFont::Num2(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänster
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// vänster nere

	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Vänster nere
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Höger nere
}

void GLFont::Num3(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänster
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// vänster mitt

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av högra, nerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Botten-vänster
}

void GLFont::Num4(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänster
	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// Mitt vänster

	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// Mitt vänster
	::glVertex3f( pos.x + size.width/2, pos.y, pos.z );						// Mitt höger

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Övre höger
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/2, pos.z );		// Nedre höger
}

void GLFont::Num5(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Övre höger
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänster

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänster
	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// vänster mitt

	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// vänster mitt
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av högra, nerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Botten-vänster
}

void GLFont::Num6(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/4, pos.z );		// 1/4 av höger, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, vänsterifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av höger, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/4, pos.z );		// 1/4 av höger, nerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av höger, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av höger, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, från höger

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, från höger
	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );						// Vänster mitt
}

void GLFont::Num7(const Point& pos, const Size& size)
{

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänster
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Övre höger

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Övre höger
	::glVertex3f( pos.x, pos.y - size.height/2, pos.z );					// Nedre mitt
}

void GLFont::Num8(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån
	::glVertex3f( pos.x - size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/4, pos.y, pos.z );						// 1/4 från vänster mitt

	::glVertex3f( pos.x - size.width/4, pos.y, pos.z );						// 1/4 från vänster mitt
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av högra, nerifrån
	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av bot, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av bot, vänsterifrån
	::glVertex3f( pos.x - size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av vänstra, nerifrån

	::glVertex3f( pos.x - size.width/2, pos.y - 3*size.height/8, pos.z );	// 1/8 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av vänstra, nerifrån

	::glVertex3f( pos.x - size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av vänstra, nerifrån
	::glVertex3f( pos.x - size.width/4, pos.y, pos.z );						// 1/4 från vänster mitt
}

void GLFont::Num9(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top,  högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån

	::glVertex3f( pos.x - size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, vänsterifrån
	::glVertex3f( pos.x - size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av vänstra, uppifrån

	::glVertex3f( pos.x - size.width/2, pos.y + size.height/8, pos.z );		// 3/8 av vänstra, uppifrån
	::glVertex3f( pos.x - size.width/4, pos.y, pos.z );						// 1/4 från vänster mitt

	::glVertex3f( pos.x - size.width/4, pos.y, pos.z );						// 1/4 från vänster mitt
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån


	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 1/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av högra, nerifrån

	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );		// 3/8 av högra, nerifrån
	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y - size.height/2, pos.z );		// 1/4 av botten, högerifrån
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Nedre vänstra
}

//----------------------------\\ MISC SIGNS //----------------------------


void GLFont::ExclamationMark(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x, pos.y + size.height/2, pos.z );					// Mitt uppe
	::glVertex3f( pos.x, pos.y - size.height/8, pos.z );					// 3/8 från nedre mitt

	::glVertex3f( pos.x, pos.y - 3*size.height/8, pos.z );					// 1/8 från nedre mitt
	::glVertex3f( pos.x, pos.y - size.height/2, pos.z );					// Mitt nere
}

void GLFont::Equality_Sign(const Point& pos, const Size& size)
{
	// Nedre strecket
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/8, pos.z );
	::glVertex3f( pos.x + size.width/2, pos.y - size.height/8, pos.z );

	// Övre strecket
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/8, pos.z );
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );
}

void GLFont::QuestionMark(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x - size.width/2, pos.y + size.height/2, pos.z );		// Övre vänster
	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y + size.height/2, pos.z );		// 1/4 av top, högerifrån
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 1/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + size.height/8, pos.z );		// 1/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 3/8 av högra, uppifrån

	::glVertex3f( pos.x + size.width/2, pos.y + 3*size.height/8, pos.z );	// 3/8 av högra, uppifrån
	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån

	::glVertex3f( pos.x + size.width/4, pos.y, pos.z );						// 1/4 av mitt, högerifrån
	::glVertex3f( pos.x, pos.y, pos.z );									// Mitt

	::glVertex3f( pos.x, pos.y, pos.z );									// Mitt
	::glVertex3f( pos.x, pos.y - 2*size.height/8, pos.z );					// 3/8 från nedre mitt

	::glVertex3f( pos.x, pos.y - 3*size.height/8, pos.z );					// 1/8 från nedre mitt
	::glVertex3f( pos.x, pos.y - size.height/2, pos.z );					// Mitt nere
}

void GLFont::Period(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x, pos.y - 3*size.height/8, pos.z );					// 1/8 från nedre mitt
	::glVertex3f( pos.x, pos.y - size.height/2, pos.z );					// Mitt nere
}

void GLFont::Comma(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x, pos.y - 3*size.height/8, pos.z );					// 1/8 från nedre mitt
	::glVertex3f( pos.x - size.height/8, pos.y - size.height/2, pos.z );	// Höfta till de
}

void GLFont::Colon(const Point& pos, const Size& size)
{
	// Nedre
	::glVertex3f( pos.x, pos.y - 2*size.height/8, pos.z );
	::glVertex3f( pos.x, pos.y - size.height/8, pos.z );

	// Övre
	::glVertex3f( pos.x, pos.y + size.height/8, pos.z );
	::glVertex3f( pos.x, pos.y + 2*size.height/8, pos.z );
}

void GLFont::Slash(const Point& pos, const Size& size)
{
	::glVertex3f( pos.x + size.width/2, pos.y + size.height/2, pos.z );		// Top-höger
	::glVertex3f( pos.x - size.width/2, pos.y - size.height/2, pos.z );		// Bott-vänster
}

void GLFont::Minus(const Point& pos, const Size& size)
{
	// Strecket
	::glVertex3f( pos.x - size.width/2, pos.y, pos.z );
	::glVertex3f( pos.x + size.width/2, pos.y, pos.z );
}

void GLFont::Plus(const Point& pos, const Size& size)
{
	// För att få det symetriskt.
	double half_len = (size.width < size.height ? size.width/2 : size.height/2);

	// Horisontell
	::glVertex3f( pos.x - half_len, pos.y, pos.z );
	::glVertex3f( pos.x + half_len, pos.y, pos.z );

	// Vertikal
	::glVertex3f( pos.x, pos.y - half_len, pos.z );
	::glVertex3f( pos.x, pos.y + half_len, pos.z );
}
