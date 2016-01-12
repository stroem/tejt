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

#include "serverinterface.hpp"

ServerInterface::ServerInterface(connection_ptr set_server_connection)
{
    // Här kommer man tillbaka till serverinterfacet från ett färdigt spel
    
	server_connection = set_server_connection;

	eye.position = Point(2.0, 2.0, 5.0);

	world.push_back(object_ptr(new Text()));	// Nicks
	world.push_back(object_ptr(new Text()));	// Chat
	world.push_back(object_ptr(new Text()));	// Input

	world.push_back(object_ptr(new Body(Point(1, 2.2, 0), Size(2.2,1.6,2), Color(1,1,1), CUBE_BORDERED)));			// Main, output
	world.push_back(object_ptr(new Body(Point(3.2, 2, 0), Size(1.2,2,2), Color(1,1,1), CUBE_BORDERED)));			// Playerlist
	world.push_back(object_ptr(new Body(Point(1, 1.15, 0.9), Size(2.2, 0.3, 0.2), Color(1,1,1), CUBE_BORDERED)));	// input
	world.push_back(object_ptr(new Body(Point(2, 0.6, 0.9), Size(0.5, 0.4, 0.2), Color(1,1,1), CUBE_BORDERED)));	// Back-to-menu-box

	Letter functionmarker(Size(0.08, 0.06, 0), 0.02, 2.5, Color(0.3,0.3,1));

	world.push_back(object_ptr(new Text("SAY:", functionmarker, Point(0.1, 1.15, 1+MILLI), Size())));
	world.push_back(object_ptr(new Text("BACK _TO MENU", functionmarker, Point(2, 0.6, 1+MILLI), Size(0.45, 0, 0))));
	world.push_back(object_ptr(new Text("ONLINE PLAYERS:", Letter(Size(0.04, 0.06, 0), 0.02, 1.5, Color(0.3,0.3,1)), Point(3.2, 1.95, 1+MILLI), Size(1.2,2,2))));
}

ServerInterface::ServerInterface(const std::string& set_nickname)
    : challenger(std::string()),
      server_connection(new connection(new zinara::ip::tcp::socket, zinara::ip::tcp::address("172.30.2.26", SERVER_PORT), set_nickname))
{
    // Här kommer spelaren från login 
    
	eye.position = Point(2.0, 2.0, 5.0);

	world.push_back(object_ptr(new Text()));	// Nicks
	world.push_back(object_ptr(new Text()));	// Chat
	world.push_back(object_ptr(new Text()));	// Input

	world.push_back(object_ptr(new Body(Point(1, 2.2, 0), Size(2.2,1.6,2), Color(1,1,1), CUBE_BORDERED)));			// Main, output
	world.push_back(object_ptr(new Body(Point(3.2, 2, 0), Size(1.2,2,2), Color(1,1,1), CUBE_BORDERED)));			// Playerlist
	world.push_back(object_ptr(new Body(Point(1, 1.15, 0.9), Size(2.2, 0.3, 0.2), Color(1,1,1), CUBE_BORDERED)));	// input
	world.push_back(object_ptr(new Body(Point(2, 0.6, 0.9), Size(0.5, 0.4, 0.2), Color(1,1,1), CUBE_BORDERED)));	// Back-to-menu-box

	Letter functionmarker(Size(0.08, 0.06, 0), 0.02, 2.5, Color(0.3,0.3,1));

	world.push_back(object_ptr(new Text("SAY:", functionmarker, Point(0.1, 1.15, 1+MILLI), Size())));
	world.push_back(object_ptr(new Text("BACK _TO MENU", functionmarker, Point(2, 0.6, 1+MILLI), Size(0.45, 0, 0))));
	world.push_back(object_ptr(new Text("ONLINE PLAYERS:", Letter(Size(0.04, 0.06, 0), 0.02, 1.5, Color(0.3,0.3,1)), Point(3.2, 1.95, 1+MILLI), Size(1.2,2,2))));

    try
    {
        // Försök att ansluta till den angivna IPn.
        zinara::ip::tcp::connector connector;
        if(connector.connect(server_connection->get_socket(), server_connection->get_address(), zinara::timeval(5, 0)) == false)
        {
            // Timeout. Inte bra. Det räknas som ett fel
            server_connection->set_erroneous();
            SetNextActivity(new Fade(new Menu("CONNECT TIMEOUT"), world, eye), true);
        }
        
        // Gör iordning och skicka IAM med nick och version
        std::string login_msg;
        login_msg += "IAM#";
        login_msg += server_connection->get_nickname();
        login_msg += ";";
        login_msg += VERSION;
        login_msg += "\r\n";

        server_connection->put_message(login_msg);
        while(server_connection->want_write())
        {
            server_connection->get_socket().update(zinara::timeval());
            server_connection->process_io();
        }
    }
    catch(std::exception& error)
    {
        // Något oväntat hände
        server_connection->set_erroneous();
        SetNextActivity(new Fade(new Menu("COMLINK FAILED"), world, eye), true);
    }
}

