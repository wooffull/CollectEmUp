#include "ImportData.h"

ImportData::ImportData()
{
	_fileContents = nullptr;
}

ImportData::~ImportData()
{
	if( _fileContents != nullptr )
	{
		delete _fileContents;
	}
}

char* ImportData::getFileContents()
{
	return _fileContents;
}
void ImportData::setFileContents( char* value )
{
	_fileContents = value;
}