#include "Event.h"

const std::string& Event::ADDED = "added";
const std::string& Event::REMOVED = "removed";
const std::string& Event::NONE = "none";

Event::Event( const std::string& name )
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