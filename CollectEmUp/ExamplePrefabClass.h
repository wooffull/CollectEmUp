#pragma once

#include "GameObject.h"
#include "ModelImporter.h"
#include "ModelImportData.h"

class ExamplePrefabClass :
	public GameObject
{
private:
	glm::vec3 _basePosition;
	float _elapsedTime, _posDeviation, _bobRate;

public:
	ExamplePrefabClass( char* modelFilePath, char* textureFilePath );
	~ExamplePrefabClass();

	virtual void update( float dt );
	virtual void draw( float dt );
};