#pragma once

#ifndef FileManagerErrorCodeInclude
#define FileManagerErrorCodeInclude

typedef enum FileManagerErrorCode_
{
	FileManager_NoError,

	FileManager_FolderNotFound,
	FileManager_FileNotFound,
	
	FileManager_NoFileExtension,
	FileManager_ExtensionToShort

}FileManagerErrorCode;

const char* FileManagerErrorCodeToString(FileManagerErrorCode state);

#endif
