#include "Environment.h"
#include "ExamplePrefabClass.h"

const glm::vec3& Environment::GRAVITY = glm::vec3( 0, -1.0f, 0 );
const float& Environment::DRAG = -0.10f;
const float& Environment::FRICTION = 0.95f;
const float& Environment::DEFLECT_PERCENTAGE = 0.5f;

Environment::Environment()
{
	// Add event listener to self for when the environment has been added
	Callback cAdded = std::bind( &Environment::onAdded, this, std::placeholders::_1 );
	addEventListener( Event::ADDED, cAdded );

	// Add event listener to self for when the environment has been removed
	Callback cRemoved = std::bind( &Environment::onRemoved, this, std::placeholders::_1 );
	addEventListener( Event::REMOVED, cRemoved );

	// Enable z-buffer depth testing
	glEnable( GL_DEPTH_TEST );

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	_worldMatrix = glm::one<glm::mat4>();
}

Environment::~Environment()
{
}

void Environment::update( float dt )
{
	applyGravity();
	applyDrag();

	GameObject::update( dt );
	
	setShaderMatrix( _programIndex, "worldMatrix", _worldMatrix );
}

void Environment::applyGravity()
{
	auto begin = _children->begin();
	auto end = _children->end();
	for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
	{
		GameObject* curChild = *it;
		curChild->addForce( GRAVITY );
	}
}

void Environment::applyDrag()
{
	auto begin = _children->begin();
	auto end = _children->end();
	for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
	{
		GameObject* curChild = *it;
		glm::vec3 childVelocity = curChild->getVelocity();
		curChild->addForce( childVelocity * DRAG );
	}
}

void Environment::onAdded( Event e )
{
	//Add level objects here.
	//IMPORTANT: Model files are stored in the Models subfolder, and so their filenames must be prefixed with "Models/". Failure to do so will result in a memory error at runtime.
	ExamplePrefabClass* rotatingCube = new ExamplePrefabClass( "Models/cube.obj" );
	addChild( rotatingCube );
}

void Environment::onRemoved( Event e )
{
}

void Environment::onMouseDown( MouseEvent e )
{
	glm::vec3 jump( 0, 0.5f, 0 );

	auto begin = _children->begin();
	auto end = _children->end();
	for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
	{
		GameObject* curChild = *it;
		curChild->addImpulse( jump );
	}
}