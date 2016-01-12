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

/**
 * @brief Program entry point
 * 
 * Server specific detail follows.
 * 
 * Tejtpuck Client-Server communication protocol
 * 
 * All messages  are ended  with two bytes;  `\r\n'.  Both server and
 * clients  will use these two bytes  to calculate the lenght  of the
 * individual messages. Think IRC.
 * 
 * All clients must send an IAM message before sending anything else.
 * The format looks like this:
 * 
 * `IAM#nick;version\r\n'
 * 
 * Where <b>nick</b> is the nickname chosen by the user of the client
 * . Nick mustn't  contain  anything  but  alfabetic  characters  and
 * digits, no special characters of any kind.  Version  is the client
 * version, a decimal number.
 * 
 * The server will respond to the IAM nick,  by giving the client the
 * server news if everything is okay, or by informing the client that
 * some problem occured.
 * 
 * `NEWS#Lots and lots of plain text (the news).\r\n'
 * 
 * `PROBLEM#Message\r\n'
 * 
 * Where the message describes the problem.
 * 
 * There is no `QUIT' message. Just close the connection.
 * 
 * When a  client connects to   the server  it will get the  server's
 * client list shortly after sending the `IAM' message. That message
 * looks like this:
 * 
 * `PLAYERS#nick_1;status_1;ip_1#[...]#nick_n;status_n;ip_n\r\n'
 * 
 * There's no way to request the server list, the server will instead
 * update connected clients when it becomes necessary.
 * 
 * Now,  there are  several ways  to handle games.  You may challange
 * peoples,  accept,  or decline other challanges.  The messages that
 * deals with this are fairly stright forward.
 * 
 * `CHLNG#nick\r\n'
 * 
 * The message stated obove sends a challange (or  game inivitaion if
 * you'd like) to the client with the specified nick.
 * 
 * `ACCEPT#nick\r\n'
 * 
 * Accept and  decline are a  bit tricky though,  when sending it the
 * nick  should specify the client that you  want to tell that you're
 * accepting the challange.  The server will then modify your message
 * inserting your nick instead to indicate  to the client to whom you
 * are accepting that the right person is accepting it.
 * 
 * DECLINE  works in a simular manner;  send it to  the client you're
 * turning down  and the server  will modify the  message to tell the 
 * client you're turning down  that you're  the one who's turning he/
 * she/it down.
 * 
 * `DECLINE#nick\r\n'
 * 
 * `GAMEOVER#winnernick;losernick\r\n'
 * 
 * GAMEOVER  is used to indicate that...  A game has ended, the first
 * nick  listed  is the winner,  the second is the loser.  The server
 * will also broadcast a  CHAT message telling  everybody  which nick
 * is the glorious winner and which is the pittyful loser.
 * 
 * It's possible for all players to chat with each other too,  that's
 * what the CHAT message is for; it's extremly straight forward:
 * 
 * `CHAT#nick;Message, lot's of plain text here\r\n'
 * 
 * This message will be echoed back to all approved connections.  And
 * that's all there's to it.
 */
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << "\nUsage: tejtserv <port> <password>\n" << std::endl;
        return EXIT_FAILURE;
    }
    try
    {
        // Only windows compat.
        zinara::system_initializer sysinit;
        
        // Turn the process into a daemon (does nothing in windows)
        zinara::daemonize(argc, argv);
        
        std::cout << "Tejtserv version 1.0, Copyright (C) 2007 Erik Edlund" << std::endl;
        std::cout << "Tejtserv comes with ABSOLUTELY NO WARRANTY." << std::endl;
        std::cout << "This is free software, and you are welcome to redistribute it.\n" << std::endl;
        
        service_handler tejtpuck_service(std::atoi(argv[1]), argv[2]);
        tejtpuck_service.run();
    }
    catch(std::exception& error)
    {
        std::cout << "\nA fatal error was encountered: " << error.what() << "\n" << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
