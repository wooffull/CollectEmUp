#pragma once

#include "GameObject.h"
#include "Random.h"
#include "ModelImporter.h"
#include "MouseEvent.h"

class Environment :
	public GameObject
{
public:
	Environment();
	virtual ~Environment();
	
	virtual void update( float dt );

	void applyGravity();
	void applyDrag();
	
	void onRemoved( Event e );
	void onAdded( Event e );

	void onMouseDown( MouseEvent e );

private:
	static const glm::vec3& GRAVITY;
	static const float& DRAG;
	static const float& FRICTION;
	static const float& DEFLECT_PERCENTAGE;

	glm::mat4 _worldMatrix;
};

