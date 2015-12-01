#include "KeyboardMovableGO.h"



KeyboardMovableGO::KeyboardMovableGO( char* modelFilePath, char* textureFilePath )
{
	ModelImporter modelImporter;
	setModel( modelImporter.loadModel( modelFilePath, textureFilePath ) );
	setPosition( glm::vec3( 0, 0, 0 ) );
	setColor( 0.5f, 0.3f, 0.5f );
	setScale( glm::vec3( 1.0f, 1.0f, 1.0f ) );
	setRotationAxis( glm::vec3( sqrt (2 ), sqrt( 2 ), 0 ) );
	setRotationalVelocity( 0.0005f );
	setFixed( true );
}


KeyboardMovableGO::~KeyboardMovableGO()
{
}

void KeyboardMovableGO::update( float dt )
{
	//I don't know if I need to call the parent method, but I might as well. The GO is fixed, so we shouldn't see any unwanted movement.
	GameObject::update( dt );
}

void KeyboardMovableGO::draw( float dt )
{
	GameObject::draw( dt );
}
