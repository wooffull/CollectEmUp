#include "MouseEvent.h"

const std::string& MouseEvent::MOUSE_DOWN = "mouseDown";
const std::string& MouseEvent::MOUSE_UP = "mouseUp";
const std::string& MouseEvent::MOUSE_MOVE = "mouseMove";

MouseEvent::MouseEvent( const std::string& name, float x, float y, float dx, float dy ) :
	Event( name )
{
	_x = x;
	_y = y;
	_dx = dx;
	_dy = dy;
}

MouseEvent::~MouseEvent()
{
}

float MouseEvent::getX()
{
	return _x;
}

float MouseEvent::getY()
{
	return _y;
}

float MouseEvent::getDx()
{
	return _dx;
}

float MouseEvent::getDy()
{
	return _dy;
}