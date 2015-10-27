#include "Model.h"

Model::Model( std::vector<GLfloat> vertexBufferData, std::vector<GLushort> faceBufferData, char* textureFilePath )
{
	_vertexBufferData = vertexBufferData;
	_faceBufferData = faceBufferData;

	// Load texture
	_textureID = SOIL_load_OGL_texture(
		textureFilePath, SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
	);
	glBindTexture( GL_TEXTURE_2D, _textureID );

	glGenVertexArrays( 1, &_vaoIndex );

	// Set newly created VAO as the active one
	glBindVertexArray( _vaoIndex );

	glGenBuffers( 1, &_vboIndex );

	// Set newly created VBO as the active one
	glBindBuffer( GL_ARRAY_BUFFER, _vboIndex );

	// Copy vertex data into OpenGL buffer
	glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * vertexBufferData.size(), &vertexBufferData[0], GL_STATIC_DRAW );

	// Describe layout of data to OpenGL
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( GL_FLOAT ) * 8, 0 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( GL_FLOAT ) * 8, (void*)( sizeof( GL_FLOAT ) * 3 ) );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, sizeof( GL_FLOAT ) * 8, (void*)( sizeof( GL_FLOAT ) * 5 ) );

	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );

	// Set up element array buffer
	GLuint indexBufferId;
	glGenBuffers( 1, &indexBufferId );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBufferId );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLushort ) * faceBufferData.size(), &faceBufferData[0], GL_STATIC_DRAW );
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
	glDrawElements( GL_TRIANGLES, 8 * _faceBufferData.size(), GL_UNSIGNED_SHORT, 0 );
}