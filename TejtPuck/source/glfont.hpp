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

#ifndef GLFONT__HPP
#define GLFONT__HPP

#include "platform.hpp"

#include "body.hpp"
#include "rotation.hpp"
#include "text.hpp"

class GLFont
{
	public:
		GLFont(const Text& set_text)
			: text(set_text)
		{
		}
		void Draw();

	private:
		void A(const Point& pos, const Size& size);
		void B(const Point& pos, const Size& size);
		void C(const Point& pos, const Size& size);
		void D(const Point& pos, const Size& size);
		void E(const Point& pos, const Size& size);
		void F(const Point& pos, const Size& size);
		void G(const Point& pos, const Size& size);
		void H(const Point& pos, const Size& size);
		void I(const Point& pos, const Size& size);
		void J(const Point& pos, const Size& size);
		void K(const Point& pos, const Size& size);
		void L(const Point& pos, const Size& size);
		void M(const Point& pos, const Size& size);
		void N(const Point& pos, const Size& size);
		void O(const Point& pos, const Size& size);
		void P(const Point& pos, const Size& size);
		void Q(const Point& pos, const Size& size);
		void R(const Point& pos, const Size& size);
		void S(const Point& pos, const Size& size);
		void T(const Point& pos, const Size& size);
		void U(const Point& pos, const Size& size);
		void V(const Point& pos, const Size& size);
		void W(const Point& pos, const Size& size);
		void X(const Point& pos, const Size& size);
		void Y(const Point& pos, const Size& size);
		void Z(const Point& pos, const Size& size);

		void Num0(const Point& pos, const Size& size);
		void Num1(const Point& pos, const Size& size);
		void Num2(const Point& pos, const Size& size);
		void Num3(const Point& pos, const Size& size);
		void Num4(const Point& pos, const Size& size);
		void Num5(const Point& pos, const Size& size);
		void Num6(const Point& pos, const Size& size);
		void Num7(const Point& pos, const Size& size);
		void Num8(const Point& pos, const Size& size);
		void Num9(const Point& pos, const Size& size);

		void ExclamationMark(const Point& pos, const Size& size);
		void Equality_Sign(const Point& pos, const Size& size);
		void QuestionMark(const Point& pos, const Size& size);
		void Period(const Point& pos, const Size& size);
		void Comma(const Point& pos, const Size& size);
		void Colon(const Point& pos, const Size& size);
		void Slash(const Point& pos, const Size& size);
		void Minus(const Point& pos, const Size& size);
		void Plus(const Point& pos, const Size& size);

		Text text;
};

#endif	// GLFONT__HPP
