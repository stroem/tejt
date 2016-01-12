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

#ifndef GAME_HPP
#define GAME_HPP

#include "menu.hpp"
#include "gameevents.hpp"
#include "activityhandler.hpp"
#include "connection.hpp"

enum WorldIndex{
	GREEN = 0,
	RED,
	FLOOR,
	LEFTWALL,
	RIGHTWALL,
	PUCK,
	GREEN_SCORE,
	RED_SCORE
};

enum Player {
	PLAYER_GREEN = 0,
	PLAYER_RED
};

class Game
	: public ActivityHandler
{
	public:
        Game(bool host, std::string set_opponent_ip, connection_ptr set_server_connection = connection_ptr(), const std::string& set_opponent_nick = std::string());
        virtual ~Game();

		virtual void Think(unsigned int elapsed_time);
        virtual void OnKeyDown(const ::SDL_KeyboardEvent& key);
        virtual void OnMouseMove(const ::SDL_MouseMotionEvent& motion);

        void PuckMove();
        void PadMove(Player pad_color, const Speed &motion);

	private:
		double Positive(const double num) { return (num < 0 ? num*(-1) : num); }

        Area board;

        Body puck, greenPad, redPad, lifetotem[2];

        double wallwidth;
        double maxSpeed;
        unsigned int lastmove;
        int score[2];
        bool host, col;

        zinara::ip::udp::socket server_socket; // Handles incomming data
        zinara::ip::udp::socket client_socket; // Sends outgoing data

        connection_ptr server_connection;
        std::string opponent_ip;
        std::string opponent_nick;
        // ME:192.168.0.166
        // Per:192.168.0.42
};

#endif
