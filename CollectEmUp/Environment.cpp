#include "Environment.h"
#include "ExamplePrefabClass.h"
#include "BlockPlatform.h"

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

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	_worldMatrix = glm::one<glm::mat4>();
	_camera.setPosition( glm::vec3( 0, 0, 1 ) );
	addChild( &_camera );
}

Environment::~Environment()
{
}

void Environment::update( float dt )
{
	//applyGravity();
	applyDrag();
	
	glm::mat4 viewMatrix =
		glm::perspective( glm::pi<float>() * 0.4f, 1.0f, 0.1f, 1000.0f ) *
		glm::lookAt( _camera.getPosition(), _camera.getLookAt(), _camera.getUp() );

	setShaderMatrix( _programIndex, "viewMatrix", viewMatrix );

	GameObject::update( dt );
}

void Environment::turnCamera( float dx, float dy )
{
	_camera.turn( dx, dy );
}
void Environment::moveCamera( float dx, float dy, float dz )
{
	glm::vec3 forward = _camera.getForward();
	glm::vec3 right = _camera.getRight();
	glm::vec3 up = _camera.getUp();
	forward *= dz;
	right *= -dx;
	up *= dy;

	glm::vec3 movement = forward + right + up;
	movement /= movement.length();
	movement *= 5.0f;

	glm::vec3 newPosition = _camera.getPosition();
	newPosition += movement;
	_camera.setPosition( newPosition );
}

void Environment::movePlayer( glm::vec3 delta )
{
	float movementSpeed = 2.0f;
	player->setPosition( player->getPosition() + delta * movementSpeed );
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
	// Add level objects here.
	// IMPORTANT: Model files are stored in the Models subfolder,
	// and so their filenames must be prefixed with "Models/".
	// Failure to do so will result in a memory error at runtime.
	ExamplePrefabClass* rotatingCube = new ExamplePrefabClass( "Models/cube.obj", "Models/Textures/cube-texture.png" );
	player = new KeyboardMovableGO( "Models/cube.obj", "Models/Textures/cube-texture.png" );
	addChild( rotatingCube );
	BlockPlatform* ground = new BlockPlatform( vec3( 0, 0, 0 ), vec3( 10, 1, 10 ) );
	addChild( ground );
	addChild( player );
}

void Environment::onRemoved( Event e )
{
}