#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glew.h>

#include "Model.h"

class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();

	BoundingBox(GLushort maxX, GLushort maxY, GLushort maxZ, GLushort minX, GLushort minY, GLushort minZ);

	static BoundingBox createFromModel(Model* model);

	//draw method for debugging goes here

private:
	GLushort _maxX;
	GLushort _maxY;
	GLushort _maxZ;
	GLushort _minX;
	GLushort _minY;
	GLushort _minZ;
};

