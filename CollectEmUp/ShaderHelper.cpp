#include "ShaderHelper.h"

void setShaderColor( GLuint programIndex, const char* uniformVariableName, float r, float g, float b )
{
	// Get location of specified variable in the specified shader program
	GLint uniformLocation = glGetUniformLocation( programIndex, uniformVariableName );

	glProgramUniform4f( programIndex, uniformLocation, r, g, b, 1.0f );
}

void setShaderVec2( GLuint programIndex, const char* uniformVariableName, const vec2& vecToSend )
{
	// Get location of specified variable in the specified shader program
	GLint uniformLocation = glGetUniformLocation( programIndex, uniformVariableName );

	glProgramUniform2fv( programIndex, uniformLocation, 1, &vecToSend[0] );
}

void setShaderVec3( GLuint programIndex, const char* uniformVariableName, const vec3& vecToSend )
{
	// Get location of specified variable in the specified shader program
	GLint uniformLocation = glGetUniformLocation( programIndex, uniformVariableName );

	glProgramUniform3fv( programIndex, uniformLocation, 1, &vecToSend[0] );
}

void setShaderMatrix( GLuint programIndex, const char* uniformVariableName, const mat4& matrixToSend )
{
	// Get location of specified variable in the specified shader program
	GLint uniformLocation = glGetUniformLocation( programIndex, uniformVariableName );

	glProgramUniformMatrix4fv( programIndex, uniformLocation, 1, GL_FALSE, &matrixToSend[0][0] );
}
