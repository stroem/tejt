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

#include "game.hpp"

typedef zinara::basic_stream_buffer<std::allocator> buffer_type;

Game::Game(bool set_host, std::string set_opponent_ip, connection_ptr set_server_connection, const std::string& set_opponent_nick)
{
	/// Initiera medlemsvariabler
    score[PLAYER_GREEN] = score[PLAYER_RED] = 0;
    lastmove = 0;
    maxSpeed = 0.1;
    host = set_host;
	opponent_ip = set_opponent_ip;
	opponent_nick = set_opponent_nick;
	server_connection = set_server_connection;

	board = Area(Point(), Size(5.0, 0.0, 10.0));
	board.position = Point(board.size.width/2, 0.0, board.size.depth/2);
	wallwidth = 1.5;

	/// The allseeing eye!
    eye.position.x = board.position.x;
    eye.position.y = board.size.depth/3;
    eye.position.z = board.size.depth+3*board.size.depth/8;

    eye.rotation.x = 20.0;

    if(!host)
    {
		eye.position.z *= -0.28;
		eye.rotation.y = 180;
    }

	/// GrÃƒÂ¶n
    greenPad.size.width = 1.2;
    greenPad.size.depth = 0.2;
    greenPad.size.height = 0.4;
    greenPad.position.x = board.position.x;
    greenPad.position.y = greenPad.size.height/2.0;
    greenPad.position.z = board.position.z + board.size.depth/3;
    greenPad.color = Color(0.3, 0.5, 0.3);
	greenPad.style = CUBE_BORDERED;

	/// RÃƒÂ¶de baronen
    redPad.size.width = greenPad.size.width;
    redPad.size.depth = greenPad.size.depth;
    redPad.size.height = greenPad.size.height;
    redPad.position.x = board.position.x;
    redPad.position.y = redPad.size.height/2.0;
    redPad.position.z = board.position.z - board.size.depth/3;
    redPad.color = Color(0.5, 0.3, 0.3);
	redPad.style = CUBE_BORDERED;

	/// LÃƒÂ¤gg till GrÃƒÂ¶n
	world.push_back(object_ptr(new Body(greenPad)));

	/// LÃƒÂ¤gg till RÃƒÂ¶d
	world.push_back(object_ptr(new Body(redPad)));

	/// LÃ¤gg till Botten
	world.push_back(object_ptr(new Body(Body(Point(board.position.x, -0.27, board.position.z),
								Size(board.size.width, 0.46, board.size.depth),
								Color(0.5, 0.45, 0.5), CUBE_BORDERED))));

	/// LÃ¤gg till VÃ¤nstra vÃ¤ggen
	world.push_back(object_ptr(new Body(Body(Point(board.position.x - board.size.width/2 - wallwidth/2 - 0.02, 0.0, board.position.z),
								Size(wallwidth, 1.0, board.size.depth),
								Color(0.5, 0.5, 0.5), CUBE_BORDERED))));

	/// LÃ¤gg till HÃ¶gra vÃ¤ggen
	world.push_back(object_ptr(new Body(Body(Point(board.position.x + board.size.width/2 + wallwidth/2 + 0.02, 0.0, board.position.z),
								Size(wallwidth, 1.0, board.size.depth),
								Color(0.5, 0.5, 0.5), CUBE_BORDERED))));


	/// Pucken
    puck.size.width = 0.3;
    puck.size.depth = 0.3;
    puck.size.height = 0.3;
    puck.position.x = greenPad.position.x;
    puck.position.y = puck.size.height/2.0;
    puck.position.z = board.position.z + board.size.depth/8;
    puck.color = Color(0.55, 0.45, 0.2);
	puck.style = CUBE_BORDERED;

	/// LÃƒÂ¤gg till Pucken
	world.push_back(object_ptr(new Body(puck)));

	//definera lifetotems
	lifetotem[0] = Body(Point(board.position.x + board.size.width/2 + wallwidth/2, 0.0, board.position.z + wallwidth),
								Size(wallwidth/2, 2.5, wallwidth/2),
								Color(0.3, 0.5, 0.3), CUBE_BORDERED);

	lifetotem[1] = Body(Point(board.position.x - board.size.width/2 - wallwidth/2, 0.0, board.position.z - wallwidth),
								Size(wallwidth/2, 2.5, wallwidth/2),
								Color(0.5, 0.3, 0.3), CUBE_BORDERED);

	lifetotem[0].position.y = 0.52 + lifetotem[0].size.height/2;
	lifetotem[1].position.y = 0.52 + lifetotem[1].size.height/2;

	// Lägg till våra liv-visualiseringar
	world.push_back(object_ptr(new Body(lifetotem[0])));
	world.push_back(object_ptr(new Body(lifetotem[1])));

    zinara::ip::udp::socket::non_blocking_io command(true);
    zinara::ip::udp::address local("0.0.0.0", SERVER_PORT);

    server_socket.open(local.get_family());
    server_socket.io_control(command);
    server_socket.bind(local);

    client_socket.open(zinara::ip::v4);
    client_socket.io_control(command);
}

