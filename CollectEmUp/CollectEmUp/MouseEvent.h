#pragma once

#include "Event.h"

class MouseEvent :
	public Event
{
public:
	static const std::string& MOUSE_DOWN;
	static const std::string& MOUSE_UP;
	static const std::string& MOUSE_MOVE;

	MouseEvent( const std::string& name, float x, float y, float dx = 0, float dy = 0 );
	virtual ~MouseEvent();

	float getX();
	float getY();
	float getDx();
	float getDy();

private:
	float _x;
	float _y;
	float _dx;
	float _dy;
};		  

