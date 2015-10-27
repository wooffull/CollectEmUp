#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
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
	
	virtual ImportData* loadFromFile( char* filePath );
	virtual Model* loadModel( char* filePath, char* textureFilePath, GLuint programIndex = 0 );

private:
	static const char& VALUE_DELIMITER;
	static const char& FACE_VERTEX_INDEX_DELIMITER;

	std::vector<std::string> split( std::string toBeSplit, char delimiter );
};

