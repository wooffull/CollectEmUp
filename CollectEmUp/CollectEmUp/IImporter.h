#pragma once

#include "IImportData.h"

class IImporter
{
public:
	virtual ~IImporter() {}

	virtual void import( IImportData data ) = 0;
};

