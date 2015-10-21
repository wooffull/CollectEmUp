#include "KeyboardEvent.h"

const std::string& KeyboardEvent::KEY_PRESSED = "keyPressed";
const std::string& KeyboardEvent::KEY_RELEASED = "keyReleased";

KeyboardEvent::KeyboardEvent( const std::string& name, int key ) :
	Event( name )
{
	_key = key;
}

KeyboardEvent::~KeyboardEvent()
{
}

int KeyboardEvent::getKey()
{
	return _key;
}