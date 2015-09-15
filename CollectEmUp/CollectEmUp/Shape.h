#pragma once

#include <glew.h>

class Shape
{
public:
	Shape( GLfloat* vertices, int totalVertices, GLuint shaderProgramIndex );
	virtual ~Shape();

	void draw( float x, float y, float xScale, float yScale, float rotation );
	
	void setProgramIndex( GLuint value );

private:
	GLuint _vboIndex;
	GLuint _vaoIndex;
	GLuint _programIndex;

	GLint _offsetIndex;
	GLint _scaleIndex;
	GLint _rotationIndex;

	GLsizei _totalVertices;
};

