#pragma once

#include "gameobject.h"

class ExamplePrefabClass :
	public GameObject
{
public:
	ExamplePrefabClass(const char* modelFilename);
	~ExamplePrefabClass(void);

	virtual void update( float dt );
	virtual void draw( float dt );
};

