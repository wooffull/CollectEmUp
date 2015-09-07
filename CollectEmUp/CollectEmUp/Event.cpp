#include "Event.h"

const std::string& Event::EVENT = "event";

Event::Event( const std::string& name = EVENT )
{
	_name = name;
}

Event::~Event()
{
}

std::string Event::getName()
{
	return _name;
}