ServerInterface::~ServerInterface()
{
}

void ServerInterface::Think(unsigned int elapsed_time)
{
    // Uppdatera anslutningen med servern
    server_connection->get_socket().update(zinara::timeval());
    server_connection->process_io();
    if(server_connection->good())
    {
        std::string msg;
        while(server_connection->get_message(msg))
        {
            // Ett chatmedelande, lägg det i utskriftsbufferten
            if(msg.size() > 7 && msg.substr(0, 5) == "CHAT#")
            {
                msg[msg.find(';')] = ':';
                chat += msg.substr(5, std::string::npos);
                chat += "\n";
            }
            else if(msg.size() > 9 && msg.substr(0, 7) == "ACCEPT#")
            {
                // Hantera en ACCEPT, med felhantering för tillfälligt bortfall av klient
            	std::string player(msg.substr(msg.find('#') +1, std::string::npos));
				std::string opponent_address;
				bool found_opponent = false;
				for(unsigned int i(0); i < clients.size(); ++i)
				{
					if(player == clients[i].nickname)
					{
						found_opponent = true;
						opponent_address = clients[i].ip;
					}
				}
				if(found_opponent)
				{
					if(player == server_connection->get_nickname())
					{
						chat += "SERVER: CHALLENGE ERROR, ABORTING.\n";

						std::string challange_msg;
						challange_msg += "DECLINE#";
						challange_msg += server_connection->get_nickname();
						challange_msg += "\r\n";
						server_connection->put_message(challange_msg);
					}
					else
					{
						SetNextActivity(new Fade(new Game(true, opponent_address, server_connection, player), world, eye), true);
					}
				}
				else
				{
					chat += "SERVER: CHALLENGE ERROR, ABORTING.\n";

					std::string challange_msg;
					challange_msg += "DECLINE#";
					challange_msg += server_connection->get_nickname();
					challange_msg += ";";
					challange_msg += player;
					challange_msg += "\r\n";
					server_connection->put_message(challange_msg);
				}
            }
            // Om någon nekar finns det inte så mycket att göra, det är bara att säga det
            else if(msg.size() > 10 && msg.substr(0, 8) == "DECLINE#")
            {
                chat += "SERVER: CHALLENGE WAS DECLINED\n";
            }
            // Vid en utmananing måste användaren välja om den ska godtas eller inte
            else if(msg.size() > 8 && msg.substr(0, 6) == "CHLNG#")
            {
            	std::string player(msg.substr(msg.find('#')+1, std::string::npos));
                chat += "\nSERVER: CHALLENGED BY ";
                chat += player;
                chat += "\n";

				chat += "SERVER: TO ACCEPT     -A\n";
				chat += "SERVER: TO DECLINE    -D\n";
				challenger = player;
            }
            // Listan över spelare som servern skickas, kan parsas till ett enklare format
            else if(msg.size() > 8 && msg.substr(0, 8) == "PLAYERS#")
                clients = ParseServerList(msg);
            // Skickas av servern en gång efter att IAM blivit godkännd, en mycket kortfattad nyhet
			else if(msg.size() > 7 && msg.substr(0, 5) == "NEWS#")
			{
				chat += msg.substr(msg.find('#')+1, std::string::npos);
				chat += "\n";
			}
        }
        // Updatera server listan över klienter
        std::string nicknames;
        for(unsigned int i(0); i < clients.size(); ++i)
        {
            nicknames += clients[i].nickname;
            nicknames += " ";
            nicknames += (clients[i].status == "BUSY" ? clients[i].status : "");
            nicknames += "\n";
        }
        
        // Uppdatera chat
		while(count(chat.begin(), chat.end(), '\n') > 14)
			chat = chat.substr(chat.find('\n')+1, std::string::npos);

    	Letter style(Size(0.04, 0.06, 0), 0.02, 2.5, Color(0.3,0.3,1));
        
        // Updatera texter
    	world[0] = object_ptr(new Text(nicknames, style, Point(3.25, 1.8, 1+MILLI), Size(1.1,1.9,0)));
    	world[1] = object_ptr(new Text(chat, style, Point(1, 2.2, 1+MILLI), Size(1.9, 1.3 ,0), Color(0.3,0.3,0.3), Rotation(), false));
    	world[2] = object_ptr(new Text(input, style, Point(1.21, 1.15, 1+MILLI), Size(1.6, 0.13,0), Color(0.3,0.3,0.3), Rotation(), false));
    }
    else
    {
        // Kommer vi hit har något av någon anledning gått fel. Är det ett fel som inträffat
        // så kommer is_erroneous() att returnera sant vilket betyder att det redan finns en
        // activity som inte får ersättas.
        if(server_connection->is_erroneous() == false)
		    SetNextActivity(new Fade(new Menu, world, eye), true);
    }
}

