#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "Event.h"
#include "Callback.h"

class DispatcherCallbackMap
{
public:
	DispatcherCallbackMap();
	~DispatcherCallbackMap();

	void add( std::string type, Callback callback );
	void remove( std::string type, Callback callback );
	CallbackVector* find( std::string type );

private:
	std::unordered_map<std::string, CallbackVector*> _callbackMap;
};

