#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#include <wchar.h>

#include "OSFileError.h"
#include "Path.h"
#include "../List/List.h"

#ifndef FileManagerInclude
#define FileManagerInclude

/*
 * Function:  OSFileExists_splitParameter
 * --------------------
 * checks if combined(directory + filePath) exists
 * --------------------
 *  returns: OSFileError_NoError
 *	   OSFileError_NoFileExtension
 *	   OSFileError_ExtensionToShort
 *	   OSFileError_FolderNotFound
 *	   OSFileError_FileNotFound
 */
OSFileError OSFileExists_splitParameter(char* directory, char* filePath);

/*
 * Function:  OSFileExists
 * --------------------
 * checks if path exists
 * --------------------
 *  returns: OSFileError_NoError
 *	   OSFileError_NoFileExtension
 *	   OSFileError_ExtensionToShort
 *	   OSFileError_FolderNotFound
 *	   OSFileError_FileNotFound
 */
OSFileError OSFileExists(char* path);

/*
 * Function:  OSFileExistsP
 * --------------------
 * checks if path exists
 * --------------------
 *  returns: OSFileError_NoError
 *	   OSFileError_NoFileExtension
 *	   OSFileError_ExtensionToShort
 *	   OSFileError_FolderNotFound
 *	   OSFileError_FileNotFound
 */
OSFileError OSFileExistsP(Path path);

/*
 * Function:  OSDirectoryExists
 * --------------------
 * checks if directory exists
 * --------------------
 *  returns: OSFileError_NoError
 *	   OSFileError_ContentIsNull
 *	   OSFileError_FolderNotFound
 */
OSFileError OSDirectoryExists(char* directory);

/*
 * Function:  OSFileWriteP
 * --------------------
 * writes content in path
 * --------------------
 *  returns: OSFileError_NoError
 *	  OSFileError_ContentIsNull
 *	  OSFileError_FolderNotFound
 *	  OSFileError_NoFileExtension
 *	  OSFileError_ExtensionToShort
 */
OSFileError OSFileWriteP(Path* path, char* content);

/*
 * Function:  OSFileWrite
 * --------------------
 * writes content in path
 * --------------------
 *  returns: OSFileError_NoError
 *	  OSFileError_ContentIsNull
 *	  OSFileError_FolderNotFound
 *	  OSFileError_NoFileExtension
 *	  OSFileError_ExtensionToShort
 */
OSFileError OSFileWrite(char* path, char* content);

OSFileError OSFileWriteBase(char* path, char* content);

/*
 * Function:  OSFileCreate
 * --------------------
 * Creates a File. If the File exists, it wont be overwritten
 * --------------------
 *  returns: OSFileError_NoError
 *	   OSFileError_FileAlreadyExists
 *	   OSFileError_AccessDenied
 *	   OSFileError_InvalidDirectory
 *	   OSFileError_PathNotFound
 *	   OSFileError_UnknownError
 */
OSFileError OSFileCreate(char* path);

/*
 * Function:  OSFileDelete
 * --------------------
 * Deletes File
 * --------------------
 *  returns: OSFileError_NoError
 *	   OSFileError_AccessDenied
 *	   OSFileError_InvalidDirectory
 *	   OSFileError_PathNotFound
 *	   OSFileError_FileIsCurrentlyInUse
 *	   OSFileError_UnknownError
 */
OSFileError OSFileDelete(char* path);

/*
 * Function:  OSDirectoryCreate
 * --------------------
 * Creates Folder
 * --------------------
 *  returns: OSFileError_NoError
 *	   OSFileError_PathNotFound
 *	   OSFileError_AccessDenied
 *	   OSFileError_FolderAlreadyExists
 *	   OSFileError_InvalidDirectory
 *	   OSFileError_UnknownError
 */
OSFileError OSDirectoryCreate(char* directory);

/*
 * Function:  OSDirectoryFullCreate
 * --------------------
 * Creates Folder hierarchy
 * --------------------
 *  returns: OSFileError_NoError
 *	   OSFileError_PathNotFound
 *	   OSFileError_CallocWentWrong
 *	   OSFileError_AccessDenied
 *	   OSFileError_FolderAlreadyExists
 *	   OSFileError_InvalidDirectory
 *	   OSFileError_UnknownError
 */
OSFileError OSDirectoryFullCreate(char* directory);

/*
 * Function:  OSDirectoryDelete
 * --------------------
 * Deletes a empty directory
 * --------------------
 *  returns: OSFileError_NoError
 *	   OSFileError_DirectoryNotEmpty
 *	   OSFileError_AccessDenied
 *	   OSFileError_InvalidDirectory
 *	   OSFileError_PathNotFound
 *	   OSFileError_UnknownError
 */
OSFileError OSDirectoryDelete(char* directory);

/*
 * Function:  OSDirectoryForceDelete
 * --------------------
 * Deletes the directory and all Content in it
 * --------------------
 *  returns: OSFileError_NoError
 *	   OSFileError_DirectoryNotEmpty
 *	   OSFileError_AccessDenied
 *	   OSFileError_InvalidDirectory
 *	   OSFileError_PathNotFound
 *	   OSFileError_FileIsCurrentlyInUse
 *	   OSFileError_UnknownError
 */
OSFileError OSDirectoryForceDelete(char* directory);

/*
 * Function:  OSListAllFiles
 * --------------------
 * Puts all directories and file names in pathList
 * --------------------
 *  pathList must be set Empty
 *		eg: List a = EMPTYLIST;
 *  
 *	Don`t forget to deconstruct pathList!
 *		eg: PathListDestruction(&pathList);
 * 
 */
void OSListAllFiles(List* pathList, char* directory);

#ifdef OSWindows
static wchar_t* stringToWString(char* string);

static OSFileError WindowsErrorToOSFileError(unsigned long rawError);
#endif

#endif
