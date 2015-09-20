#include "ShaderImporter.h"

ShaderImporter::ShaderImporter() :
	FileImporter()
{
}

ShaderImporter::~ShaderImporter()
{
}

GLuint ShaderImporter::loadShaderProgram( char* vertexFile, char* fragmentFile )
{
	GLuint vertexShaderIndex = loadShader( vertexFile, GL_VERTEX_SHADER );

	if( !vertexShaderIndex )
	{
		return 0;
	}
	
	GLuint fragmentShaderIndex = loadShader( fragmentFile, GL_FRAGMENT_SHADER );

	if( !fragmentShaderIndex )
	{
		return 0;
	}

	// Create the shader program if the shaders were loaded correctly
	GLuint programID = glCreateProgram();
	glAttachShader( programID, vertexShaderIndex );
	glAttachShader( programID, fragmentShaderIndex );
	glLinkProgram( programID );

	// Determine if the program linked correctly
	GLint linkResult;
	glGetProgramiv( programID, GL_LINK_STATUS, &linkResult );

	if( linkResult == GL_TRUE )
	{
		return programID;
	}
	else
	{
		int errorLogLength;
		glGetProgramiv( programID, GL_INFO_LOG_LENGTH, &errorLogLength );

		char* errorLog = new char[errorLogLength];
		glGetProgramInfoLog( programID, errorLogLength, 0, errorLog );

		std::cout << errorLog;

		glDeleteProgram( programID );

		delete[] errorLog;

		return -1;
	}
}

GLuint ShaderImporter::loadShader( char* filePath, GLenum shaderType )
{
	ImportData* importData = loadFromFile( filePath );
	FileImportData* fileImportData = static_cast<FileImportData*>( importData );

	const char* fileContents = fileImportData->getFileContents();

	if( !fileContents )
	{
		if( fileImportData )
		{
			delete fileImportData;
		}

		std::cout << "There was an error opening the file." << std::endl;
		return 0;
	}

	GLuint shaderIndex = glCreateShader( shaderType );
	glShaderSource( shaderIndex, 1, &fileContents, 0 );
	glCompileShader( shaderIndex );
	
	delete fileImportData;

	// Determine if shader compiled
	GLint compilationResult;
	glGetShaderiv( shaderIndex, GL_COMPILE_STATUS, &compilationResult );

	if( compilationResult == GL_TRUE )
	{
		std::cout << "Successful compilation." << std::endl;
		return shaderIndex;
	}
	else
	{
		std::cout << "Failed to compile." << std::endl;

		GLint logLength;

		// Get length of log
		glGetShaderiv( shaderIndex, GL_INFO_LOG_LENGTH, &logLength );

		// Get the log
		char* log = new char[logLength];
		glGetShaderInfoLog( shaderIndex, logLength, 0, log );

		std::cout << log << std::endl;

		glDeleteShader( shaderIndex );

		delete[] log;

		return -1;
	}
}