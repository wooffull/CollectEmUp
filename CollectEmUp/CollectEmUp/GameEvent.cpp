#include "GameEvent.h"

const std::string& GameEvent::START = "start";
const std::string& GameEvent::STOP = "stop";
const std::string& GameEvent::CLOSE = "close";

GameEvent::GameEvent( const std::string& name ) :
	Event( name )
{
}

GameEvent::~GameEvent(void)
{
}
