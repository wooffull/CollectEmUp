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
    setAcceleration( glm::vec3( 0, -5, 0 ) );
}

KeyboardMovableGO::~KeyboardMovableGO()
{
}

void KeyboardMovableGO::update( float dt )
{
    if( _inputData.x != 0 )
    {
        float deltaRot = _inputData.x;
        setRotation( _rotation + deltaRot );
        forward = glm::vec3( sin( _rotation ), 0, cos( _rotation ) );
    }
    if( _onGround && _inputData.y != 0 )
    {
        _onGround = false;
        _velocity.y = 20;
        _acceleration.y = -60;
    }

    glm::vec3 deltaPos = forward * _inputData.z;
    setPosition( _position + deltaPos * _movementSpeed );
    //I don't know if I need to call the parent method, but I might as well. The GO is fixed, so we shouldn't see any unwanted movement.
    GameObject::update( dt );

    _inputData = glm::vec3( 0, 0, 0 );

    if( !_onGround && _position.y <= 0 )
    {
        _position.y = 0;
        _velocity.y = 0;
        _acceleration.y = 0;
        _onGround = true;
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