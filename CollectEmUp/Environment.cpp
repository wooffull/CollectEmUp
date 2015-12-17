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

    _timeElapsed = 0;

    _skyBox = new ExamplePrefabClass( "Models/cube.obj", "Models/Textures/skybox.png" );
    _skyBox->setScale( glm::vec3( 100, 100, 100 ) );
    _skyBox->setPosition( glm::vec3( 0, 0, 0 ) );
    _skyBox->setBrightness( 1.0f );
    addChild( _skyBox );

    addChild( &_camera );
}

Environment::~Environment()
{
    delete _octTree;
	delete _lvl1;
    delete _skyBox;
    delete _winPanel;
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

    glm::vec3 playerPos = _player->getPosition();
    _skyBox->setPosition( _camera.getPosition() );
    _winPanel->setPosition( glm::vec3( playerPos.x, playerPos.y + 3.0f, playerPos.z ) );

	GameObject::update( dt );

    // Check for collisions
	_octTree->checkCollisions( _player );

    glm::vec3 obstaclePos = _obstacle->getPosition();
    obstaclePos.x = -5 + 3 * glm::sin( _timeElapsed * 2 );
    _obstacle->setPosition( obstaclePos );

    if( _player->collidesWith( _obstacle ) )
    {
        _player->setPosition( glm::vec3( 0, 2, 0 ) );
    }

    _timeElapsed += dt;
}

void Environment::draw( float dt )
{
    GameObject::draw( dt );

    //_octTree->draw();
}

void Environment::addChild( GameObject* child )
{
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
    delta.x *= 2.f;	// Turn speed
    delta.z *= 3.f;	// Movement speed
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
    _lvl1 = new Level1();
    std::vector<GameObject*> level1Objects = _lvl1->getLevelObjects();
    for( size_t i = 0; i < level1Objects.size(); ++i )
    {
        level1Objects[i]->update( 0 );
        addChild( level1Objects[i] );
    }

    _winPanel = new ExamplePrefabClass( "Models/cube.obj", "Models/Textures/winner-texture.png" );
    _winPanel->setIsVisible( false );
    _winPanel->setBrightness( 1.0f );
    _winPanel->setRotationAxis( glm::vec3( 0, 1, 0 ) );
    _winPanel->setRotationalVelocity( 0.005f );
    _winPanel->setScale( glm::vec3( 4.f, 2.5f, 0.001f ) );
    _winPanel->setRotationAxis( glm::vec3( 0, 1, 0 ) );
    _winPanel->update( 0 );
	
	_player = new KeyboardMovableGO( "Models/Player1.obj", "Models/Textures/player_texture2.jpg" );
    _player->setPosition( glm::vec3( 0, -39.9f, 0 ) );
    _player->update( 0 );
    _player->addChild( _winPanel );
    addChild( _player );

    _camera.setPosition( _player->getPosition() - glm::vec3( 0, 0, 1 ) );

    _obstacle = new ExamplePrefabClass( "Models/obstacle.obj", "Models/Textures/obstacle_texture.png" );
    _obstacle->setPosition( glm::vec3( -5, 8.5f, 15.5f ) );
    _obstacle->update( 0 );
    addChild( _obstacle );

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