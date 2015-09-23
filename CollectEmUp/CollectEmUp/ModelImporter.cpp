#include "ModelImporter.h"

const std::string& ModelImporter::VALUE_DELIMITER = " ";
const std::string& ModelImporter::FACE_VERTEX_INDEX_DELIMITER = "/";

ModelImporter::ModelImporter()
{
}

ModelImporter::~ModelImporter()
{
}

ImportData* ModelImporter::loadFromFile( const char* filePath )
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textureCoordinates;
	std::vector<glm::vec3> normals;
	std::vector<GLushort> faceVertexIndices;

	std::ifstream inFile( filePath );

	if( inFile.is_open() )
	{
		std::string line;

		while( std::getline( inFile, line ) )
		{
			bool isVertex = ( line.find( "v " ) == 0 );
			bool isTextureCoord = ( line.find( "vt " ) == 0 );
			bool isNormal = ( line.find( "vn " ) == 0 );
			bool isFace = ( line.find( "f " ) == 0 );
			bool isValid = isVertex || isTextureCoord || isNormal || isFace;

			if( isValid )
			{
				if( isVertex )
				{
					glm::vec3 vertex = parseVertexValues( line );
					vertices.push_back( vertex );
				}
				else if( isTextureCoord )
				{
					glm::vec3 vertex = parseVertexValues( line );
					glm::vec2 textureCoordinate( vertex.x, vertex.y );
					textureCoordinates.push_back( textureCoordinate );
				}
				else if( isNormal )
				{
					glm::vec3 normal = parseVertexValues( line );
					normals.push_back( normal );
				}
				else if( isFace )
				{
					std::vector<GLushort> face = parseFaceValues( line );

					// Put all index values from the parsed face into the array containing them all
					faceVertexIndices.insert( faceVertexIndices.end(), face.begin(), face.end() );
				}
			}
		}

		ModelImportData* importData = new ModelImportData();
		importData->setVertices( vertices );
		importData->setTextureCoordinates( textureCoordinates );
		importData->setNormals( normals );
		importData->setFaceVertexIndices( faceVertexIndices );
		return importData;
	}
	else
	{
		return nullptr;
	}
}

Model* ModelImporter::loadModel( const char* filePath, GLuint programIndex )
{
	ImportData* importData = loadFromFile( filePath );
	ModelImportData* modelImportData = static_cast<ModelImportData*>( importData );
	
	std::vector<glm::vec3> vertices = modelImportData->getVertices();
	std::vector<GLushort> faces = modelImportData->getFaceVertexIndices();

	Model* model = new Model( vertices, faces );

	return model;
}

glm::vec3 ModelImporter::parseVertexValues( std::string line )
{
	size_t valPos = line.find( VALUE_DELIMITER );
	std::vector<float> parsedValues;
	int totalParsedValues = 0;
	bool endOfLine = false;

	// Remove the key
	line.erase( 0, valPos + 1 );

	// Parse the string
	while( true )
	{
		valPos = line.find( VALUE_DELIMITER );

		std::string valString;

		if( valPos == std::string::npos )
		{
			valString = line.substr( 0, line.size() );
			endOfLine = true;
		}
		else
		{
			valString = line.substr( 0, valPos );
		}

		float value = std::stof( valString );
		parsedValues.push_back( value );
		totalParsedValues++;

		if( endOfLine )
		{
			break;
		}

		line.erase( 0, valPos + VALUE_DELIMITER.size() );
	}

	// Ensure we have 3 values in the vec3 by forcing 0s into the empty spots
	for( int i = 0; i < 3 - totalParsedValues; i++ )
	{
		parsedValues.push_back( 0 );
	}

	return glm::vec3( parsedValues[0], parsedValues[1], parsedValues[2] );
}

std::vector<GLushort> ModelImporter::parseFaceValues( std::string line )
{
	size_t valPos = line.find( VALUE_DELIMITER );
	size_t separatorPos;
	std::vector<GLushort> parsedValues;

	// Remove the key
	line.erase( 0, valPos + 1 );

	// Parse the string
	while( true )
	{
		valPos = line.find( VALUE_DELIMITER );
		separatorPos = line.find( FACE_VERTEX_INDEX_DELIMITER );

		std::string valString;

		if( separatorPos != std::string::npos )
		{
			valString = line.substr( 0, separatorPos );
		}

		// -1 because face vertex indices start at 1, not 0
		GLushort value = (GLushort)( std::stoi( valString ) - 1 );
		parsedValues.push_back( value );
		
		if( valPos == std::string::npos )
		{
			break;
		}

		line.erase( 0, valPos + VALUE_DELIMITER.size() );
	}

	return parsedValues;
}