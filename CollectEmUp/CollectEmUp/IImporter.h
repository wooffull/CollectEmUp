#pragma once

#include "ImportData.h"

class IImporter
{
public:
	virtual ImportData* loadFromFile( const char* filePath ) = 0;
};

