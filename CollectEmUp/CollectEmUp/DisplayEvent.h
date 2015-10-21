#pragma once

#include "Event.h"

class DisplayEvent :
	public Event
{
public:
	static const std::string& ADDED;
	static const std::string& REMOVED;

	DisplayEvent( const std::string& name );
	virtual ~DisplayEvent();
};

