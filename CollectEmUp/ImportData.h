#pragma once

class ImportData
{
public:
	ImportData();
	virtual ~ImportData();

	virtual char* getFileContents();
	virtual void setFileContents( char* value );

private:
	char* _fileContents;
};

