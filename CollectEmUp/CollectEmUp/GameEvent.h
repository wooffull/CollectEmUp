#pragma once

#include "Event.h"

class GameEvent :
	public Event
{
public:
	static const std::string& START;
	static const std::string& STOP;
	static const std::string& CLOSE;

	GameEvent( const std::string& name );
	virtual ~GameEvent();
};

