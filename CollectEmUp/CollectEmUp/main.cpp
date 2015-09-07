/* CollectEmUp Game © 2015
Created for:
IGME - 309 Data Structures and Algorithms for Games and Simulation II

Team Members:
Norman Greenberg: Team Manager/Design
Cathy Altenburger: Designer/Artist
L.A. Stapleford: Designer/Artist
Andrew Litfin: Designer
Andrew Knowland: Designer

Michael Lynch: Engine Lead
Matthew Fasman: Engine Developer
Ryan Mignini : Engine Developer
Hector Piñeiro: Engine Developer

This main.cpp is just to get OpenGL set up as it is can have the most
difficulties. For the future we should begin to separate out different
elements into their own methods and classes.

I have selected Visual Studos 2013 as it is what all of the lab machines have
on them. I apologize if this causes an inconvenience initially.
*/

#include <iostream>
#include "Game.h"
#include "Event.h"

void onGameStart( Event e )
{
	std::cout << "Game started" << std::endl;
}

void onGameStop( Event e )
{
	std::cout << "Game stopped" << std::endl;
}

void onGameClose( Event e )
{
	std::cout << "Game closed" << std::endl;
}

int main( int argc, char* argv[] )
{
	Game game = Game( "CollectEmUp" );
	game.addEventListener( GameEvent::START, onGameStart );
	game.addEventListener( GameEvent::STOP, onGameStop );
	game.addEventListener( GameEvent::CLOSE, onGameClose );

	game.start();
}