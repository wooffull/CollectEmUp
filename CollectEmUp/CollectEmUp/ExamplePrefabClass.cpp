#include "ExamplePrefabClass.h"

ExamplePrefabClass::ExamplePrefabClass( char* modelFilePath, char* textureFilePath ) :
	GameObject()
{
	// Perhaps we should put this in GameObject? Having the ability to import and load
	// a model just from its filename could be handy in the future.
	ModelImporter modelImporter;
	setModel( modelImporter.loadModel( modelFilePath, textureFilePath ) );

	// Write prefab init code here.
	setPosition( glm::vec3( 1.0f, 1.0f, 1.5f ) );
	setColor( 0.5f, 0.3f, 0.5f );
	setScale( glm::vec3( 1.0f, 1.0f, 1.0f ) );
	setRotationAxis( glm::vec3( sqrt( 2 ), sqrt( 2 ), 0 ) );
	setRotationalVelocity( 0.0005f );
	setFixed( false );

	_elapsedTime = 0;
	_basePosition = getPosition();
	_posDeviation = 0.1f;
	// Rate measured in radians per second
	_bobRate = glm::pi<float>() / 3.0f;
}

ExamplePrefabClass::~ExamplePrefabClass()
{
	GameObject::~GameObject();
}

void ExamplePrefabClass::update( float dt )
{
	// Write prefab update code here.
	// Useful functions can be found in GameObject.h.

	// This example object should float in one spot. Acceleration is being canceled out to prevent gravity,
	// while its position is modified with a sine wave to produce a nice bobbing motion.
	// Rotational velocity is set in the constructor and not modified after, so it continues to rotate at a steady pace.
	setAcceleration( vec3( 0, 0, 0 ) );
	_elapsedTime += dt;
	setPosition( vec3( _basePosition.x, _basePosition.y + _posDeviation * sin( _bobRate * _elapsedTime ), _basePosition.z ) );
	
	// Include this function call at the end of each update.
	GameObject::update( dt );
}

void ExamplePrefabClass::draw( float dt )
{
	// Write prefab draw code here, if applicable.


	// Include this function call at the end of each draw.
	GameObject::draw( dt );
}