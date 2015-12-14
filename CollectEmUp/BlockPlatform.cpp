#include "BlockPlatform.h"

BlockPlatform::BlockPlatform( vec3 position, vec3 scale ) :
	GameObject()
{
	ModelImporter modelImporter;
	setModel( modelImporter.loadModel( "Models/cube.obj", "Models/Textures/cube-texture.png" ) );

	setPosition( position );
	setScale( scale );
	setFixed( true );
	setSolid( true );
}

BlockPlatform::~BlockPlatform()
{
}

void BlockPlatform::update( float dt )
{
	GameObject::update( dt );
}

void BlockPlatform::draw( float dt )
{
	GameObject::draw( dt );
}