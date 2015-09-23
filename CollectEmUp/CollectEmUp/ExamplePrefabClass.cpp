#define _USE_MATH_DEFINES

#include "ExamplePrefabClass.h"
#include "ModelImporter.h"
#include "ModelImportData.h"

#include <iostream>

ExamplePrefabClass::ExamplePrefabClass(const char* modelFilename) : GameObject()
{
	//Perhaps we should put this in GameObject? Having the ability to import and load a model just from its filename could be handy in the future.
	ModelImporter modelImporter;
	setModel(modelImporter.loadModel(modelFilename));

	//Write prefab init code here.
	setPosition( glm::vec3( 0, 0, -.5f ) );
	setColor( 0.5f, 0.3f, 0.5f );
	setScale( glm::vec3( 0.5f, 0.5f, 0.5f ) );
	setRotationAxis( glm::vec3( sqrt( 2 ), sqrt( 2 ), 0 ) );
	setRotationalVelocity( 0.0005f );
	setFixed( false );

	elapsedTime = 0;
	basePosition = getPosition();
	posDeviation = .1f;
	//Rate measured in radians per second
	bobRate = (float)M_PI/3;
}

void ExamplePrefabClass::update(float dt)
{
	//Write prefab update code here.
	//Useful functions can be found in GameObject.h.

	//This example object should float in one spot. Acceleration is being canceled out to prevent gravity, while its position is modified with a sine wave to produce a nice bobbing motion.
	//Rotational velocity is set in the constructor and not modified after, so it continues to rotate at a steady pace.
	setAcceleration(vec3( 0, 0, 0 ));
	elapsedTime += dt;
	setPosition(vec3(basePosition.x, basePosition.y+posDeviation*sin(bobRate*elapsedTime), basePosition.z));
	
	//Include this function call at the end of each update.
	GameObject::update(dt);
	
	std::cout << dt << " " << elapsedTime << std::endl;
	std::cout << _position.y << std::endl;
}

void ExamplePrefabClass::draw(float dt)
{
	//Write prefab draw code here, if applicable.


	//Include this function call at the end of each draw.
	GameObject::draw(dt);
}

ExamplePrefabClass::~ExamplePrefabClass(void)
{
	GameObject::~GameObject();
}