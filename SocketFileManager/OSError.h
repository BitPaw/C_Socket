#pragma once

#define OSTODO OSError_NotImplemented

#ifndef OSErrorInclude
#define OSErrorInclude

typedef enum OSError_
{
	OSError_NoError,

	OSError_DirectoryNotFound,
	OSError_FolderAlreadyExists,

	OSError_FileIsCurrentlyInUse,
	OSError_FileNotFound,
	OSError_FileAlreadyExists,
	OSError_FileToBig,
	OSError_FileNameToLong,
	OSError_FileNameInvalid,
	OSError_DirectoryInvalid,

	OSError_DirectoryNotEmpty,

	OSError_PathNotFound,

	OSError_AccessDenied,
	
	OSError_NoFileExtension,
	OSError_ExtensionToShort,

	OSError_CallocWentWrong,
	
	OSError_ContentIsNull,

	OSError_WrittenContentIsCorrupted,
	
	OSError_ParameterIsNull,
	OSError_ParameterInvalid,
	
	OSError_UnknownError,



	OSError_NotImplemented

}OSError;

const char* OSErrorToString(OSError state);

#endif
