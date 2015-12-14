#pragma once
#include "GameObject.h"
#include "ModelImporter.h"
#include "ModelImportData.h"

class KeyboardMovableGO :
	public GameObject
{
public:
	glm::vec3 forward;
	KeyboardMovableGO( char* modelFilePath, char* textureFilePath );
	~KeyboardMovableGO();

	virtual void update( float dt );
	virtual void draw( float dt );

	void setInput( glm::vec3 );

private:
    glm::vec3 _inputData;
    float _movementSpeed = 2;
    bool _onGround;
};

