#pragma once

#include <glew.h>
#include <glm\glm.hpp>

using namespace glm;

void setShaderColor( GLuint programIndex, const char* uniformVariableName, float r, float g, float b );
void setShaderVec2( GLuint programIndex, const char* uniformVariableName, const vec2& vecToSend );
void setShaderVec3( GLuint programIndex, const char* uniformVariableName, const vec3& vecToSend );
void setShaderMatrix( GLuint programIndex, const char* uniformVariableName, const mat4& matrixToSend );