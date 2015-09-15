#include "Environment.h"

const glm::vec3& Environment::GRAVITY = glm::vec3( 0, -1.0f, 0 );
const float& Environment::DRAG = -0.10f;
const float& Environment::FRICTION = 0.95f;
const float& Environment::DEFLECT_PERCENTAGE = 0.5f;
const int& Environment::TOTAL_TRIANGLES = 200;

Environment::Environment()
{
	// Add event listener to self for when the triangle has been removed
	Callback cRemoved = std::bind( &Environment::onRemoved, this, std::placeholders::_1 );
	addEventListener( Event::REMOVED, cRemoved );

	_triangles = new Triangle*[TOTAL_TRIANGLES];

	for( int i = 0; i < TOTAL_TRIANGLES; i++ )
	{
		float percentage = ( i - TOTAL_TRIANGLES * 0.5f ) / ( TOTAL_TRIANGLES * 0.5f );
		float r = percentage * 0.75f;
		float g = percentage;
		float b = 0.5f - percentage * 0.5f;

		Triangle* t = new Triangle();
		t->setColor( r, g, b );
		_triangles[i] = t;
	}

	_curTriangleIndex = 0;
	_worldMatrix = glm::one<glm::mat4>();
}

Environment::~Environment()
{
	for( int i = TOTAL_TRIANGLES - 1; i >= 0; i-- )
	{
		delete _triangles[i];
	}

	delete[] _triangles;
}

void Environment::update( float dt )
{
	applyGravity();
	applyDrag();

	GameObject::update( dt );

	auto begin = _children->begin();
	auto end = _children->end();
	for( std::vector<GameObject*>::iterator it = begin; it != end; ++it )
	{
		GameObject* curChild = *it;
		glm::vec3 position = curChild->getPosition();

		bool deflectOffLeft = position.x - Triangle::SIZE * 0.5f <= -1.0f;
		bool deflectOffRight = position.x + Triangle::SIZE * 0.5f >= 1.0f;
		bool deflectOffBottom = position.y - Triangle::SIZE * 0.5f <= -1.0f;
		bool deflectOffTop = position.y + Triangle::SIZE * 0.5f >= 1.0f;
		bool deflecting = deflectOffLeft || deflectOffRight || deflectOffBottom || deflectOffTop;

		if( deflecting )
		{
			glm::vec3 newVelocity = curChild->getVelocity();
			glm::vec3 newPosition = curChild->getPosition();
			float newRotationalVelocity = curChild->getRotationalVelocity() * -FRICTION;
			glm::vec3 surfaceNorm;
			glm::vec3 vNorm;

			// Deflect the triangle off the left and right parts of the screen
			if( deflectOffLeft || deflectOffRight )
			{
				if( deflectOffLeft )
				{
					newPosition.x = -1.0f + Triangle::SIZE * 0.5f;
					surfaceNorm = glm::vec3( 1, 0, 0 );
				}
				else
				{
					newPosition.x = 1.0f - Triangle::SIZE * 0.5f;
					surfaceNorm = glm::vec3( -1, 0, 0 );
				}

				vNorm = surfaceNorm * glm::dot( newVelocity, surfaceNorm );
				newVelocity -= vNorm * ( 1.0f + DEFLECT_PERCENTAGE );
			}

			// Deflect the triangle off the top and bottom parts of the screen
			if( deflectOffBottom || deflectOffTop )
			{
				if( deflectOffBottom )
				{
					newPosition.y = -1.0f + Triangle::SIZE * 0.5f;
					surfaceNorm = glm::vec3( 0, 1, 0 );
				}
				else
				{
					newPosition.y = 1.0f - Triangle::SIZE * 0.5f;
					surfaceNorm = glm::vec3( 0, -1, 0 );
				}

				vNorm = surfaceNorm * glm::dot( newVelocity, surfaceNorm );
				newVelocity -= vNorm * ( 1.0f + DEFLECT_PERCENTAGE );

				// Apply floor's friction
				if( deflectOffBottom )
				{
					newVelocity *= FRICTION;
				}
			}
			
			curChild->setPosition( newPosition );
			curChild->setVelocity( newVelocity );
			curChild->setRotationalVelocity( newRotationalVelocity );
		}
	}
	
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

void Environment::createTriangle( glm::vec2 position, glm::vec2 velocity )
{
	Triangle* t = _triangles[_curTriangleIndex];
	t->setPosition(
		glm::vec3
		(
			position.x,
			position.y,
			0
		)
	);
	t->setVelocity( glm::vec3( velocity, 0 ) );
	t->setAcceleration( glm::vec3() );
	
	float speed = sqrt( velocity.x * velocity.x + velocity.y * velocity.y );
	glm::vec2 velocityDirection;
	
	if( speed == 0 )
	{
		velocityDirection = glm::vec2( 0, -1 );
	}
	else
	{
		velocityDirection = velocity / speed;
	}

	float rotation = 2 * glm::pi<float>() * ( Random::getNext() % 100 ) / 100.0f;
	float rotationalVelocity = -glm::dot( velocityDirection, glm::vec2( 1, 0 ) ) / 100.0f;
	t->setRotation( rotation );
	t->setRotationalVelocity( rotationalVelocity );
	t->setRotationalAcceleration( 0 );

	addChild( t );

	_curTriangleIndex++;
	_curTriangleIndex %= TOTAL_TRIANGLES;
}

void Environment::onRemoved( Event e )
{
}