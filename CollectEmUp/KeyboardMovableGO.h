#pragma once
#include "GameObject.h"
#pragma once
#include "GameObject.h"
#include "ModelImporter.h"
#include "ModelImportData.h"

class KeyboardMovableGO :
	public GameObject
{
public:
	KeyboardMovableGO( char* modelFilePath, char* textureFilePath );
	~KeyboardMovableGO();

	virtual void update( float dt );
	virtual void draw( float dt );
};

