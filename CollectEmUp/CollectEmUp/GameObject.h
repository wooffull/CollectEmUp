#pragma once

#include <vector>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "ShaderHelper.h"
#include "EventDispatcher.h"
#include "Color.h"
#include "Model.h"

class GameObject :
	public EventDispatcher
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void update( float dt );
	virtual void draw( float dt );
	virtual void drawShape();

	virtual void addChild( GameObject* child );
	virtual void removeChild( GameObject* child, bool free = false );
	virtual bool contains( GameObject* child );

	virtual void addForce( glm::vec3 force );

	GameObject* getParent();
	void setParent( GameObject* value );

	virtual glm::vec3 getPosition();
	virtual void setPosition( glm::vec3 value );

	virtual glm::vec3 getVelocity();
	virtual void setVelocity( glm::vec3 value );

	virtual glm::vec3 getAcceleration();
	virtual void setAcceleration( glm::vec3 value );

	virtual glm::vec3 getScale();
	virtual void setScale( glm::vec3 value );

	virtual glm::vec3 getRotationAxis();
	virtual void setRotationAxis( glm::vec3 value );

	virtual float getRotation();
	virtual void setRotation( float value );

	virtual float getRotationalVelocity();
	virtual void setRotationalVelocity( float value );

	virtual float getRotationalAcceleration();
	virtual void setRotationalAcceleration( float value );

	virtual float getMass();
	virtual void setMass( float value );

	virtual bool getFixed();
	virtual void setFixed( bool value );

	virtual Color getColor();
	virtual void setColor( Color value );
	virtual void setColor( float r, float g, float b, float a = 1.0f );

	virtual GLuint getProgramIndex();
	virtual void setProgramIndex( GLuint value );

	virtual Model* getModel();
	virtual void setModel( Model* value );

protected:
	GameObject* _parent;
	std::vector<GameObject*>* _children;
	glm::vec3 _position;
	glm::vec3 _velocity;
	glm::vec3 _acceleration;
	glm::vec3 _scale;
	glm::vec3 _rotationAxis;
	float _rotation;
	float _rotationalVelocity;
	float _rotationalAcceleration;
	float _mass;
	bool _fixed;
	Color _color;
	GLuint _programIndex;
	Model* _model;

	GLint _offsetIndex;
	GLint _scaleIndex;
};

