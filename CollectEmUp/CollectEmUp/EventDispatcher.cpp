#include "EventDispatcher.h"

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
}

void EventDispatcher::addEventListener( std::string type, Callback listener )
{
	_callbackMap.add( type, listener );
}

void EventDispatcher::removeEventListener( std::string type, Callback listener )
{
	_callbackMap.remove( type, listener );
}

void EventDispatcher::dispatchEvent( Event e )
{
	CallbackVector* foundCallbackVector = _callbackMap.find( e.getName() );

	if( foundCallbackVector != nullptr )
	{
		for( Callback callback : *foundCallbackVector )
		{
			callback( e );
		}
	}
}