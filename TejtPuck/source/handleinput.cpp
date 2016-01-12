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

#include "handleinput.hpp"

void HandleInput(const ::SDL_KeyboardEvent& key, std::string& Buffer)
{
    switch(key.keysym.sym)
    {
    	case SDLK_a:
    		Buffer += "A";
    		break;
    	case SDLK_b:
    		Buffer += "B";
    		break;
    	case SDLK_c:
    		Buffer += "C";
    		break;
    	case SDLK_d:
    		Buffer += "D";
    		break;
    	case SDLK_e:
    		Buffer += "E";
    		break;
    	case SDLK_f:
    		Buffer += "F";
    		break;
    	case SDLK_g:
    		Buffer += "G";
    		break;
    	case SDLK_h:
    		Buffer += "H";
    		break;
    	case SDLK_i:
    		Buffer += "I";
    		break;
    	case SDLK_j:
    		Buffer += "J";
    		break;
    	case SDLK_k:
    		Buffer += "K";
    		break;
    	case SDLK_l:
    		Buffer += "L";
    		break;
    	case SDLK_m:
    		Buffer += "M";
    		break;
    	case SDLK_n:
    		Buffer += "N";
    		break;
    	case SDLK_o:
    		Buffer += "O";
    		break;
    	case SDLK_p:
    		Buffer += "P";
    		break;
    	case SDLK_q:
    		Buffer += "Q";
    		break;
    	case SDLK_r:
    		Buffer += "R";
    		break;
    	case SDLK_s:
    		Buffer += "S";
    		break;
    	case SDLK_t:
    		Buffer += "T";
    		break;
    	case SDLK_u:
    		Buffer += "U";
    		break;
    	case SDLK_v:
    		Buffer += "V";
    		break;
    	case SDLK_w:
    		Buffer += "W";
    		break;
    	case SDLK_x:
    		Buffer += "X";
    		break;
    	case SDLK_y:
    		Buffer += "Y";
    		break;
    	case SDLK_z:
    		Buffer += "Z";
    		break;

    	case SDLK_0:
    		Buffer += "0";
    		break;
    	case SDLK_1:
    		Buffer += "1";
    		break;
    	case SDLK_2:
    		Buffer += "2";
    		break;
    	case SDLK_3:
    		Buffer += "3";
    		break;
    	case SDLK_4:
    		Buffer += "4";
    		break;
    	case SDLK_5:
    		Buffer += "5";
    		break;
    	case SDLK_6:
    		Buffer += "6";
    		break;
    	case SDLK_7:
    		Buffer += "7";
    		break;
    	case SDLK_8:
    		Buffer += "8";
    		break;
    	case SDLK_9:
    		Buffer += "9";
    		break;

        case SDLK_EXCLAIM:
            Buffer += "!";
            break;
        case SDLK_QUESTION:
            Buffer += "?";
            break;
    	case SDLK_PERIOD:
    		Buffer += ".";
    		break;
    	case SDLK_COMMA:
    		Buffer += ",";
    		break;
    	case SDLK_COLON:
    		Buffer += ":";
    		break;
    	case SDLK_SLASH:
    		Buffer += "/";
    		break;
    	case SDLK_EQUALS:
    		Buffer += "=";
    		break;
    	case SDLK_PLUS:
			Buffer += "+";
    		break;
    	case SDLK_MINUS:
    		Buffer += "-";
    		break;
        case SDLK_SPACE:
            Buffer += " ";
            break;

        case SDLK_BACKSPACE:
			if(Buffer.size() > 0)
				Buffer = Buffer.substr(0, Buffer.size()-1);
            break;

        default:
			break;
    }
}

std::string StripCharacters(const std::string& raw_data, const std::string& characters)
{
    std::string approved_data;
    zinara::copy_if(raw_data.begin(), raw_data.end(), std::back_inserter(approved_data), no_unwanted_characters(characters));
    return approved_data;
}
