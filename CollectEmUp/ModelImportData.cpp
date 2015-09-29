#include "ModelImportData.h"

ModelImportData::ModelImportData()
{
}

ModelImportData::~ModelImportData()
{
}

std::vector<glm::vec3> ModelImportData::getVertices()
{
	return _vertices;
}
void ModelImportData::setVertices( std::vector<glm::vec3> value )
{
	_vertices = value;
}

std::vector<glm::vec2> ModelImportData::getTextureCoordinates()
{
	return _textureCoordinates;
}
void ModelImportData::setTextureCoordinates( std::vector<glm::vec2> value )
{
	_textureCoordinates = value;
}

std::vector<glm::vec3> ModelImportData::getNormals()
{
	return _normals;
}
void ModelImportData::setNormals( std::vector<glm::vec3> value )
{
	_normals = value;
}

std::vector<GLushort> ModelImportData::getFaceVertexIndices()
{
	return _faceVertexIndices;
}
void ModelImportData::setFaceVertexIndices( std::vector<GLushort> value )
{
	_faceVertexIndices = value;
}