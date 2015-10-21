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

	std::vector<GLfloat> getVertexBufferData();
	void setVertexBufferData( std::vector<GLfloat> value );

	std::vector<GLushort> getFaceBufferData();
	void setFaceBufferData( std::vector<GLushort> value );

private:
	std::vector<GLfloat> _vertexBufferData;
	std::vector<GLushort> _faceBufferData;
};

