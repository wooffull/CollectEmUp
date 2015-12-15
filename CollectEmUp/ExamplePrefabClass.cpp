#include "ExamplePrefabClass.h"

ExamplePrefabClass::ExamplePrefabClass( char* modelFilePath, char* textureFilePath ) :
	GameObject()
{
	// Perhaps we should put this in GameObject? Having the ability to import and load
	// a model just from its filename could be handy in the future.
	ModelImporter modelImporter;
	setModel( modelImporter.loadModel( modelFilePath, textureFilePath ) );

	// Write prefab init code here.
	setScale( glm::vec3( 5.f, 3.f, 0.1f ) );
	setRotationAxis( glm::vec3( 0, 1, 0 ) );
	setFixed( true );
	setIsVisible( false );
}

ExamplePrefabClass::~ExamplePrefabClass()
{
	GameObject::~GameObject();
}

void ExamplePrefabClass::update( float dt )
{
	vec3 parentPos = _parent->getPosition();
	setPosition( vec3( parentPos.x, _parent->getPosition().y + 2.75f, parentPos.z ) );
//	setRotation( _parent->getRotation() );
}

void ExamplePrefabClass::draw( float dt )
{
	// Write prefab draw code here, if applicable.


	// Include this function call at the end of each draw.
	GameObject::draw( dt );
}