Game::~Game()
{

}

void Game::Think(unsigned int elapsed_time)
{
	// Hantera livpelarna
	lifetotem[0].size.height = 2.5 - 0.5*score[PLAYER_RED];
	lifetotem[1].size.height = 2.5 - 0.5*score[PLAYER_GREEN];
	lifetotem[0].position.y = 0.52 + lifetotem[0].size.height/2;
	lifetotem[1].position.y = 0.52 + lifetotem[1].size.height/2;

	*world[RED_SCORE] = lifetotem[1];
	*world[GREEN_SCORE] = lifetotem[0];

	// Kolla om någon vunnit
	if( score[PLAYER_GREEN] >= 5 || score[PLAYER_RED] >= 5)
	{
		if(server_connection.get() == 0)	// Om man använder direktanslutning
		{
			if(score[PLAYER_GREEN] >= 5)	// Om grön pad är segraren
			{
				if(host)
					SetNextActivity(new Fade(new Menu("WINNER!"), world, eye), true);
				else
					SetNextActivity(new Fade(new Menu("LOSER!"), world, eye), true);
			}
			else	// röd pad vann
			{
				if(host)
					SetNextActivity(new Fade(new Menu("LOSER!"), world, eye), true);
				else
					SetNextActivity(new Fade(new Menu("WINNER!"), world, eye), true);
			}
		}
		else
		{
			if(server_connection->good())
			{
				// Hosten har enligt protokollet på sitt ansvar att upplysa servern om
				// att spelet är klart och vem som van, så att spelarna blir available igen
				if(host)
				{
					std::string gameover_msg;
					gameover_msg += "GAMEOVER#";

					if(score[PLAYER_GREEN] >= 5)
					{
						gameover_msg += server_connection->get_nickname();
						gameover_msg += ";";
						gameover_msg += opponent_nick;
					}
					else
					{
						gameover_msg += opponent_nick;
						gameover_msg += ";";
						gameover_msg += server_connection->get_nickname();
					}

					gameover_msg += "\r\n";
					server_connection->put_message(gameover_msg);
				}
				// Vi vill tillbaka till ett server interface, men med samma anslutning.
				SetNextActivity(new Fade(new ServerInterface(server_connection), world, eye), true);
			}
			else	// Ifall anslutning till servern av någon anledning brutits, tillbaka till menyn.
				SetNextActivity(new Fade(new Menu("NO CONN TO SERV"), world, eye), true);
		}
	}
	else
	{
		if(server_connection.get() != 0)	// inte om man använder direktanslutning
		{
			// Tar emot, men gör ingenting med, de packet som skickas av spelservern.
			std::string msg;
			while(server_connection->get_message(msg));
		}

		if(host)
		{
			// Hosten sköter all kollission
			PuckMove();

			// Ta emot data från klienten
			buffer_type buffer;
			zinara::ip::udp::address remote;
			while(server_socket.recvfrom(buffer, remote) != SOCKET_ERROR)
			{
				// Det enda klienten skickar är mousemoves
				MouseMotionEvent game_event;
				buffer.getn(reinterpret_cast<char*>(&game_event), sizeof(MouseMotionEvent));
				Speed mouseMotion(game_event.x, 0, game_event.z);
				PadMove(PLAYER_RED, mouseMotion);	// Flytta padden
				buffer.clear();
			}

			// Skicka data till klienten
			zinara::ip::udp::address opponent(opponent_ip, SERVER_PORT);

			ServerGameEvent net_event;

			net_event.x = (*world[GREEN]).position.x;
			net_event.z = (*world[GREEN]).position.z;
			net_event.type = GREEN;

			buffer.putn(reinterpret_cast<char*>(&net_event), sizeof(ServerGameEvent));
			client_socket.sendto(buffer, opponent);
			buffer.clear();

			net_event.x = (*world[RED]).position.x;
			net_event.z = (*world[RED]).position.z;
			net_event.type = RED;

			buffer.putn(reinterpret_cast<char*>(&net_event), sizeof(ServerGameEvent));
			client_socket.sendto(buffer, opponent);
			buffer.clear();

			net_event.x = (*world[PUCK]).position.x;
			net_event.z = (*world[PUCK]).position.z;
			net_event.type = PUCK;

			buffer.putn(reinterpret_cast<char*>(&net_event), sizeof(ServerGameEvent));
			client_socket.sendto(buffer, opponent);
			buffer.clear();
		}
		else
		{
			// Ta emot och hantera datan från servern.
			buffer_type buffer;
			zinara::ip::udp::address remote;
			while(server_socket.recvfrom(buffer, remote) != SOCKET_ERROR)
			{
				ServerGameEvent game_event;
				buffer.getn(reinterpret_cast<char*>(&game_event), sizeof(ServerGameEvent));

				switch(game_event.type)
				{
					case RED:
						(*world[RED]).position.x = game_event.x;
						(*world[RED]).position.z = game_event.z;
					break;

					case PUCK:
						(*world[PUCK]).position.x = game_event.x;
						(*world[PUCK]).position.z = game_event.z;
					break;

					case GREEN:
						(*world[GREEN]).position.x = game_event.x;
						(*world[GREEN]).position.z = game_event.z;
					break;
					case GREEN_SCORE:
						score[PLAYER_GREEN] = int(game_event.x);
					break;
					case RED_SCORE:
						score[PLAYER_RED] = int(game_event.x);
					break;
				}
			}
		}
	}
}

