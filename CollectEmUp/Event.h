#pragma once

#include <string>
#include <vector>

class Event
{
public:
	static const std::string& ADDED;
	static const std::string& REMOVED;

	Event( const std::string& name = Event::NONE );
	virtual ~Event();

	std::string getName();

private:
	static const std::string& NONE;

	std::string _name;
};

