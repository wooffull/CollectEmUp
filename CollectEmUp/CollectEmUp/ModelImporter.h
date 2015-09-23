#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glew.h>
#include <glm\glm.hpp>
#include "FileImporter.h"
#include "ModelImportData.h"
#include "Model.h"

class ModelImporter :
	public FileImporter
{
public:
	ModelImporter();
	virtual ~ModelImporter();
	
	virtual ImportData* loadFromFile( const char* filePath );
	virtual Model* loadModel( const char* filePath, GLuint programIndex = 0 );

private:
	static const std::string& VALUE_DELIMITER;
	static const std::string& FACE_VERTEX_INDEX_DELIMITER;

	glm::vec3 parseVertexValues( std::string line );
	std::vector<GLushort> parseFaceValues( std::string line );
};

