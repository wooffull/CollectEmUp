#pragma once

#include <glew.h>
#include <glfw3.h>
#include <time.h>
#include <string>
#include "Event.h"
#include "GameEvent.h"
#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "EventDispatcher.h"
#include "GameException.h"
#include "Callback.h"
#include "IScreen.h"
#include "Random.h"

class Game :
	public EventDispatcher
{
public:
	static const int& DEFAULT_WIDTH;
	static const int& DEFAULT_HEIGHT;

	Game( const char* name, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT );
	~Game();

	void start();
	void stop();

	GLFWwindow* getWindow();

	IScreen* getScreen();
	void setScreen( IScreen* value );

	Color getClearColor();
	void setClearColor( Color value );

	void onClose( Event e );
	void onMouseButtonChange( int button, int action, int mods );
	void onKeyChange( int key, int action );

private:
	GLFWwindow* _windowPtr;
	IScreen* _curScreen;
	Color _clearColor;
	glm::vec2 _mousePos;
	int _width;
	int _height;

	glm::vec2 getCursorPos();
	void updateMouseMovement();
};