void ServerInterface::OnKeyDown(const ::SDL_KeyboardEvent& key)
{
	switch(key.keysym.sym)
	{
		case SDLK_DOWN:
		    // Stäng server anslutningen och återvänd till menyn
			SetNextActivity(new Fade(new Menu, world, eye), true);
		break;
		case SDLK_ESCAPE:
		    // Stäng server anslutningen och återvänd till menyn
			SetNextActivity(new Fade(new Menu, world, eye), true);
		break;
		case SDLK_RETURN:
		{
		    // Hantera en challange
		    if(input.size() > 3 && input[0] == '-')
		    {
		        if(input.substr(0, 3) == "-C ")
		        {
		            std::string player(input.substr(3, std::string::npos));

		            bool found_opponent = false;
                    for(unsigned int i(0); i < clients.size(); ++i)
                    {
                        if(clients[i].nickname == player)
						    found_opponent = true;
				    }
		            if(found_opponent)
		            {
		                if(player == server_connection->get_nickname())
		                {
                            chat += "SERVER: THAT WOULD BE BORING.\n";
		                }
		                else
		                {
		                    // Anyone but yourself
							std::string challange_msg;
							challange_msg += "CHLNG#";
							challange_msg += player;
							challange_msg += "\r\n";
							server_connection->put_message(challange_msg);

                            chat += "SERVER: CHALLENGE SENT.\n";
		                }
		            }
		            else
		            {
		                chat += "SERVER: CANT FIND OPPONENT.\n";
		            }
		        }
		    }
		    // Acceptera
			else if(input.substr(0, 2) == "-A")
			{
				if(challenger != "")
				{
					bool found_opponent = false;
					std::string opponent_address;
					for(unsigned int i(0); i < clients.size(); ++i)
					{
						if(challenger == clients[i].nickname)
						{
							found_opponent = true;
							opponent_address = clients[i].ip;
						}
					}
					if(found_opponent)
					{
						if(challenger == server_connection->get_nickname())
						{
							chat += "SERVER: CHALLENGE ERROR, ABORTING.\n";

							std::string decline_msg;
							decline_msg += "DECLINE#";
							decline_msg += challenger;
							decline_msg += "\r\n";
							server_connection->put_message(decline_msg);

							challenger = std::string();
						}
						else
						{
							std::string accept_msg;
							accept_msg += "ACCEPT#";
							accept_msg += challenger;
							accept_msg += "\r\n";
							server_connection->put_message(accept_msg);

							SetNextActivity(new Fade(new Game(false, opponent_address, server_connection), world, eye), true);
						}
					}
					else
					{
						chat += "SERVER: CHALLENGE ERROR, ABORTING.\n";

						std::string decline_msg;
						decline_msg += "DECLINE#";
						decline_msg += challenger;
						decline_msg += "\r\n";
						server_connection->put_message(decline_msg);

						challenger = std::string();
					}
				}
				else
				{
					chat += "SERVER: YOU HAVENT BEEN CHALLENGED.\n";
				}
			}
			// Neka
			else if(input.substr(0, 2) == "-D")
			{
				if(challenger != "")
				{
					std::string decline_msg;
					decline_msg += "DECLINE#";
					decline_msg += challenger;
					decline_msg += "\r\n";
					server_connection->put_message(decline_msg);

					chat += "SERVER: DECLINING CHALLENGE!\n";

					challenger = std::string();
				}
				else
				{
					chat += "SERVER: YOU HAVENT CHALLENGED!\n";
				}
			}
		    else
		    {
    		    std::string chat_msg;
    		    chat_msg += "CHAT#";
    		    chat_msg += server_connection->get_nickname();
    		    chat_msg += ";";
    		    chat_msg += input;
    		    chat_msg += "\r\n";
    		    server_connection->put_message(chat_msg);
            }

			input = "";
	    }
		break;

		default:
			break;
	}
    // Hämta input från tangentbordet och lagra i input
	HandleInput(key, input);
    
    // Trunkera meddelanden större än 20 chars
	if(input.size() >= 20)
		input = input.substr(0, 20);
}
