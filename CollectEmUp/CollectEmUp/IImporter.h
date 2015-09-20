#pragma once

#include "ImportData.h"

class IImporter
{
public:
	virtual ImportData* loadFromFile( char* filePath ) = 0;
};

