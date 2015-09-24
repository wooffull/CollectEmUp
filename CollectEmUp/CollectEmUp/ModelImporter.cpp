#include "ModelImporter.h"

const char& ModelImporter::VALUE_DELIMITER = ' ';
const char& ModelImporter::FACE_VERTEX_INDEX_DELIMITER = '/';

ModelImporter::ModelImporter()
{
}

ModelImporter::~ModelImporter()
{
}

ImportData* ModelImporter::loadFromFile( char* filePath )
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvVertices;
	std::vector<glm::vec3> normals;
	std::vector<GLushort> faceVertexIndices;
	std::vector<GLushort> faceUvIndices;
	std::vector<GLushort> faceNormalIndices;

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
				std::vector<std::string> splitValues = split( line, VALUE_DELIMITER );
				splitValues.erase( splitValues.begin(), splitValues.begin() + 1 );

				if( isVertex )
				{
					glm::vec3 vertex;
					vertex.x = std::stof( splitValues[0] );
					vertex.y = std::stof( splitValues[1] );
					vertex.z = std::stof( splitValues[2] );
					vertices.push_back( vertex );
				}
				else if( isTextureCoord )
				{
					glm::vec2 uv;
					uv.x = std::stof( splitValues[0] );
					uv.y = std::stof( splitValues[1] );
					uvVertices.push_back( uv );
				}
				else if( isNormal )
				{
					glm::vec3 normal;
					normal.x = std::stof( splitValues[0] );
					normal.y = std::stof( splitValues[1] );
					normal.z = std::stof( splitValues[2] );
					normals.push_back( normal );
				}
				else if( isFace )
				{
					GLushort vertexIndices[3], uvIndices[3], normalIndices[3];

					for( unsigned i = 0; i < splitValues.size(); i++ )
					{
						// -1 because face vertex indices start at 1, not 0
						std::vector<std::string> splitData = split( splitValues[i], FACE_VERTEX_INDEX_DELIMITER );
						vertexIndices[i] = (GLushort)( std::stoi( splitData[0] ) - 1 );
						uvIndices[i] = (GLushort)( std::stoi( splitData[1] ) - 1 );
						normalIndices[i] = (GLushort)( std::stoi( splitData[2] ) - 1 );
					}

					for( unsigned i = 0; i < 3; i++ )
					{
						faceVertexIndices.push_back( vertexIndices[i] );
						faceUvIndices.push_back( uvIndices[i] );
						faceNormalIndices.push_back( normalIndices[i] );
					}
				}
			}
		}

		ModelImportData* importData = new ModelImportData();
		importData->setVertices( vertices );
		importData->setTextureCoordinates( uvVertices );
		importData->setNormals( normals );
		importData->setFaceVertexIndices( faceVertexIndices );
		return importData;
	}
	else
	{
		return nullptr;
	}
}

Model* ModelImporter::loadModel( char* filePath, GLuint programIndex )
{
	ImportData* importData = loadFromFile( filePath );
	ModelImportData* modelImportData = static_cast<ModelImportData*>( importData );
	
	std::vector<glm::vec3> vertices = modelImportData->getVertices();
	std::vector<GLushort> faces = modelImportData->getFaceVertexIndices();

	Model* model = new Model( vertices, faces );

	return model;
}

std::vector<std::string> ModelImporter::split( std::string toBeSplit, char delimiter )
{
	std::vector<std::string> splitValues;
	splitValues.push_back("");

	for( auto c : toBeSplit )
	{
		if( c == delimiter )
		{
			splitValues.push_back("");
		}
		else
		{
			splitValues.back().push_back( c );
		}
	}
	
	return splitValues;
}