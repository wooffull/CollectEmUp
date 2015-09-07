#pragma once

#include <glew.h>
#include <glfw3.h>
#include <string>
#include "Event.h"
#include "GameEvent.h"
#include "EventDispatcher.h"
#include "GameException.h"
#include "Callback.h"

class Game :
	public EventDispatcher
{
private:	
	static const int& DEFAULT_WIDTH;
	static const int& DEFAULT_HEIGHT;

public:
	Game( const char* name, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT );
	~Game();

	void start();
	void stop();

private:
	GLFWwindow* windowPtr;

	void onClose( Event e );
};

