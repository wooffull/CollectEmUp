#pragma once

#include "GameObject.h"
#include "ModelImporter.h"
#include "ModelImportData.h"

class ExamplePrefabClass :
	public GameObject
{
public:
	ExamplePrefabClass( char* modelFilePath, char* textureFilePath );
	virtual ~ExamplePrefabClass();

	virtual void update( float dt );
	virtual void draw( float dt );
};