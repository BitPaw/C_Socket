#pragma once

#define FM_TODO FileManager_NotImplemented

#ifndef FileManagerErrorCodeInclude
#define FileManagerErrorCodeInclude

typedef enum FileManagerErrorCode_
{
	FileManager_NoError,

	FileManager_FolderNotFound,
	FileManager_FolderAlreadyExists,

	FileManager_FileIsCurrentlyInUse,
	FileManager_FileNotFound,
	FileManager_FileAlreadyExists,
	FileManager_InvalidDirectory,

	FileManager_DirectoryNotEmpty,

	FileManager_PathNotFound,

	FileManager_AccessDenied,
	
	FileManager_NoFileExtension,
	FileManager_ExtensionToShort,

	FileManager_CallocWentWrong,
	
	FileManager_ContentIsNull,

	FileManager_WrittenContentIsCorrupted,

	FileManager_UnknownError,

	FileManager_NotImplemented

}FileManagerErrorCode;

const char* FileManagerErrorCodeToString(FileManagerErrorCode state);

#endif
