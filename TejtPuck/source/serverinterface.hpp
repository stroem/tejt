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

#ifndef SERVERMENU__HPP
#define SERVERMENU__HPP

#include "text.hpp"
#include "body.hpp"
#include "fade.hpp"
#include "menu.hpp"
#include "game.hpp"
#include "client.hpp"
#include "connection.hpp"
#include "activityhandler.hpp"

/**
 * Detta är interfacet mot servern, dvs den har hand om den grafiska representationen av
 * samt kommunikationen med servern. När man pratar med servern är det extremt viktigt
 * att ha ett nickname och en klient version, utan dessa godkänner inte servern anslutningen.
 * nickname sätts i konstruktorn och kommer från någon form av input (login.{cpp,hpp}).
 * 
 * OBSERVERA ATT SERVERNS IP ÄR SATT STATISKT I KONSTRUKTORN OCH MÅSTE ÄNDRAS MANUELLT.
 */
class ServerInterface
	: public ActivityHandler
{
    public:
        explicit ServerInterface(const std::string& set_nickname);
        explicit ServerInterface(connection_ptr set_server_connection);
        virtual ~ServerInterface();

		virtual void Think(unsigned int elapsed_time);
        virtual void OnKeyDown(const ::SDL_KeyboardEvent& key);

    protected:
        std::string chat;
        std::string input;
        std::string challenger;

        ClientVector clients;
        connection_ptr server_connection;
};

#endif	// SERVERMENU__HPP
