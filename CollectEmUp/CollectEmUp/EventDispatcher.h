#pragma once

#include <string>
#include <vector>
#include "Event.h"
#include "IEventDispatcher.h"
#include "Callback.h"

class EventDispatcher :
	public IEventDispatcher
{
public:
	EventDispatcher();
	virtual ~EventDispatcher();

	virtual void addEventListener( std::string type, Callback listener );
	virtual void removeEventListener( std::string type, Callback listener );
	virtual void dispatchEvent( Event e );
};

