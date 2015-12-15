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
	//glBindTexture( GL_TEXTURE_2D, _textureID );

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
	glBindTexture(GL_TEXTURE_2D, _textureID);

	// Bind VAO
	glBindVertexArray( _vaoIndex );

	// Have OpenGL draw using the currently bound buffer
	glDrawElements( GL_TRIANGLES, 8 * _faceBufferData.size(), GL_UNSIGNED_SHORT, 0 );
}

/*
std::vector<glm::vec3> Model::boundingBox(GLushort maxX, GLushort maxY, GLushort maxZ, GLushort minX, GLushort minY, GLushort minZ)
{
	//vector to contain the vec3s for each vertex in the bounding box
	std::vector<glm::vec3> boxVectors;
	
	//data showing point connections and layout of bounding box
	
	point 1 connects to: point 2, point 3, point 5
	point 2 connects to: point 1, point 4, point 6
	point 3 connects to: point 1, point 4, point 7
	point 4 connects to: point 2, point 3, point 8
	point 5 connects to: point 1, point 6, point 7
	point 6 connects to: point 2, point 5, point 8
	point 7 connects to: point 3, point 5, point 8
	point 8 connects to: point 4, point 6, point 7
	

	//top square
	// (maxX, maxY, maxZ)
	glm::vec3 point1 = glm::vec3(maxX, maxY, maxZ);
	boxVectors.push_back(point1);
	// (minX, maxY, maxZ)
	glm::vec3 point2 = glm::vec3(minX, maxY, maxZ);
	boxVectors.push_back(point2);
	// (maxX, maxY, minZ)
	glm::vec3 point3 = glm::vec3(maxX, maxY, minZ);
	boxVectors.push_back(point3);
	// (minX, maxY, minZ)
	glm::vec3 point4 = glm::vec3(minX, maxY, minZ);	
	boxVectors.push_back(point4);

	//bottom square
	// (maxX, minY, maxZ)
	glm::vec3 point5 = glm::vec3(maxX, minY, maxZ);
	boxVectors.push_back(point5);
	// (minX, minY, maxZ)
	glm::vec3 point6 = glm::vec3(minX, minY, maxZ);
	boxVectors.push_back(point6);
	// (maxX, minY, minZ)
	glm::vec3 point7 = glm::vec3(maxX, minY, minZ);
	boxVectors.push_back(point7);
	// (minX, minY, minZ)
	glm::vec3 point8 = glm::vec3(minX, minY, minZ);
	boxVectors.push_back(point8);

	return boxVectors;
}
*/

std::vector<GLfloat> Model::getVertexBufferData()
{
	return _vertexBufferData;
}