void Game::OnKeyDown(const ::SDL_KeyboardEvent& key)
{
	// Ändrar kamerans position
	switch(key.keysym.sym)
	{
		// Sidorna
		case SDLK_LEFT:
			eye.position.x -= 0.1;
		break;
		case SDLK_RIGHT:
			eye.position.x += 0.1;
		break;

		// Upp & ner
		case SDLK_UP:
			eye.position.y += 0.1;
		break;
		case SDLK_DOWN:
			eye.position.y -= 0.1;
		break;

		// Fram, bak
		case SDLK_COMMA:
			eye.position.z -= 0.1;
		break;
		case SDLK_PERIOD:
			eye.position.z += 0.1;
		break;

		default: break;
	}
}

void Game::OnMouseMove(const ::SDL_MouseMotionEvent& motion)
{
	Speed mouseMotion(double(motion.xrel)/100.0, 0, double(motion.yrel)/100.0);	// Musens relativa förflyttning

	// Hosten flyttar padden, medan client skickar sina uppgifter till hosten, som sköter förflyttningen.
	if(host)
	{
		PadMove(PLAYER_GREEN, mouseMotion);
	}
	else
	{
	    MouseMotionEvent net_event;

	    net_event.x = -mouseMotion.x;
	    net_event.z = -mouseMotion.z;

	    zinara::ip::udp::address opponent(opponent_ip, SERVER_PORT);

	    buffer_type buffer;
	    buffer.putn(reinterpret_cast<char*>(&net_event), sizeof(MouseMotionEvent));
	    client_socket.sendto(buffer, opponent);
	}
}

