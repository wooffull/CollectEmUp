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
	std::vector<GLfloat> vertexBufferData;
	std::vector<GLushort> faceBufferData;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvVertices;
	std::vector<glm::vec3> normals;
	std::unordered_map<std::string, GLushort> faceDataMap;
	GLushort faceIndexCounter = 0;

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
			bool isValid = ( isVertex || isTextureCoord || isNormal || isFace );
			
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
					GLushort vertexIndex, uvIndex, normalIndex;

					for( unsigned i = 0; i < splitValues.size(); i++ )
					{
						std::string currentFaceVertexData = splitValues[i];

						// Couldn't find the current face vertex data in the unordered map, so we have to parse it
						if( faceDataMap.find( currentFaceVertexData ) == faceDataMap.end() )
						{
							// Subtract 1 because face vertex indices start at 1, not 0
							std::vector<std::string> splitData = split( splitValues[i], FACE_VERTEX_INDEX_DELIMITER );
							vertexIndex = (GLushort)( std::stoi( splitData[0] ) - 1 );
							uvIndex = (GLushort)( std::stoi( splitData[1] ) - 1 );
							normalIndex = (GLushort)( std::stoi( splitData[2] ) - 1 );

							vertexBufferData.push_back( vertices[vertexIndex].x );
							vertexBufferData.push_back( vertices[vertexIndex].y );
							vertexBufferData.push_back( vertices[vertexIndex].z );
							vertexBufferData.push_back( uvVertices[uvIndex].x );
							vertexBufferData.push_back( uvVertices[uvIndex].y );
							vertexBufferData.push_back( normals[normalIndex].x );
							vertexBufferData.push_back( normals[normalIndex].y );
							vertexBufferData.push_back( normals[normalIndex].z );

							faceDataMap.insert( std::make_pair( currentFaceVertexData, faceIndexCounter ) );
							faceIndexCounter++;
						}

						// Add the index to the face buffer data
						faceBufferData.push_back( faceDataMap[currentFaceVertexData] );
					}
				}
			}
		}

		ModelImportData* importData = new ModelImportData();
		importData->setVertexBufferData( vertexBufferData );
		importData->setFaceBufferData( faceBufferData );
		return importData;
	}
	else
	{
		return nullptr;
	}
}

Model* ModelImporter::loadModel( char* filePath, char* textureFilePath, GLuint programIndex )
{
	ImportData* importData = loadFromFile( filePath );
	ModelImportData* modelImportData = static_cast<ModelImportData*>( importData );
	
	std::vector<GLfloat> vertexBufferData = modelImportData->getVertexBufferData();
	std::vector<GLushort> faceBufferData = modelImportData->getFaceBufferData();

	Model* model = new Model( vertexBufferData, faceBufferData, textureFilePath );

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