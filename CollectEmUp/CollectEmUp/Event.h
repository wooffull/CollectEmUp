#pragma once

#include <string>
#include <vector>

class Event
{
public:
	static const std::string& EVENT;

	Event( const std::string& name );
	virtual ~Event();

	std::string getName();

private:
	std::string _name;
};

