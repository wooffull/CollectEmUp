#include "ModelImportData.h"

ModelImportData::ModelImportData()
{
}

ModelImportData::~ModelImportData()
{
}

std::vector<GLfloat> ModelImportData::getVertexBufferData()
{
	return _vertexBufferData;
}
void ModelImportData::setVertexBufferData( std::vector<GLfloat> value )
{
	_vertexBufferData = value;
}

std::vector<GLushort> ModelImportData::getFaceBufferData()
{
	return _faceBufferData;
}
void ModelImportData::setFaceBufferData( std::vector<GLushort> value )
{
	_faceBufferData = value;
}