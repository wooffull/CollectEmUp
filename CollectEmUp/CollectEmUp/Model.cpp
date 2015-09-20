#include "Model.h"

Model::Model( std::vector<glm::vec3> vertices, std::vector<GLushort> faces )
{
	_vertices = vertices;
	_faces = faces;

	glGenVertexArrays( 1, &_vaoIndex );

	// Set newly created VAO as the active one
	glBindVertexArray( _vaoIndex );

	glGenBuffers( 1, &_vboIndex );

	// Set newly created VBO as the active one
	glBindBuffer( GL_ARRAY_BUFFER, _vboIndex );

	// Copy vertex data into OpenGL buffer
	glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec3 ) * vertices.size(), &vertices[0], GL_STATIC_DRAW );

	// Describe layout of data to OpenGL
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glEnableVertexAttribArray( 0 );

	// Set up element array buffer
	GLuint indexBufferId;
	glGenBuffers( 1, &indexBufferId );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBufferId );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof( GLushort ) * faces.size(), &faces[0], GL_STATIC_DRAW );
}

Model::~Model()
{
	glDeleteVertexArrays( 1, &_vaoIndex );
	glDeleteBuffers( 1, &_vboIndex );
}

// Draw the shape to the screen
void Model::draw()
{
	// Bind VAO
	glBindVertexArray( _vaoIndex );

	// Have OpenGL draw using the currently bound buffer
	glDrawElements( GL_TRIANGLES, 3 * _faces.size(), GL_UNSIGNED_SHORT, 0 );
}