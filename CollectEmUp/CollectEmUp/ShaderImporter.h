#pragma once

#include <glew.h>
#include <iostream>
#include "FileImporter.h"

class ShaderImporter :
	public FileImporter
{
public:
	ShaderImporter();
	virtual ~ShaderImporter();

	GLuint loadShaderProgram( char* vertexFile, char* fragmentFile );

private:
	GLuint loadShader( char* filePath, GLenum shaderType );
};

