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

private:
	GLuint _vboIndex;
	GLuint _vaoIndex;

	std::vector<GLfloat> _vertexBufferData;
	std::vector<GLushort> _faceBufferData;
	GLuint _textureID;
};

