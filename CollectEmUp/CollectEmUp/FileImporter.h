#pragma once

#include <iostream>
#include <fstream>
#include "IImporter.h"
#include "ImportData.h"
#include "FileImportData.h"

class FileImporter :
	public IImporter
{
public:
	FileImporter();
	virtual ~FileImporter();

	virtual ImportData* loadFromFile( const char* filePath );
};

