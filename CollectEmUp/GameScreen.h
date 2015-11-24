#pragma once

#include "IScreen.h"
#include "Environment.h"
#include "GameException.h"
#include "ShaderImporter.h"
#include <iostream>
#include <map>

class GameScreen :
	public IScreen
{
public:
	GameScreen();
	virtual ~GameScreen();

	virtual void update( float dt );

	virtual void onMouseMove( MouseEvent e );
	virtual void onMouseDown( MouseEvent e );
	virtual void onMouseUp( MouseEvent e );
	virtual void onKeyPressed( KeyboardEvent e );
	virtual void onKeyReleased( KeyboardEvent e );

private:
	Environment* _environment;
	glm::vec2 _mousePos;
	glm::vec2 _mouseDisplacement;
	std::map<int, bool> _keysPressed;
	bool _mouseIsDown;

	void updateMouse( MouseEvent e );
};

