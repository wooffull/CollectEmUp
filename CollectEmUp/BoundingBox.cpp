#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::~BoundingBox()
{
}

BoundingBox::BoundingBox(GLushort maxX, GLushort maxY, GLushort maxZ, GLushort minX, GLushort minY, GLushort minZ)
{
	_maxX = maxX;
	_maxX = maxY;
	_maxX = maxZ;
	_maxX = minX;
	_maxX = minY;
	_maxX = minZ;
}

BoundingBox BoundingBox::createFromModel(Model* model)
{
	GLushort maxX = (GLushort)model->getVertexBufferData()[0];
	GLushort maxY = (GLushort)model->getVertexBufferData()[1];
	GLushort maxZ = (GLushort)model->getVertexBufferData()[2];
	GLushort minX = (GLushort)model->getVertexBufferData()[0];
	GLushort minY = (GLushort)model->getVertexBufferData()[1];
	GLushort minZ = (GLushort)model->getVertexBufferData()[2];
	for (GLuint i = 8; i < model->getVertexBufferData().size(); i += 8)
	{
		//calculate whether the current X is greater than maxX or less than minX
		GLushort tempX = (GLushort)model->getVertexBufferData()[i];
		if (tempX > maxX)
		{
			maxX = tempX;
		}
		else if (tempX < minX)
		{
			minX = tempX;
		}
		//calculate whether the current Y is greater than maxY or less than minY
		GLushort tempY = (GLushort)model->getVertexBufferData()[i+1];
		if (tempY > maxY)
		{
			maxY = tempY;
		}
		else if (tempY < minY)
		{
			minY = tempY;
		}
		//calculate whether the current Z is greater than maxZ or less than minZ
		GLushort tempZ = (GLushort)model->getVertexBufferData()[i+2];
		if (tempZ > maxZ)
		{
			maxZ = tempZ;
		}
		else if (tempZ < minZ)
		{
			minZ = tempZ;
		}
	}
	return BoundingBox(maxX, maxY, maxZ, minX, minY, minZ);
}