#pragma once

#include "IScreen.h"
#include "Environment.h"
#include "GameException.h"
#include "ShaderImporter.h"

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

private:
	Environment* _environment;
	glm::vec2 _mousePos;
	glm::vec2 _mouseDisplacement;
	bool _mouseIsDown;

	void updateMouse( MouseEvent e );
};

