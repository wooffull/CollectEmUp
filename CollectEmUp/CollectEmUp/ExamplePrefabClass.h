#pragma once

#include "gameobject.h"

class ExamplePrefabClass :
	public GameObject
{
private:
	glm::vec3 basePosition;
	float elapsedTime, posDeviation, bobRate;

public:
	ExamplePrefabClass(const char* modelFilename);
	~ExamplePrefabClass(void);

	virtual void update( float dt );
	virtual void draw( float dt );
};