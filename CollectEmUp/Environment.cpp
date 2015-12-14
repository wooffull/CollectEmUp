#include "Environment.h"

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

    _octTree = new OctTree
    (
        glm::vec3(),
        glm::vec3
        (
            50,
            50,
            50
        )
    );

	_worldMatrix = glm::one<glm::mat4>();

    addChild( &_camera );
}

Environment::~Environment()
{
    delete _octTree;
	delete _lvl1;
}

void Environment::update( float dt )
{
	//applyGravity();
	//applyDrag();
	
	glm::mat4 viewMatrix =
		glm::perspective( glm::pi<float>() * 0.4f, 1.0f, 0.1f, 1000.0f ) *
		glm::lookAt( _camera.getPosition(), _camera.getLookAt(), _camera.getUp() );

	setShaderMatrix( _programIndex, "viewMatrix", viewMatrix );

	// Setting camera to proper position/ rotation for following player
	_camera.setPosition( _player->getPosition() - _player->forward * 4.5f + glm::vec3( 0, 2.25f, 0 ) );
	if( _turnAmount != 0 )
	{
		// Player is turning, turn cam to match
		_camera.turn( _turnAmount, 0 );
        _turnAmount = 0;
	}

	GameObject::update( dt );

    // Check for collisions
	_octTree->checkCollisions();
	/*
    auto begin = _children->begin();
    auto end = _children->end();

    for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
    {
        GameObject* child1 = *it;

        for( std::vector<GameObject*>::iterator it2 = it + 1; it2 != end; ++it2 )
        {
            GameObject* child2 = *it2;

            if( child1 != &_camera && child2 != &_camera && child1->collidesWith( child2 ) )
            {
                //std::cout << "COLLISION -- " << Random::getNext() <<  std::endl;
            }
        }
    }*/
}

void Environment::draw( float dt )
{
    GameObject::draw( dt );

    _octTree->draw();
}

void Environment::addChild( GameObject* child )
{
	std::cout << child << std::endl;
    GameObject::addChild( child );

    if( child != &_camera )
    {
        _octTree->add( child );
    }
}

void Environment::turnCamera( float dx, float dy )
{
	_camera.turn( dx, dy );
}

void Environment::moveCamera( float dx, float dy, float dz )
{
	// Deprecated code -- do not use
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
    delta.x *= 2.f;	//Turn speed
    delta.z *= 3.f;	//Movement speed
	//changing delta.y has no effect. Modify jump height in KeyboardMovableGO.cpp
    _player->setInput( delta );
	_turnAmount = -1 * delta.x;
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

	//ExamplePrefabClass* rotatingCube = new ExamplePrefabClass( "Models/cube.obj", "Models/Textures/cube-texture.png" );
 //   rotatingCube->update( 0 );
	//addChild( rotatingCube );

	//BlockPlatform* ground = new BlockPlatform( vec3( 0, -1, 0 ), vec3( 10, 1, 10 ) );
 //   ground->update( 0 );
	//addChild( ground );

	_lvl1 = new Level1();
	std::vector<GameObject*> level1Objects = _lvl1->getLevelObjects();
	for (size_t i = 0; i < level1Objects.size(); ++i)
	{
		std::cout << "adding child" << std::endl;
		level1Objects[i]->update( 0 );
		addChild(level1Objects[i]);
	}

	_player = new KeyboardMovableGO( "Models/cube.obj", "Models/Textures/cube-texture.png" );
    _player->setPosition( glm::vec3( 0, 0, 1 ) );
    _player->update( 0 );
	addChild( _player );

    // Make camera point at player!
    glm::vec3 displacement = _player->getPosition() - _camera.getPosition();
    float displacementLength = glm::sqrt( displacement.x * displacement.x + displacement.y * displacement.y + displacement.z * displacement.z );

    // Camera's forward length = 1
    float angle = glm::acos( glm::dot( displacement, _camera.getForward() ) / ( displacementLength * 1 ) );
    turnCamera( angle, -15 * glm::pi<float>() / 180.0f );

    _camera.update( 0 );
}

void Environment::onRemoved( Event e )
{
}