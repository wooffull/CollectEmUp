#include "DispatcherCallbackMap.h"


DispatcherCallbackMap::DispatcherCallbackMap()
{
	_callbackMap = std::unordered_map<std::string, CallbackVector*>();
}


DispatcherCallbackMap::~DispatcherCallbackMap()
{
	for( auto element : _callbackMap )
	{
		delete element.second;
	}
}

/**
 * Adds a callback to the map with the given type as the key
 */
void DispatcherCallbackMap::add( std::string type, Callback callback )
{
	CallbackVector* foundCallbackVector = find( type );
	bool exists = ( foundCallbackVector != nullptr );

	if( exists )
	{
		foundCallbackVector->push_back( callback );
	}
	else
	{
		CallbackVector* newCallbackVector = new CallbackVector();
		newCallbackVector->push_back( callback );

		std::pair<std::string, CallbackVector*> newCallbackPair( type, newCallbackVector );
		_callbackMap.insert( newCallbackPair );
	}
}

/**
 * Removes a specificied callback based on the provided type
 */
void DispatcherCallbackMap::remove( std::string type, Callback callback )
{
	CallbackVector* foundCallbackVector = find( type );
	bool exists = ( foundCallbackVector != nullptr );

	if( exists )
	{
		auto begin = foundCallbackVector->begin();
		auto end = foundCallbackVector->end();
		

		// @TODO - Remove all callbacks appropriately
		// Function pointers (or std::function) cannot be compared directly with ==
		// Need better way of comparing to check which to remove
		/*for( std::vector<Callback>::iterator it = begin; it != end; ++it )
		{
			Callback c = std::bind( &it, it, std::placeholders::_1 );

			if( &c == &callback )
			{
				foundCallbackVector->erase( it );
				break;
			}
		}*/

		// TEMP - Remove all callbacks for the given key
		foundCallbackVector->clear();
	}
}

/**
 * Finds a vector of callbacks in the map based on the given string.
 * Returns null pointer if no callbacks are associated with the given string.
 */
CallbackVector* DispatcherCallbackMap::find( std::string type )
{
	std::unordered_map<std::string, CallbackVector*>::const_iterator found = _callbackMap.find( type );

	if( found == _callbackMap.end() )
	{
		return nullptr;
	}
	else
	{
		return found->second;
	}
}