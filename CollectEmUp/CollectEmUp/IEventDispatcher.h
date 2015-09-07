#pragma once

#include <string>
#include "Event.h"
#include "DispatcherCallbackMap.h"
#include "Callback.h"

class IEventDispatcher
{
public:
	virtual ~IEventDispatcher() {}

	virtual void addEventListener( std::string type, Callback listener ) = 0;
	virtual void removeEventListener( std::string type, Callback listener ) = 0;
	virtual void dispatchEvent( Event e ) = 0;

protected:
	DispatcherCallbackMap _callbackMap;
};