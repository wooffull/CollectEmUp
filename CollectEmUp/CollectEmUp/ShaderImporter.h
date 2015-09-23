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

	GLuint loadShaderProgram( const char* vertexFile, const char* fragmentFile );

private:
	GLuint loadShader( const char* filePath, GLenum shaderType );
};

