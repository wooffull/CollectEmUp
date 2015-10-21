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
	_wKeyPressed = false;
	_aKeyPressed = false;
	_sKeyPressed = false;
	_dKeyPressed = false;
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

	if( _wKeyPressed )
	{
		dy += dt;
	}
	if( _sKeyPressed )
	{
		dy -= dt;
	}
	if( _aKeyPressed )
	{
		dx -= dt;
	}
	if( _dKeyPressed )
	{
		dx += dt;
	}

	if( dx != 0 || dy != 0 )
	{
		_environment->moveCamera( dx, dy );
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
	switch( e.getKey() )
	{
	case GLFW_KEY_W:
		_wKeyPressed = true;
		break;
		
	case GLFW_KEY_A:
		_aKeyPressed = true;
		break;

	case GLFW_KEY_S:
		_sKeyPressed = true;
		break;

	case GLFW_KEY_D:
		_dKeyPressed = true;
		break;
	}
}
void GameScreen::onKeyReleased( KeyboardEvent e )
{
	switch( e.getKey() )
	{
	case GLFW_KEY_W:
		_wKeyPressed = false;
		break;
		
	case GLFW_KEY_A:
		_aKeyPressed = false;
		break;

	case GLFW_KEY_S:
		_sKeyPressed = false;
		break;

	case GLFW_KEY_D:
		_dKeyPressed = false;
		break;
	}
}

void GameScreen::updateMouse( MouseEvent e )
{
	_mousePos.x = e.getX();
	_mousePos.y = e.getY();
	_mouseDisplacement.x = e.getDx();
	_mouseDisplacement.y = e.getDy();
}