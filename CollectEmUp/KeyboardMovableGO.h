#pragma once
#include "GameObject.h"
#pragma once
#include "GameObject.h"
#include "ModelImporter.h"
#include "ModelImportData.h"

class KeyboardMovableGO :
	public GameObject
{
private:
	glm::vec3 inputData;
	float movementSpeed = 2;
	bool onGround;

public:
	glm::vec3 forward;
	KeyboardMovableGO( char* modelFilePath, char* textureFilePath );
	~KeyboardMovableGO();

	virtual void update( float dt );
	virtual void draw( float dt );

	void setInput( glm::vec3 );
};

