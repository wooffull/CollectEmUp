#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Game.h"
#include "Event.h"
#include "GameScreen.h"

Game* _game;

/**
 * Callback for when the game starts running
 */
void onGameStart( Event e )
{
	std::cout << "Game started" << std::endl;
}

/**
 * Callback for when the game stops running
 */
void onGameStop( Event e )
{
	std::cout << "Game stopped" << std::endl;
}

/**
 * Callback for when the game closes
 */
void onGameClose( Event e )
{
	std::cout << "Game closed" << std::endl;
}

/**
 * Callback for when a mouse button is either clicked or released
 */
void onMouseButtonChange( GLFWwindow* windowPtr, int button, int action, int mods )
{
	_game->onMouseButtonChange( button, action, mods );
}

/**
 * Callback for when a key is either pressed or released
 */
void onKeyChange( GLFWwindow* windowPtr, int key, int scancode, int action, int mods )
{
	_game->onKeyChange( key, action );

	// Catch when to exit the game
	if( key == GLFW_KEY_Q )
	{
		glfwSetWindowShouldClose( windowPtr, GL_TRUE );
	}
}

/**
 * Main entry point for the program
 */
int main( int argc, char* argv[] )
{
	// Create a new game
	_game = new Game( "CollectEmUp" );

	// Set the current screen for the game
	GameScreen* gameScreen = new GameScreen();
	_game->setScreen( gameScreen );

	// Add event listeners for the game
	_game->addEventListener( GameEvent::START, onGameStart );
	_game->addEventListener( GameEvent::STOP, onGameStop );
	_game->addEventListener( GameEvent::CLOSE, onGameClose );

	// Set up event listeners for input methods for the game
	glfwSetMouseButtonCallback( _game->getWindow(), onMouseButtonChange );
	glfwSetKeyCallback( _game->getWindow(), onKeyChange );

	// Set clear color for the game's background
	_game->setClearColor( Color( 0.5f, 1.0f, 0.8f ) );

	// Start game loop
	_game->start();

	// Free memory for objects created on the heap
	delete gameScreen;
	delete _game;
}