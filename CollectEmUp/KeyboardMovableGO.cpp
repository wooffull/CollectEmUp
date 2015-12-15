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
        // Turn
        float deltaRot = _inputData.x;
        setRotation( _rotation + deltaRot );
        forward = glm::vec3( sin( _rotation ), 0, cos( _rotation ) );
    }

    if( _velocity.y == 0 && _inputData.y != 0 )
    {
        _velocity.y = 20;
    }

    // Move
    glm::vec3 deltaPos = forward * _inputData.z;
    setPosition( _position + deltaPos * _movementSpeed );
    GameObject::update( dt );

    // Reset input data & check for ground
    _inputData = glm::vec3( 0, 0, 0 );

    if( _position.y <= -40 )
    {
        _position = glm::vec3( 0, 2, 1 );
        _velocity = glm::vec3( 0, 0, 0 );
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

int KeyboardMovableGO::getCollectablesCount()
{
    return _collectablesCount;
}

void KeyboardMovableGO::setCollectablesCount( int collectablesCount )
{
    _collectablesCount = collectablesCount;
    if( _collectablesCount >= 3 )
    {
        auto begin = _children->begin();
        auto end = _children->end();
        for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
        {
            GameObject* curChild = *it;
            curChild->setIsVisible( true );
        }
    }
}