#pragma once

#define OSTODO OSFileError_NotImplemented

#ifndef OSFileErrorInclude
#define OSFileErrorInclude

typedef enum OSFileError_
{
	OSFileError_NoError,

	OSFileError_FolderNotFound,
	OSFileError_FolderAlreadyExists,

	OSFileError_FileIsCurrentlyInUse,
	OSFileError_FileNotFound,
	OSFileError_FileAlreadyExists,
	OSFileError_InvalidDirectory,

	OSFileError_DirectoryNotEmpty,

	OSFileError_PathNotFound,

	OSFileError_AccessDenied,
	
	OSFileError_NoFileExtension,
	OSFileError_ExtensionToShort,

	OSFileError_CallocWentWrong,
	
	OSFileError_ContentIsNull,

	OSFileError_WrittenContentIsCorrupted,

	OSFileError_UnknownError,

	OSFileError_NotImplemented

}OSFileError;

const char* OSFileErrorToString(OSFileError state);

#endif
