#include "KeyboardMovableGO.h"

KeyboardMovableGO::KeyboardMovableGO( char* modelFilePath, char* textureFilePath )
{
    forward = glm::vec3( 0, 0, 1 );
    ModelImporter modelImporter;
    setModel( modelImporter.loadModel( modelFilePath, textureFilePath ) );
    setPosition( glm::vec3( 0, 0, 0 ) );
    setScale( glm::vec3( 1.0f, 1.0f, 1.0f ) );
    setRotationAxis( glm::vec3( 0, 1, 0 ) );
    setFixed( false );
    setAcceleration( glm::vec3( 0, -60, 0 ) );
	setSolid( true );
}

KeyboardMovableGO::~KeyboardMovableGO()
{
}

void KeyboardMovableGO::update( float dt )
{
    if( _inputData.x != 0 )
    {
		//Turn
        float deltaRot = _inputData.x;
        setRotation( _rotation + deltaRot );
        forward = glm::vec3( sin( _rotation ), 0, cos( _rotation ) );
    }
    if( _velocity.y == 0 && _inputData.y != 0 )
    {
		//Jump
//        _onGround = false;
        _velocity.y = 20;
//        _acceleration.y = -60;
    }

	//Move
    glm::vec3 deltaPos = forward * _inputData.z;
    setPosition( _position + deltaPos * _movementSpeed );
    GameObject::update( dt );

	//Reset input data & check for ground
    _inputData = glm::vec3( 0, 0, 0 );
    /*if( !_onGround && _position.y <= 0 )
    {
        _position.y = 0;
        _velocity.y = 0;
        _acceleration.y = 0;
        _onGround = true;
    }*/

	if (_position.y <= -20)
	{
		_position = glm::vec3(0, 0, 0);
		_velocity = glm::vec3(0, 0, 0);
	}
}

void KeyboardMovableGO::draw( float dt )
{
	GameObject::draw( dt );
}

void KeyboardMovableGO::setInput( glm::vec3 in )
{
	_inputData = in;
}