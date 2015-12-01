#include "KeyboardMovableGO.h"
#include <iostream>


KeyboardMovableGO::KeyboardMovableGO(char* modelFilePath, char* textureFilePath)
{
	forward = glm::vec3(0, 0, 1);
	ModelImporter modelImporter;
	setModel(modelImporter.loadModel(modelFilePath, textureFilePath));
	setPosition(glm::vec3(0, 0, 0));
	setColor(0.5f, 0.3f, 0.5f);
	setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	setRotationAxis(glm::vec3(0, 1, 0));
	setFixed(true);
}


KeyboardMovableGO::~KeyboardMovableGO()
{
}

void KeyboardMovableGO::update(float dt)
{
	if (inputData.x != 0)
	{
		float deltaRot = inputData.x;
		setRotation(_rotation + deltaRot);
		forward = glm::vec3(sin(_rotation), 0, cos(_rotation));
	}

	glm::vec3 deltaPos = forward*inputData.z;
	setPosition(_position + deltaPos*movementSpeed);
	//I don't know if I need to call the parent method, but I might as well. The GO is fixed, so we shouldn't see any unwanted movement.
	GameObject::update(dt);

	inputData = glm::vec3(0, 0, 0);
}

void KeyboardMovableGO::draw(float dt)
{
	GameObject::draw(dt);
}

void KeyboardMovableGO::setInput(glm::vec3 in)
{
	inputData = in;
}