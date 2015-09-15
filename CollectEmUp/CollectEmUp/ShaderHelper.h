#pragma once

#include <glew.h>
#include <glm\glm.hpp>

using namespace glm;

char* loadTextFile( const char* file );
GLuint loadShader( const char* file, GLenum shaderType );
GLuint loadShaderProgram( const char* vertexFile, const char* fragmentFile );
void setShaderColor( GLuint programIndex, const char* uniformVariableName, float r, float g, float b );
void setShaderVec2( GLuint programIndex, const char* uniformVariableName, vec2 vecToSend );
void setShaderMatrix( GLuint programIndex, const char* uniformVariableName, mat4 matrixToSend );