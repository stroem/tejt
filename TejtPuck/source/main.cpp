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

/*		VEM SOM GJORT VAD:
 *
 * De filer, i vilka en övervägande del av koden är skriven av samma person är:
 *
 * Per:
 * glfont.cpp + hpp
 * fade.cpp + hpp
 * directip.cpp + hpp
 * menu.cpp + hpp
 * body.hpp
 * color.hpp
 * letter.hpp
 * object.hpp
 * point.hpp
 * rotation.hpp
 * size.hpp
 * speed.hpp
 * text.hpp
 * view.hpp
 *
 * Erik:
 * Hela server, tejtserv
 * handleinput.cpp + hpp
 * connection.cpp + hpp
 * client.cpp + hpp
 * stringutility.cpp + hpp
 * eventhandler.cpp + hpp
 * gameevents.hpp
 *
 * Jonte har tyvär inte mycket mer än 2 ifsatser och en del av SetCanvas-funktionen kvar i projektet.
 * Dock är det Jonte som stått för hela konceptet, grunden som vi arbetat från. Hur meny, värld och
 * spelet i helhet är utformat, står Jonte för. Största delen av de praktiska idéerna kommer från Jonte,
 * men vi har arbetat om och designat om dessa så pass mycket att det inte finns mycket av koden kvar.
 * Jonte har även skrivit funktioner för att bl.a rendera texturer, som aldrig implementerades p.g.a.
 * bristfälligt sammarbete och kommunikation.
 *
 * Eventhandler- och applicaiton-designen kommer från Erik. Han har bestämt syntaxt-relaterade standarder
 * som jag, Per, försökt följa. Dock är det svårt att fullfölja sådant. Mycket design, i form av arv och
 * objektorientering i allmänhet, står erik för.
 *
 * Per har kommit med activityhandler-designen, och stått för all kollision och alla grafikrelaterade
 * uträkningar. Per har även stått för text och text-design.
 *
 * Vi tänker inte säga exakt vilka rader som är skrivna av vilka, i de filer ej listade ovan, då det ofta
 * skulle vara frågan om en situatin där ingen kan tillägnas äran för att skriva något som den andre sagt
 * åt en att göra, eller design som man kommit överens om. Det finns få rader som ej blivit diskuterade, vi
 * har hela tiden bollat idéer om design och semantik, men även funktionalitet.
 *
 */

#include "tejtpuck.hpp"
#include "application.hpp"
#include "eventhandler.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        zinara::system_initializer systeminit;
        
        Tejtpuck GameHandler;
        SDL_Application MyApp(GameHandler, 1024, 768, 32);
        MyApp.Run();
    }
    catch(std::exception& error)
    {
        std::cout << "Tejtpuck encountered an error which it couldn't recover from." << std::endl;
        std::cout << "Error message; " << error.what() << std::endl;
    }
}
