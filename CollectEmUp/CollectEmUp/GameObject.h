#pragma once

#include "EventDispatcher.h"

class GameObject :
	public EventDispatcher
{
public:
	GameObject();
	virtual ~GameObject();
};

