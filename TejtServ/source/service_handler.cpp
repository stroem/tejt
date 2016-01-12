/*
** The dedicated TejtPuck server
** Copyright (C) 2007 Erik Edlund [eitlund at gmail dot com]
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

#include "service_handler.hpp"

service_handler::service_handler(int local_port, const std::string& set_passwd)
    : passwd(set_passwd),
      acceptor(address_type("0.0.0.0", local_port))
{
    // 0.0.0.0 means "any address" from a routing perspective. It's used since
    // I don't know the IP of the computer on which this server will run.
}

service_handler::~service_handler()throw()
{
}

void service_handler::run()
{
    player_map players;
    connection_list connections;
    
    while(acceptor.good())
    {
        // Add all sockets to be updated
        multiplexer.watch(acceptor, FD_READABLE);
        for(connection_list::iterator c_it(connections.begin()); c_it != connections.end(); ++c_it)
        {
            if((*c_it)->good())
            {
                // Do work if there's work to be done, we want to empty the send buffers as fast
                // as possible, so make sure that the socket will send when it's necessary.
                if((*c_it)->want_write())
                    multiplexer.watch((*c_it)->get_socket(), FD_WRITABLE);
                
                multiplexer.watch((*c_it)->get_socket(), FD_READABLE);
            }
        }
        multiplexer.update(zinara::timeval()); // This will only block if all send buffers are empty
        
        if(acceptor.readable())
        {
            // Simply accept a new connection
            accept_connection(connections);
            
            std::cout << zinara::now() << " got a new connection from " << (*connections.rbegin())->get_address().get_ip() << std::endl;
        }
        
        // Go trough each of te connections
        bool update_peer_game_list(false);
        for(connection_list::iterator c_it(connections.begin()); c_it != connections.end(); ++c_it)
        {
            // Knowing that the connection is updated, it is safe to call process_io
            std::string msg;
            (*c_it)->process_io();
            
            // If the socket is good
            if((*c_it)->good())
            {
                #ifdef DEBUG
                std::cout << zinara::now() << " processing connection." << std::endl;
                #endif
                
                (*c_it)->touch();
                while((*c_it)->get_message(msg))
                {
                    std::cout << zinara::now() << " message to be processed: " << msg << std::endl;
                    
                    // IAM#x;v.v
                    // Got an IAM message, it has to be processed carefully
                    if(msg.size() > 8 && msg.substr(0, 4) == "IAM#")
                    {
                        std::cout << zinara::now() << " Got IAM#" << std::endl;
                        
                        // Retrieve tha wanted nickname
                        std::string nickname;
                        std::string::size_type nickend(msg.find(";"));
                        if(nickend != std::string::npos && (nickname = msg.substr(4, nickend - 4)) != "")
                        {
                            std::cout << zinara::now() << " nickname OK" << std::endl;
                            
                            // And the software version
                            std::string version(msg.substr(nickend + 1, msg.size()));
                            if(compatible_versions.find(version) != std::string::npos)
                            {
                                std::cout << zinara::now() << " compatible client" << std::endl;
                                
                                // Nicknames must be unique
                                bool taken_nickname(false);
                                for(player_map::iterator p(players.begin()); p != players.end(); ++p)
                                {
                                    if(p->second.nickname == nickname)
                                        taken_nickname = true;
                                }
                                if(nickname == "server")
                                    taken_nickname = true;
                                
                                if(taken_nickname == false)
                                {
                                    (*c_it)->approve();
                                    update_peer_game_list = true;
                                    players.insert(std::make_pair((*c_it), player(nickname, (*c_it)->get_address().get_ip())));
                                    
                                    (*c_it)->put_message(get_news());
                                    
                                    std::cout << zinara::now() << " everything is fine, client got news." << std::endl;
                                }
                                else
                                {
                                    // Send a specific problem to a connection
                                    std::string answer;
                                    answer += "PROBLEM#";
                                    answer += "Your nickname is allready used, please chose another.";
                                    answer += "\r\n";
                                    
                                    (*c_it)->put_message(answer);
                                    (*c_it)->turn_down();
                                    
                                    std::cout << zinara::now() << " nickname was allready in use, client kicked." << std::endl;
                                }
                            }
                            else
                            {
                                std::string answer;
                                answer += "PROBLEM#";
                                answer += "Your client is not supported by this server, ";
                                answer += "we apologize for any inconvenience.\n";
                                answer += "Server version: " + server_version;
                                answer += "\nYour client version: " + version;
                                answer += "\r\n";
                                
                                (*c_it)->put_message(answer);
                                (*c_it)->turn_down();
                                
                                std::cout << zinara::now() << " client version was not supported." << std::endl;
                            }
                        }
                    }
                    
                    // Chat messages are sent to all approved connections
                    if(msg.size() > 7 && msg.substr(0, 5) == "CHAT#" && (*c_it)->is_approved())
                    {
                        for(connection_list::iterator c(connections.begin()); c != connections.end(); ++c)
                        {
                            msg += "\r\n";
                            if((*c)->is_approved())
                                (*c)->put_message(msg);
                        }
                        #ifdef DEBUG
                        std::cout << zinara::now() << " sending chat message to all." << std::endl;
                        #endif
                    }
                    
                    // A CHALLANGE message is a bit tricky, needs lots of handling
                    if(msg.size() > 6 && msg.substr(0, 6) == "CHLNG#" && (*c_it)->is_approved())
                    {
                        std::string origin;
                        std::string opponent(msg.substr(6, std::string::npos));
                        
                        player_map::iterator res;
                        if((res = players.find((*c_it))) != players.end())
                        {
                            // Ignore any requests made by busy client
                            if(res->second.busy == true)
                                continue;
                            
                            res->second.busy = true;
                            origin = res->second.nickname;
                        }
                        for(connection_list::iterator c(connections.begin()); c != connections.end(); ++c)
                        {
                            player_map::iterator playit;
                            if((playit = players.find((*c))) != players.end() && (*c)->is_approved())
                            {
                                if(playit->second.nickname == opponent)
                                {
                                    if(playit->second.busy == false)
                                    {
                                        // If the requested client isn't busy, we'll offer him the challange
                                        playit->second.busy = true;
                                        std::string opponent_msg;
                                        opponent_msg += "CHLNG#";
                                        opponent_msg += origin;
                                        opponent_msg += "\r\n";
                                        (*c)->put_message(opponent_msg);
                                    }
                                    else
                                    {
                                        // Autodecline if the client is busy
                                        std::string opponent_msg;
                                        opponent_msg += "DECLINE#";
                                        opponent_msg += opponent;
                                        opponent_msg += "\r\n";
                                        (*c_it)->put_message(opponent_msg);
                                        res->second.busy = false;
                                    }
                                }
                            }
                        }
                        update_peer_game_list = true;
                        
                        std::cout << zinara::now() << " " << origin << " is challening " << opponent << "." << std::endl;
                    }
                    
                    // This means that a client accepted a challange, handle it
                    if(msg.size() > 7 && msg.substr(0, 7) == "ACCEPT#" && (*c_it)->is_approved())
                    {
                        std::string origin;
                        std::string opponent(msg.substr(7, std::string::npos));
                        
                        player_map::iterator res;
                        if((res = players.find((*c_it))) != players.end())
                        {
                            origin = res->second.nickname;
                        }
                        for(connection_list::iterator c(connections.begin()); c != connections.end(); ++c)
                        {
                            player_map::iterator playit;
                            if((playit = players.find((*c))) != players.end() && (*c)->is_approved())
                            {
                                if(playit->second.nickname == opponent)
                                {
                                    std::string opponent_msg;
                                    opponent_msg += "ACCEPT#";
                                    opponent_msg += origin;
                                    opponent_msg += "\r\n";
                                    (*c)->put_message(opponent_msg);
                                }
                            }
                        }
                        update_peer_game_list = true;
                        
                        std::cout << zinara::now() << " " << origin << " accepts " << opponent << "'s challange." << std::endl;
                    }
                    
                    // This is what happens when someone is turned down
                    if(msg.size() > 8 && msg.substr(0, 8) == "DECLINE#" && (*c_it)->is_approved())
                    {
                        std::string origin;
                        std::string opponent(msg.substr(8, std::string::npos));
                        
                        player_map::iterator res;
                        if((res = players.find((*c_it))) != players.end())
                        {
                            res->second.busy = false;
                            origin = res->second.nickname;
                        }
                        for(connection_list::iterator c(connections.begin()); c != connections.end(); ++c)
                        {
                            player_map::iterator playit;
                            if((playit = players.find((*c))) != players.end() && (*c)->is_approved())
                            {
                                if(playit->second.nickname == opponent)
                                {
                                    playit->second.busy = false;
                                    std::string opponent_msg;
                                    opponent_msg += "DECLINE#";
                                    opponent_msg += origin;
                                    opponent_msg += "\r\n";
                                    (*c)->put_message(opponent_msg);
                                }
                            }
                        }
                        update_peer_game_list = true;
                        
                        std::cout << zinara::now() << " " << origin << " declines " << opponent << "'s challange." << std::endl;
                    }
                    
                    // GAMEOVER is a funny event, it's sent to the server by a host and will trigger
                    // a winning CHAT event
                    if(msg.size() > 9 && msg.substr(0, 9) == "GAMEOVER#" && (*c_it)->is_approved())
                    {
                        // Get the nicknames of the involved connections
                        std::string::size_type delim(msg.find(";"));
                        std::string winner(msg.substr(9, delim - 9));
                        std::string loser(msg.substr(delim + 1, std::string::npos));
                        
                        for(connection_list::iterator c(connections.begin()); c != connections.end(); ++c)
                        {
                            player_map::iterator playit;
                            if((playit = players.find((*c))) != players.end() && (*c)->is_approved())
                            {
                                if(playit->second.nickname == winner || playit->second.nickname == loser)
                                {
                                    playit->second.busy = false;
                                    
                                    if(c_it != c)
                                    {
                                        // Got it from host, give it to client
                                        std::string client_notif;
                                        client_notif += msg;
                                        client_notif += "\r\n";
                                        (*c)->put_message(client_notif);
                                    }
                                }
                            }
                        }
                        // Broadcast the message on the chat
                        update_peer_game_list = true;
                        std::string announcement;
                        announcement += "CHAT#SERVER;";
                        announcement += winner;
                        announcement += " PWNED ";
                        announcement += loser;
                        announcement += "\r\n";
                        for(connection_list::iterator c(connections.begin()); c != connections.end(); ++c)
                            (*c)->put_message(announcement);
                        
                        std::cout << zinara::now() << " " << winner << " spanks " << loser << "!" << std::endl;
                    }
                    
                    // Remotely halt the execution of this server.
                    if(msg.find("HALTEXEC:") != std::string::npos)
                    {
                        // But only if the correct password was supplied.
                        if(msg.find(passwd) != std::string::npos)
                        {
                            acceptor.close();
                            
                            std::cout << zinara::now() << " server halted by admin(" << (*c_it)->get_address().get_ip() << ")." << std::endl;
                        }
                        else
                        {
                            std::cout << zinara::now() << " " << (*c_it)->get_address().get_ip();
                            std::cout << ": Failed termination attempt. Wrong password." << std::endl;
                        }
                    }
                }
            }
            else
            {
                // The socket is bad, some error has occured which has forced the
                // communication link to shutdown.
                
                update_peer_game_list = true;
                
                players.erase((*c_it));
                c_it = connections.erase(c_it);
                
                std::cout << zinara::now() << " client closed connection." << std::endl;
            }
        }
        
        if(update_peer_game_list)
        {
            for(connection_list::iterator c_it(connections.begin()); c_it != connections.end(); ++c_it)
            {
                std::string client_list("");
                for(connection_list::iterator key(connections.begin()); key != connections.end(); ++key)
                {
                    if((*key)->is_approved())
                    {
                        player_map::iterator res;
                        if((res = players.find(*key)) != players.end())
                        {
                            client_list += "#";
                            client_list += res->second.nickname;
                            client_list += ";";
                            client_list += (res->second.busy ? "BUSY" : "AVAIL");
                            client_list += ";";
                            client_list += res->second.ip;
                        }
                    }
                }
                if(client_list != "")
                {
                    std::string msg("PLAYERS");
                    msg += client_list;
                    msg += "\r\n";
                    (*c_it)->put_message(msg);
                }
            }
            std::cout << zinara::now() << " sent the client list to all approved clients." << std::endl;
        }
    }
}

void service_handler::accept_connection(connection_list& connections)
{
    address_type remote_addr;
    std::auto_ptr<socket_type> socket(new socket_type);
    
    acceptor.accept(*socket, remote_addr);
    connections.push_back(connection_ptr(new connection(socket.release(), remote_addr)));
}

std::string service_handler::get_news()
{
    return "NEWS#"
    "WELCOME TO TEJTPUCK!\n"
    "TO CHALLENGE: TYPE -C NICK\n"
    "HAVE FUN AND BEHAVE."
    "\r\n";
}
