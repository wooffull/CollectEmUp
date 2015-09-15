#pragma once

#include "GameObject.h"

class Triangle :
	public GameObject
{
public:
	static const float& SIZE;

	Triangle();
	virtual ~Triangle();

	void onAdded( Event e );
	void onRemoved( Event e );
};

