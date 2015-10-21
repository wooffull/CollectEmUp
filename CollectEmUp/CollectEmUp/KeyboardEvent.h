#pragma once

#include "Event.h"

class KeyboardEvent :
	public Event
{
public:
	static const std::string& KEY_PRESSED;
	static const std::string& KEY_RELEASED;

	KeyboardEvent( const std::string& name, int key );
	virtual ~KeyboardEvent();

	int getKey();

private:
	int _key;
};

