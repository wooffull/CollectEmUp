#pragma once

#include "GameObject.h"
#include "Triangle.h"
#include "Random.h"

class Environment :
	public GameObject
{
public:
	Environment();
	virtual ~Environment();
	
	virtual void update( float dt );

	void applyGravity();
	void applyDrag();

	void createTriangle( glm::vec2 position, glm::vec2 velocity );
	
	void onRemoved( Event e );

private:
	static const glm::vec3& GRAVITY;
	static const float& DRAG;
	static const float& FRICTION;
	static const float& DEFLECT_PERCENTAGE;
	static const int& TOTAL_TRIANGLES;

	Triangle** _triangles;
	int _curTriangleIndex;
	glm::mat4 _worldMatrix;
};

