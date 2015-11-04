#pragma once

#include <vector>
#include <glew.h>
#include <glm\glm.hpp>
#include <SOIL.h>

class Model
{
public:
	Model( std::vector<GLfloat> vertexBufferData, std::vector<GLushort> faceBufferData, char* textureFilePath );
	virtual ~Model();

	void draw();
	
	std::vector<glm::vec3> boundingBox(GLushort maxX, GLushort maxY, GLushort maxZ, GLushort minX, GLushort minY, GLushort minZ);

	GLushort getMaxX();
	GLushort getMaxY();
	GLushort getMaxZ();
	GLushort getMinX();
	GLushort getMinY();
	GLushort getMinZ();

private:
	GLuint _vboIndex;
	GLuint _vaoIndex;

	std::vector<GLfloat> _vertexBufferData;
	std::vector<GLushort> _faceBufferData;
	GLuint _textureID;

	GLushort _maxX;
	GLushort _maxY;
	GLushort _maxZ;
	GLushort _minX;
	GLushort _minY;
	GLushort _minZ;
};

