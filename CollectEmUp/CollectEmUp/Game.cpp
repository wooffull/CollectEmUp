#include "Game.h"

const int& Game::DEFAULT_WIDTH = 800;
const int& Game::DEFAULT_HEIGHT = 600;

Game::Game( const char* name, int width, int height ) :
	EventDispatcher()
{
	// Initialize the library
	if( !glfwInit() )
	{
		throw GameException::GlfwInitFail;
	}

	// Create a windowed mode window and its OpenGL context 
	windowPtr = glfwCreateWindow(
		width,
		height,
		name,
		NULL,
		NULL
	);
	if( !windowPtr )
	{
		glfwTerminate();
		throw GameException::GlfwCreateWindowFail;
	}

	glfwMakeContextCurrent( windowPtr );

	glewExperimental = GL_TRUE;

	if ( glewInit() != GLEW_OK )
	{
		throw GameException::GlewInitFail;
	}
	
	Callback c = std::bind( &Game::onClose, this, std::placeholders::_1 );
	this->addEventListener( GameEvent::CLOSE, c );
}


Game::~Game()
{
	glfwTerminate();
}

void Game::start()
{
	GameEvent eStart( GameEvent::START );
	dispatchEvent( eStart );

	while( !glfwWindowShouldClose( windowPtr ) )
	{
		glClear( GL_COLOR_BUFFER_BIT );

		glfwSwapBuffers( windowPtr );
		glfwPollEvents();
	}
	
	GameEvent eClose( GameEvent::CLOSE );
	dispatchEvent( eClose );
}

void Game::stop()
{
	glfwSetWindowShouldClose( windowPtr, GL_TRUE );
	
	GameEvent e( GameEvent::STOP );
	dispatchEvent( e );
}

void Game::onClose( Event e )
{
	glfwDestroyWindow( windowPtr );
}