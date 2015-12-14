#include "GameObject.h"

GameObject::GameObject() :
    EventDispatcher()
{
    _parent = nullptr;
    _children = new std::vector<GameObject*>();
    _position = glm::vec3( 0, 0, 0 );
    _velocity = glm::vec3( 0, 0, 0 );
    _acceleration = glm::vec3( 0, 0, 0 );
    _scale = glm::vec3( 1, 1, 1 );
    _rotationAxis = glm::vec3( 0, 0, 1 );
    _forward = glm::vec3( 0, 0, 1 );
    _rotation = 0;
    _rotationalVelocity = 0;
    _rotationalAcceleration = 0;
    _mass = 1.0f;
    _fixed = false;
    _programIndex = -1;
    _model = nullptr;
	_isSolid = false;
    _boundingBox = new BoundingBox();
	//_boundingBox->setParentGO(this);
}

GameObject::~GameObject()
{
    // TDODO Notify all children that they were removed
    /*auto begin = _children->begin();
    auto end = _children->end();
    for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
    {
    // Dispatch event that child has been removed
    GameObject* curChild = *it;
    Event e( Event::REMOVED );
    curChild->dispatchEvent( e );
    }*/

    /*auto begin = _children->begin();
    auto end = _children->end();
    for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
    {
    // Free child memory here? Or should it be removed where it's created?
    //delete *it;
    }*/

    delete _children;
    delete _boundingBox;
}

void GameObject::update( float dt )
{
    if( !_fixed )
    {
        // Apply "Euler Integration" for physics
        _velocity += _acceleration * dt / _mass;
        setPosition( _position + _velocity * dt );

        _rotationalVelocity += _rotationalAcceleration * dt / _mass;
        setRotation( _rotation + _rotationalVelocity );
    }

    if( _model != nullptr )
    {
        _boundingBox->setCenter( _position );
        _boundingBox->setScale( _scale );
        _boundingBox->setRotation( _rotation, _rotationAxis );
    }

    // Update all nested children
    auto begin = _children->begin();
    auto end = _children->end();
    for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
    {
        ( *it )->update( dt );
    }
}

void GameObject::draw( float dt )
{
    drawShape();

    // Draw all nested children
    auto begin = _children->begin();
    auto end = _children->end();
    for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
    {
        ( *it )->draw( dt );
    }
}

void GameObject::drawShape()
{
    /*
    setShaderColor
    (
    _programIndex,
    "color",
    _color.getRed(),
    _color.getGreen(),
    _color.getBlue()
    );
    */

    if( _model != nullptr )
    {
        glm::mat4 worldMatrix =
            glm::translate( _position ) *
            glm::scale( _scale ) *
            glm::rotate( _rotation, _rotationAxis );
        setShaderMatrix( _programIndex, "worldMatrix", worldMatrix );

        _model->draw();

        // Reset world matrix for any upcoming draw calls
        setShaderMatrix( _programIndex, "worldMatrix", glm::scale( glm::vec3( 1, 1, 1 ) ) );
        // _boundingBox->draw();
    }
}

void GameObject::addChild( GameObject* child )
{
    if( !contains( child ) )
    {
        child->setProgramIndex( _programIndex );
        _children->push_back( child );

        // Dispatch event that child has been added
        DisplayEvent e( DisplayEvent::ADDED );
        child->dispatchEvent( e );
        child->setParent( this );
    }
}

void GameObject::removeChild( GameObject* child, bool free )
{
    auto begin = _children->begin();
    auto end = _children->end();
    for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
    {
        GameObject* curChild = *it;

        if( curChild == child )
        {
            // Dispatch event that child has been removed
            DisplayEvent e( DisplayEvent::REMOVED );
            child->dispatchEvent( e );
            child->setParent( nullptr );

            _children->erase( it );

            if( free )
            {
                delete curChild;
            }

            break;
        }
    }
}

bool GameObject::contains( GameObject* child )
{
    auto begin = _children->begin();
    auto end = _children->end();
    for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
    {
        GameObject* curChild = *it;

        if( curChild == child )
        {
            return true;
        }
    }

    return false;
}

void GameObject::addForce( glm::vec3 force )
{
    _acceleration += force / _mass;
}

void GameObject::addImpulse( glm::vec3 impulse )
{
    _velocity += impulse;
}

GameObject* GameObject::getParent()
{
    return _parent;
}
void GameObject::setParent( GameObject* value )
{
    _parent = value;
}

glm::vec3 GameObject::getPosition()
{
    return _position;
}
void GameObject::setPosition( glm::vec3 value )
{
    _position = value;
}

glm::vec3 GameObject::getVelocity()
{
    return _velocity;
}
void GameObject::setVelocity( glm::vec3 value )
{
    _velocity = value;
}

glm::vec3 GameObject::getAcceleration()
{
    return _acceleration;
}
void GameObject::setAcceleration( glm::vec3 value )
{
    _acceleration = value;
}

glm::vec3 GameObject::getScale()
{
    return _scale;
}
void GameObject::setScale( glm::vec3 value )
{
    _scale = value;
}

glm::vec3 GameObject::getRotationAxis()
{
    return _rotationAxis;
}
void GameObject::setRotationAxis( glm::vec3 value )
{
    _rotationAxis = value;
}

glm::vec3 GameObject::getForward()
{
    return _forward;
}
void GameObject::setForward( glm::vec3 value )
{
    _forward = value;
}

void GameObject::rotate( float angle )
{
    setRotation( _rotation + angle );
}

float GameObject::getRotation()
{
    return _rotation;
}
void GameObject::setRotation( float value )
{
    _rotation = value;
}

float GameObject::getRotationalVelocity()
{
    return _rotationalVelocity;
}
void GameObject::setRotationalVelocity( float value )
{
    _rotationalVelocity = value;
}

float GameObject::getRotationalAcceleration()
{
    return _rotationalAcceleration;
}
void GameObject::setRotationalAcceleration( float value )
{
    _rotationalAcceleration = value;
}

float GameObject::getMass()
{
    return _mass;
}
void GameObject::setMass( float value )
{
    _mass = value;
}

bool GameObject::getFixed()
{
    return _fixed;
}
void GameObject::setFixed( bool value )
{
    _fixed = value;
}

bool GameObject::getSolid()
{
	return _isSolid;
}
void GameObject::setSolid(bool value)
{
	_isSolid = value;
}

GLuint GameObject::getProgramIndex()
{
    return _programIndex;
}
void GameObject::setProgramIndex( GLuint value )
{
    _programIndex = value;

    // Get locations of uniform variables in the shader program
    _offsetIndex = glGetUniformLocation( _programIndex, "offset" );
    _scaleIndex = glGetUniformLocation( _programIndex, "scale" );

    auto begin = _children->begin();
    auto end = _children->end();
    for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
    {
        GameObject* curChild = *it;
        curChild->setProgramIndex( _programIndex );
    }
}

Model* GameObject::getModel()
{
    return _model;
}
void GameObject::setModel( Model* value )
{
    _model = value;
    _boundingBox->createFromModel( _model );
}

BoundingBox* GameObject::getBoundingBox()
{
    return _boundingBox;
}

bool GameObject::collidesWith( GameObject* other )
{
    return _boundingBox->collidesWith( other->getBoundingBox() );
}

void GameObject::handleCollision(GameObject* other )
{
	if (_velocity.y < 0 && other->getSolid() && _isSolid)
	{
		_velocity.y = 0;
		_position.y = other->getPosition().y + other->getBoundingBox()->getHalfWidthY() + _boundingBox->getHalfWidthY();
	}
}
