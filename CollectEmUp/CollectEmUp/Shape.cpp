#include "Shape.h"

Shape::Shape( GLfloat* vertices, int totalVertices, GLuint shaderProgramIndex )
{
	setProgramIndex( shaderProgramIndex );
	_totalVertices = totalVertices;

	glGenVertexArrays( 1, &_vaoIndex );

	// Set newly created VAO as the active one
	glBindVertexArray( _vaoIndex );

	glGenBuffers( 1, &_vboIndex );

	// Set newly created VBO as the active one
	glBindBuffer( GL_ARRAY_BUFFER, _vboIndex );

	// Copy vertex data into OpenGL buffer
	glBufferData( GL_ARRAY_BUFFER, 2 * sizeof( GLfloat ) * _totalVertices, vertices, GL_STATIC_DRAW );

	// Describe layout of data to OpenGL
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glEnableVertexAttribArray( 0 );
}

Shape::~Shape()
{
	glDeleteVertexArrays( 1, &_vaoIndex );
	glDeleteBuffers( 1, &_vboIndex );
}

// Draw the shape to the screen
void Shape::draw( float x, float y, float xScale, float yScale, float rotation )
{
	glProgramUniform2f( _programIndex, _offsetIndex, x, y );
	glProgramUniform2f( _programIndex, _scaleIndex, xScale, yScale );
	glProgramUniform1f( _programIndex, _rotationIndex, rotation );

	// Bind VAO
	glBindVertexArray( _vaoIndex );

	// Have OpenGL draw using the currently bound buffer
	glDrawArrays( GL_TRIANGLE_FAN, 0, _totalVertices );
}

void Shape::setProgramIndex( GLuint value )
{
	_programIndex = value;

	// Get locations of uniform variables in the shader program
	_offsetIndex = glGetUniformLocation( _programIndex, "offset" );
	_scaleIndex = glGetUniformLocation( _programIndex, "scale" );
	_rotationIndex = glGetUniformLocation( _programIndex, "rotation" );
}