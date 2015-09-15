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
	_windowPtr = glfwCreateWindow(
		width,
		height,
		name,
		NULL,
		NULL
	);
	if( !_windowPtr )
	{
		glfwTerminate();
		throw GameException::GlfwCreateWindowFail;
	}

	glfwMakeContextCurrent( _windowPtr );

	glewExperimental = GL_TRUE;

	if ( glewInit() != GLEW_OK )
	{
		throw GameException::GlewInitFail;
	}
	
	// Add event listener to self for when the game closes
	Callback c = std::bind( &Game::onClose, this, std::placeholders::_1 );
	addEventListener( GameEvent::CLOSE, c );

	_mousePos = glm::vec2( 0, 0 );

	Random::seedRandom( unsigned( time( NULL ) ) );
}

Game::~Game()
{
	glfwTerminate();
}

void Game::start()
{
	float dt;
	float prevTime = float( glfwGetTime() );
	float curTime;

	GameEvent eStart( GameEvent::START );
	dispatchEvent( eStart );

	// Game loop
	while( !glfwWindowShouldClose( _windowPtr ) )
	{
		// Calculate time difference from last loop iteration
		curTime = float( glfwGetTime() );
		dt = curTime - prevTime;

		glClear( GL_COLOR_BUFFER_BIT );

		if( _curScreen != nullptr )
		{
			_curScreen->update( dt );
			_curScreen->draw( dt );
		}

		glfwSwapBuffers( _windowPtr );
		glfwPollEvents();

		// Update time for next loop iteration
		prevTime = curTime;
	}
	
	GameEvent eClose( GameEvent::CLOSE );
	dispatchEvent( eClose );
}

void Game::stop()
{
	glfwSetWindowShouldClose( _windowPtr, GL_TRUE );
	
	GameEvent e( GameEvent::STOP );
	dispatchEvent( e );
}

GLFWwindow* Game::getWindow()
{
	return _windowPtr;
}

IScreen* Game::getScreen()
{
	return _curScreen;
}
void Game::setScreen( IScreen* value )
{
	if( _curScreen != nullptr )
	{
		delete _curScreen;
	}

	_curScreen = value;
}

Color Game::getClearColor()
{
	return _clearColor;
}
void Game::setClearColor( Color value )
{
	_clearColor.set( value );
	glClearColor
	(
		_clearColor.getRed(),
		_clearColor.getGreen(),
		_clearColor.getBlue(),
		_clearColor.getAlpha()
	);
}

void Game::onClose( Event e )
{
	glfwDestroyWindow( _windowPtr );
}

void Game::onMouseButtonChange( int button, int action, int mods )
{
	if( _curScreen != nullptr )
	{
		if( button == GLFW_MOUSE_BUTTON_LEFT )
		{
			glm::vec2 cursorPos = getCursorPos();

			if( action == GLFW_PRESS )
			{
				MouseEvent e( MouseEvent::MOUSE_DOWN, cursorPos.x, cursorPos.y );
				_curScreen->onMouseDown( e );
			}
			else
			{
				MouseEvent e( MouseEvent::MOUSE_UP, cursorPos.x, cursorPos.y );
				_curScreen->onMouseUp( e );
			}
		}
	}
}

void Game::onMouseMove( double x, double y )
{
	if( _curScreen != nullptr )
	{
		glm::vec2 cursorPos = getCursorPos();
		glm::vec2 displacement = cursorPos - _mousePos;
		MouseEvent e( MouseEvent::MOUSE_MOVE, cursorPos.x, cursorPos.y, displacement.x, displacement.y );
		_curScreen->onMouseMove( e );
		_mousePos = cursorPos;
	}
}

glm::vec2 Game::getCursorPos()
{
	double x;
	double y;
	int width;
	int height;
	glm::vec2 cursorPosition;

	glfwGetCursorPos( _windowPtr, &x, &y );
	glfwGetWindowSize( _windowPtr, &width, &height );
	cursorPosition.x = 2.0f * ( (float)x / (float)width ) - 1.0f;
	cursorPosition.y = ( 2.0f * ( (float)y / (float)height ) - 1.0f ) * -1.0f;

	return cursorPosition;
}