#include "FileImporter.h"

FileImporter::FileImporter()
{
}

FileImporter::~FileImporter()
{
}

ImportData* FileImporter::loadFromFile( char* filePath )
{
	std::ifstream inFile( filePath, std::ios::binary );

	if( inFile.is_open() )
	{
		inFile.seekg( 0, std::ios::end );
		int length = (int)inFile.tellg();

		inFile.seekg( 0, std::ios::beg );

		char* fileContents = new char[length + 1];
		inFile.read( fileContents, length );

		fileContents[length] = 0;

		// Close the file and clear up memory that was used
		// to hold the file contents
		inFile.close();

		FileImportData* importData = new FileImportData();
		importData->setFileContents( fileContents );
		
		return importData;
	}
	else
	{
		return nullptr;
	}
}