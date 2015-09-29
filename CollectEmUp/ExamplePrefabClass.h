#pragma once

#include "GameObject.h"
#include "ModelImporter.h"
#include "ModelImportData.h"

class ExamplePrefabClass :
	public GameObject
{
private:
	glm::vec3 basePosition;
	float elapsedTime, posDeviation, bobRate;

public:
	ExamplePrefabClass( char* modelFilename );
	~ExamplePrefabClass();

	virtual void update( float dt );
	virtual void draw( float dt );
};