// Puckens förflyttning och kollission
void Game::PuckMove()
{
	if(host)
	{
		bool collided = false;

		double timeToMove = double(SDL_GetTicks() - lastmove)/10.0;

		// Puckens nya position
		Point newPuck(puck.position.x + puck.velocity.x*timeToMove, puck.position.y, puck.position.z + puck.velocity.z*timeToMove);

		// Skapa en ny kropp, som representerar det omrÃƒÂ¥de som pucken skall ha som hitbox
		Body hitBox(Point((puck.position.x + newPuck.x)/2.0, 0.4, (puck.position.z + newPuck.z)/2.0),
					Size(Positive(puck.position.x - newPuck.x) + puck.size.width,
						 0.1,
						 Positive(puck.position.z - newPuck.z) + puck.size.depth),
					Color(1, 0, 0));

		/// Om pucken krockar med vÃƒÂ¤nster vÃƒÂ¤gg
		if(hitBox.position.x - puck.size.width/2.0 < board.position.x - board.size.width/2)
		{
			collided = true;
			puck.velocity.x *= -1.0;
			puck.position.x = board.position.x - board.size.width/2.0 + puck.size.width/2.0;

			lastmove += (unsigned int)(Positive(puck.position.x - (board.position.x - board.size.width/2.0 + puck.size.width/2.0))/puck.velocity.x);
		}
		/// Om pucken krockar med hÃƒÂ¶ger vÃƒÂ¤gg
		if(hitBox.position.x + puck.size.width/2.0 > board.position.x + board.size.width/2)
		{
			collided = true;
			puck.velocity.x *= -1.0;
			puck.position.x = board.position.x + board.size.width/2.0 - puck.size.width/2.0;

			lastmove += (unsigned int)(Positive(puck.position.x - (board.position.x + board.size.width/2.0 + puck.size.width/2.0))/puck.velocity.x);
		}

		/// Om den slÃƒÂ¥r i vÃƒÂ¤ggen bakom grÃƒÂ¶n
		if(hitBox.position.z + puck.size.depth/2.0 > board.position.z + board.size.depth/2)
		{
			collided = true;

			puck.velocity = Speed();
			puck.position.x = board.position.x;
			puck.position.y = puck.size.height/2.0;
			puck.position.z = board.position.z + board.size.depth/8;

			score[RED]++;

			ServerGameEvent net_event;
			net_event.x = score[PLAYER_RED];
			net_event.type = RED_SCORE;

			buffer_type buffer;
			buffer.putn(reinterpret_cast<char*>(&net_event), sizeof(ServerGameEvent));

			zinara::ip::udp::address opponent(opponent_ip, SERVER_PORT);
			client_socket.sendto(buffer, opponent);
			buffer.clear();
		}
		/// Om den gÃƒÂ¥r in i den rÃƒÂ¶das mÃƒÂ¥l
		if(hitBox.position.z - puck.size.depth/2.0 < board.position.z - board.size.depth/2)
		{
			collided = true;

			puck.velocity = Speed();
			puck.position.x = board.position.x;
			puck.position.y = puck.size.height/2.0;
			puck.position.z = board.position.z - board.size.depth/8;

			score[GREEN]++;

			ServerGameEvent net_event;
			net_event.x = score[PLAYER_GREEN];
			net_event.type = GREEN_SCORE;

			buffer_type buffer;
			buffer.putn(reinterpret_cast<char*>(&net_event), sizeof(ServerGameEvent));

			zinara::ip::udp::address opponent(opponent_ip, SERVER_PORT);
			client_socket.sendto(buffer, opponent);
			buffer.clear();
		}

		/// Om pucken krockar med den grÃƒÂ¶na padden
		if(hitBox.position.x + hitBox.size.width/2.0 > greenPad.position.x - greenPad.size.width/2.0
		&& hitBox.position.x - hitBox.size.width/2.0 < greenPad.position.x + greenPad.size.width/2.0
		&& hitBox.position.z + hitBox.size.depth/2.0 > greenPad.position.z - greenPad.size.depth/2.0
		&& hitBox.position.z - hitBox.size.depth/2.0 < greenPad.position.z + greenPad.size.depth/2.0 )
		{
			collided = true;

			// kolla vilken sida av greenPadden den krockar med
			if(puck.position.x + puck.size.width/2.0 > greenPad.position.x - greenPad.size.width/2.0
			&& puck.position.x - puck.size.width/2.0 < greenPad.position.x + greenPad.size.width/2.0)
				puck.velocity.z *= -1.0;

			else if(puck.position.z + puck.size.depth/2.0 > greenPad.position.z - greenPad.size.depth/2.0
				 && puck.position.z - puck.size.depth/2.0 < greenPad.position.z + greenPad.size.depth/2.0)
				puck.velocity.x *= -1.0;
		}

		/// Om pucken krockar med den rÃƒÂ¶da padden
		if(hitBox.position.x + hitBox.size.width/2.0 > redPad.position.x - redPad.size.width/2.0
		&& hitBox.position.x - hitBox.size.width/2.0 < redPad.position.x + redPad.size.width/2.0
		&& hitBox.position.z + hitBox.size.depth/2.0 > redPad.position.z - redPad.size.depth/2.0
		&& hitBox.position.z - hitBox.size.depth/2.0 < redPad.position.z + redPad.size.depth/2.0 )
		{
			collided = true;

			// kolla vilken sida av redPadden den krockar med
			if(puck.position.x + puck.size.width/2.0 > redPad.position.x - redPad.size.width/2.0
			&& puck.position.x - puck.size.width/2.0 < redPad.position.x + redPad.size.width/2.0)
				puck.velocity.z *= -1.0;

			else if(puck.position.z + puck.size.depth/2.0 > redPad.position.z - redPad.size.depth/2.0
				 && puck.position.z - puck.size.depth/2.0 < redPad.position.z + redPad.size.depth/2.0)
				puck.velocity.x *= -1.0;
		}

		/// Flytta pucken
		if(!collided)
		{
			puck.position.x += puck.velocity.x*timeToMove;
			puck.position.z += puck.velocity.z*timeToMove;

			lastmove = ::SDL_GetTicks();
		}
		else if( col )
			puck.velocity = Speed();

		col = collided;


		// Lite friktion ÃƒÂ¤r vÃƒÂ¤l alltid bra ;)
		if((puck.velocity.z < 0 ? puck.velocity.z*(-1) : puck.velocity.z) > 0.01)	// FÃƒÂ¥r aldrig stÃƒÂ¥ helt still, dÃƒÂ¥ kan den astna i no-mans-land
			puck.velocity.z *= 0.9942;
		if((puck.velocity.x < 0 ? puck.velocity.x*(-1) : puck.velocity.x) > 0.01)
			puck.velocity.x *= 0.9942;


		// Uppdatera objektet
		*world[PUCK] = puck;
	}
}

