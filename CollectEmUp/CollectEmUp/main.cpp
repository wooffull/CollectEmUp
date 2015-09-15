#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Game.h"
#include "Event.h"
#include "GameScreen.h"

Game* _game;

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

void onMouseButtonChange( GLFWwindow* windowPtr, int button, int action, int mods )
{
	_game->onMouseButtonChange( button, action, mods );
}

void onMouseMove( GLFWwindow* windowPtr, double x, double y )
{
	_game->onMouseMove( x, y );
}

int main( int argc, char* argv[] )
{
	_game = new Game( "CollectEmUp" );
	GameScreen* gameScreen = new GameScreen();
	_game->setScreen( gameScreen );
	_game->addEventListener( GameEvent::START, onGameStart );
	_game->addEventListener( GameEvent::STOP, onGameStop );
	_game->addEventListener( GameEvent::CLOSE, onGameClose );

	// Notify when a mouse button is pressed/ released or when the cursor moves
	glfwSetMouseButtonCallback( _game->getWindow(), onMouseButtonChange );
	glfwSetCursorPosCallback( _game->getWindow(), onMouseMove );

	_game->start();

	delete gameScreen;
	delete _game;
}