#pragma once

#include <vector>
#include <glfw3.h>
#include <glm\glm.hpp>
#include "FileImportData.h"

class ModelImportData :
	public FileImportData
{
public:
	ModelImportData();
	virtual ~ModelImportData();

	std::vector<glm::vec3> getVertices();
	void setVertices( std::vector<glm::vec3> value );

	std::vector<glm::vec2> getTextureCoordinates();
	void setTextureCoordinates( std::vector<glm::vec2> value );

	std::vector<glm::vec3> getNormals();
	void setNormals( std::vector<glm::vec3> value );

	std::vector<GLushort> getFaceVertexIndices();
	void setFaceVertexIndices( std::vector<GLushort> value );

private:
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _textureCoordinates;
	std::vector<glm::vec3> _normals;
	std::vector<GLushort> _faceVertexIndices;
};

