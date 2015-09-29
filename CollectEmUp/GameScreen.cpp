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
}

void GameScreen::onMouseMove( MouseEvent e )
{
	updateMouse( e );
}
void GameScreen::onMouseDown( MouseEvent e )
{
	_mouseIsDown = true;
	updateMouse( e );
	_environment->onMouseDown( e );
}
void GameScreen::onMouseUp( MouseEvent e )
{
	_mouseIsDown = false;
	updateMouse( e );
}

void GameScreen::updateMouse( MouseEvent e )
{
	_mousePos.x = e.getX();
	_mousePos.y = e.getY();
	_mouseDisplacement.x = e.getDx();
	_mouseDisplacement.y = e.getDy();
}