void Game::PadMove(Player player, const Speed &motion)
{
	// Skapa en pekare som pekar pÃƒÂ¥ den pad vi vill anvÃƒÂ¤nda oss av
	Body *pad = (player == PLAYER_GREEN ? &greenPad : &redPad);

	Point newPadPos(pad->position.x + motion.x, pad->position.y, pad->position.z + motion.z);

	Body hitBox(Point((pad->position.x + newPadPos.x)/2.0, 0.48, (pad->position.z + newPadPos.z)/2.0),
				Size(Positive(pad->position.x - newPadPos.x) + pad->size.width,
					0.1,
					Positive(pad->position.z - newPadPos.z) + pad->size.depth), Color());

	/// Om padden krockar med pucken
	if(puck.position.x + puck.size.width/2.0 > hitBox.position.x - hitBox.size.width/2.0
	&& puck.position.x - puck.size.width/2.0 < hitBox.position.x + hitBox.size.width/2.0
	&& puck.position.z + puck.size.depth/2.0 > hitBox.position.z - hitBox.size.depth/2.0
	&& puck.position.z - puck.size.depth/2.0 < hitBox.position.z + hitBox.size.depth/2.0 )
	{
		puck.velocity = motion;

		// Kolla sÃƒÂ¥ man inte ÃƒÂ¶verskrider maxfarten
		if(puck.velocity.z > maxSpeed)
			puck.velocity.z = maxSpeed;
		else if(puck.velocity.z < -maxSpeed)
			puck.velocity.z = -maxSpeed;

		if(puck.velocity.x > maxSpeed)
			puck.velocity.x = maxSpeed;
		else if(puck.velocity.x < -maxSpeed)
			puck.velocity.x = -maxSpeed;
	}
	else	//Padden flyttas bara om man inte krockar (det mÃƒÂ¤rks aldrig att den stannar upp, men det fÃƒÂ¶rhindrar att man fastnar i pucken)
	{
		/// Kolla om man hÃƒÂ¥ller sig pÃƒÂ¥ spelbordet med padden
		//VÃƒÂ¤nster, hÃƒÂ¶ger
		if(newPadPos.x < board.position.x - board.size.width/2.0 + pad->size.width/2.0)
			pad->position.x = board.position.x - board.size.width/2.0 + pad->size.width/2.0;
		else if(newPadPos.x > board.position.x + board.size.width/2.0 - pad->size.width/2.0)
			pad->position.x = board.position.x + board.size.width/2.0 - pad->size.width/2.0;
		else
			pad->position.x = newPadPos.x;

		// fram, bak
		if(player == PLAYER_RED)
		{
			if(newPadPos.z > pad->size.depth/2 + board.position.z - board.size.depth/10)
				pad->position.z = pad->size.depth/2 + board.position.z - board.size.depth/10;
			else if(newPadPos.z < -pad->size.depth/2 + board.position.z - board.size.depth/2)
				pad->position.z = -pad->size.depth/2 + board.position.z - board.size.depth/2;
			else
				pad->position.z = newPadPos.z;
		}
		else
		{
			if(newPadPos.z < pad->size.depth/2 + board.position.z + board.size.depth/10)
				pad->position.z = pad->size.depth/2 + board.position.z + board.size.depth/10;
			else if(newPadPos.z > -pad->size.depth/2 + board.position.z + board.size.depth/2)
				pad->position.z = -pad->size.depth/2 + board.position.z + board.size.depth/2;
			else
				pad->position.z = newPadPos.z;
		}
	}

	/// Uppdatera objektet
	*world[player] = *pad;
}
