#include "ExamplePrefabClass.h"

ExamplePrefabClass::ExamplePrefabClass( char* modelFilePath, char* textureFilePath ) :
	GameObject()
{
	// Perhaps we should put this in GameObject? Having the ability to import and load
	// a model just from its filename could be handy in the future.
	ModelImporter modelImporter;
	setModel( modelImporter.loadModel( modelFilePath, textureFilePath ) );
}

ExamplePrefabClass::~ExamplePrefabClass()
{
}

void ExamplePrefabClass::update( float dt )
{
    GameObject::update( dt );
}

void ExamplePrefabClass::draw( float dt )
{
	GameObject::draw( dt );
}