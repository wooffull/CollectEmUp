#include "GameScreen.h"

GameScreen::GameScreen()
{
	ShaderImporter shaderImporter;
	_programIndex = shaderImporter.loadShaderProgram
	(
		"Shaders/vertexShader.glsl",
		"Shaders/fragmentShader.glsl"
	);

	if( !_programIndex )
	{
		throw GameException::LoadShadersFail;
	}

	glUseProgram( _programIndex );

	_environment = new Environment();
	addChild( _environment );

	_mousePos = glm::vec2( 0, 0 );
	_mouseDisplacement = glm::vec2( 0, 0 );
	_mouseIsDown = false;
}

GameScreen::~GameScreen()
{
	delete _environment;
}

void GameScreen::update( float dt )
{
	GameObject::update( dt );

	float dx = 0;
	float dy = 0;
	float dz = 0;

	if(_keysPressed[GLFW_KEY_W])
	{
		dz += dt;
	}
	if(_keysPressed[GLFW_KEY_S])
	{
		dz -= dt;
	}
	if(_keysPressed[GLFW_KEY_A])
	{
		dx -= dt;
	}
	if(_keysPressed[GLFW_KEY_D])
	{
		dx += dt;
	}
	if (_keysPressed[GLFW_KEY_SPACE])
	{
		dy += dt;
	}
	if (_keysPressed[GLFW_KEY_LEFT_SHIFT])
	{
		dy -= dt;
	}

	if( dx != 0 || dy != 0 || dz != 0 )
	{
		_environment->moveCamera( dx, dy, dz );
	}

	dx = 0;
	dy = 0;
	dz = 0;
	if (_keysPressed[GLFW_KEY_UP])
	{
		dz += dt;
	}
	if (_keysPressed[GLFW_KEY_LEFT])
	{
		dx += dt;
	}
	if (_keysPressed[GLFW_KEY_DOWN])
	{
		dz -= dt;
	}
	if (_keysPressed[GLFW_KEY_RIGHT])
	{
		dx -= dt;
	}
	if (dx != 0 || dy != 0 || dz != 0)
	{
		_environment->movePlayer(glm::vec3(dx, dy, dz));
	}
}

void GameScreen::onMouseMove( MouseEvent e )
{
	updateMouse( e );

	_environment->turnCamera( e.getDx(), e.getDy() );
}
void GameScreen::onMouseDown( MouseEvent e )
{
	_mouseIsDown = true;
	updateMouse( e );
}
void GameScreen::onMouseUp( MouseEvent e )
{
	_mouseIsDown = false;
	updateMouse( e );
}
void GameScreen::onKeyPressed( KeyboardEvent e )
{
	_keysPressed[e.getKey()] = true;
}
void GameScreen::onKeyReleased( KeyboardEvent e )
{
	_keysPressed[e.getKey()] = false;
}

void GameScreen::updateMouse( MouseEvent e )
{
	_mousePos.x = e.getX();
	_mousePos.y = e.getY();
	_mouseDisplacement.x = e.getDx();
	_mouseDisplacement.y = e.getDy();
}