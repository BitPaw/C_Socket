#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#include <wchar.h>

#include "OSError.h"
#include "Path.h"
#include "../List/List.h"

#ifndef FileManagerInclude
#define FileManagerInclude

#define WriteMode_Overwrite 0
#define WriteMode_AddToEnd 1

/*
 * Function:  OSFileExists_splitParameter
 * --------------------
 * checks if combined(directory + filePath) exists
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_NoFileExtension
 *	   OSError_ExtensionToShort
 *	   OSError_DirectoryNotFound
 *	   OSError_FileNotFound
 */
OSError OSFileExists_splitParameter(char* directory, char* filePath);

/*
 * Function:  OSFileExists
 * --------------------
 * checks if path exists
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_NoFileExtension
 *	   OSError_ExtensionToShort
 *	   OSError_DirectoryNotFound
 *	   OSError_FileNotFound
 */
OSError OSFileExists(char* path);

/*
 * Function:  OSFileExistsP
 * --------------------
 * checks if path exists
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_NoFileExtension
 *	   OSError_ExtensionToShort
 *	   OSError_DirectoryNotFound
 *	   OSError_FileNotFound
 */
OSError OSFileExistsP(Path* path);

/*
 * Function:  OSDirectoryExists
 * --------------------
 * checks if directory exists
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_ContentIsNull
 *	   OSError_DirectoryNotFound
 */
OSError OSDirectoryExists(char* directory);

/*
 * Function:  OSDirectoryExistsP
 * --------------------
 * checks if path->directory exists
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_ContentIsNull
 *	   OSError_DirectoryNotFound
 */
OSError OSDirectoryExistsP(Path* path);

/*
 * Function:  OSFileForceWrite
 * --------------------
 * writes content in path, if file or directory doesn't exists, they will be created
 *
 * writeMode = [WriteMode_Overwrite | WriteMode_AddToEnd]
 * --------------------
 *  returns: OSError_NoError
 *    OSError_ParameterIsNull
 *	  OSError_ParameterInvalid
 *	  OSError_ContentIsNull
 *	  OSError_DirectoryNotFound
 *	  OSError_CallocWentWrong
 *	  OSError_AccessDenied
 *	  OSError_FileToBig
 *	  OSError_FileNameInvalid
 *	  OSError_FileNameToLong
 *	  OSError_NoFileExtension
 *	  OSError_ExtensionToShort
 *	  OSError_UnknownError
 */
OSError OSFileForceWrite(char* path, char* content, char writeMode);

/*
 * Function:  OSFileForceWriteP
 * --------------------
 * writes content in path, if file or directory doesn't exists, they will be created
 *
 * writeMode = [WriteMode_Overwrite | WriteMode_AddToEnd] 
 * --------------------
 *  returns: OSError_NoError
 *    OSError_ParameterIsNull
 *	  OSError_ParameterInvalid
 *	  OSError_ContentIsNull
 *	  OSError_DirectoryNotFound
 *	  OSError_CallocWentWrong
 *	  OSError_AccessDenied
 *	  OSError_FileToBig
 *	  OSError_FileNameInvalid
 *	  OSError_FileNameToLong
 *	  OSError_NoFileExtension
 *	  OSError_ExtensionToShort
 *	  OSError_UnknownError
 */
OSError OSFileForceWriteP(Path* path, char* content, char writeMode);

/*
 * Function:  OSFileWriteBase
 * --------------------
 * Writes in a existing/non existing File. Directory must exist. (Better use OSFileForceWrite)
 * --------------------
 *  returns: OSError_NoError
 *    OSError_ParameterIsNull
 *	  OSError_ParameterInvalid
 *	  OSError_ContentIsNull
 *	  OSError_DirectoryNotFound
 *	  OSError_CallocWentWrong
 *	  OSError_AccessDenied
 *	  OSError_FileToBig
 *	  OSError_FileNameInvalid
 *	  OSError_FileNameToLong
 *	  OSError_NoFileExtension
 *	  OSError_ExtensionToShort
 *	  OSError_UnknownError
 */
OSError OSFileWriteBase(char* path, char* content, char writeMode);

/*
 * Function:  OSFileWriteBaseP
 * --------------------
 * Writes in a existing/non existing File. Directory must exist. (Better use OSFileForceWriteP)
 * --------------------
 *  returns: OSError_NoError
 *    OSError_ParameterIsNull
 *	  OSError_ParameterInvalid
 *	  OSError_ContentIsNull
 *	  OSError_DirectoryNotFound
 *	  OSError_CallocWentWrong
 *	  OSError_AccessDenied
 *	  OSError_FileToBig
 *	  OSError_FileNameInvalid
 *	  OSError_FileNameToLong
 *	  OSError_NoFileExtension
 *	  OSError_ExtensionToShort
 *	  OSError_UnknownError
 */
OSError OSFileWriteBaseP(Path* path, char* content, char writeMode);

/*
 * Function:  OSFileRead
 * --------------------
 * Will read content in the pathFile. Don't forget to free readContent, if this function returned OSError_NoError  
 * --------------------
 *  returns: OSError_NoError
 *    OSError_ParameterIsNull
 *	  OSError_ParameterInvalid
 *	  OSError_DirectoryNotFound
 *	  OSError_CallocWentWrong
 *	  OSError_AccessDenied
 *	  OSError_NoFileExtension
 *	  OSError_ExtensionToShort
 *	  OSError_UnknownError
 */
OSError OSFileRead(char* path, char** readContent);

/*
 * Function:  OSFileReadP
 * --------------------
 * Will read content in the pathFile. Don't forget to free readContent, if this function returned OSError_NoError
 * --------------------
 *  returns: OSError_NoError
 *    OSError_ParameterIsNull
 *	  OSError_ParameterInvalid
 *	  OSError_DirectoryNotFound
 *	  OSError_CallocWentWrong
 *	  OSError_AccessDenied
 *	  OSError_NoFileExtension
 *	  OSError_ExtensionToShort
 *	  OSError_UnknownError
 */
OSError OSFileReadP(Path* path, char** readContent);

/*
 * Function:  OSFileCreate
 * --------------------
 * Creates a File. If the File exists, it wont be overwritten
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_FileAlreadyExists
 *	   OSError_AccessDenied
 *	   OSError_DirectoryInvalid
 *	   OSError_PathNotFound
 *	   OSError_UnknownError
 */
OSError OSFileCreate(char* path);

/*
 * Function:  OSFileCreateP
 * --------------------
 * Creates a File. If the File exists, it wont be overwritten
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_FileAlreadyExists
 *	   OSError_AccessDenied
 *	   OSError_DirectoryInvalid
 *	   OSError_PathNotFound
 *	   OSError_UnknownError
 */
OSError OSFileCreateP(Path* path);

/*
 * Function:  OSFileDelete
 * --------------------
 * Deletes File
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_AccessDenied
 *	   OSError_DirectoryInvalid
 *	   OSError_PathNotFound
 *	   OSError_FileIsCurrentlyInUse
 *	   OSError_UnknownError
 */
OSError OSFileDelete(char* path);

/*
 * Function:  OSFileDeleteP
 * --------------------
 * Deletes File
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_AccessDenied
 *	   OSError_DirectoryInvalid
 *	   OSError_PathNotFound
 *	   OSError_FileIsCurrentlyInUse
 *	   OSError_UnknownError
 */
OSError OSFileDeleteP(Path* path);

/*
 * Function:  OSDirectoryCreate
 * --------------------
 * Creates Folder
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_PathNotFound
 *	   OSError_AccessDenied
 *	   OSError_FolderAlreadyExists
 *	   OSError_DirectoryInvalid
 *	   OSError_UnknownError
*/
OSError OSDirectoryCreate(char* directory);

/*
 * Function:  OSDirectoryCreate
 * --------------------
 * Creates Folder
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_PathNotFound
 *	   OSError_AccessDenied
 *	   OSError_FolderAlreadyExists
 *	   OSError_DirectoryInvalid
 *	   OSError_UnknownError
*/
OSError OSDirectoryCreateP(Path* path);

/*
 * Function:  OSDirectoryFullCreate
 * --------------------
 * Creates Folder hierarchy
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_PathNotFound
 *	   OSError_CallocWentWrong
 *	   OSError_AccessDenied
 *	   OSError_FolderAlreadyExists
 *	   OSError_DirectoryInvalid
 *	   OSError_UnknownError
 */
OSError OSDirectoryFullCreate(char* directory);

/*
 * Function:  OSDirectoryFullCreateP
 * --------------------
 * Creates Folder hierarchy
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_PathNotFound
 *	   OSError_CallocWentWrong
 *	   OSError_AccessDenied
 *	   OSError_FolderAlreadyExists
 *	   OSError_DirectoryInvalid
 *	   OSError_UnknownError
 */
OSError OSDirectoryFullCreateP(Path* path);

/*
 * Function:  OSDirectoryDelete
 * --------------------
 * Deletes a empty directory
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_DirectoryNotEmpty
 *	   OSError_AccessDenied
 *	   OSError_DirectoryInvalid
 *	   OSError_PathNotFound
 *	   OSError_UnknownError
 */
OSError OSDirectoryDelete(char* directory);

/*
 * Function:  OSDirectoryDeleteP
 * --------------------
 * Deletes a empty directory
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_DirectoryNotEmpty
 *	   OSError_AccessDenied
 *	   OSError_DirectoryInvalid
 *	   OSError_PathNotFound
 *	   OSError_UnknownError
 */
OSError OSDirectoryDeleteP(Path* path);

/*
 * Function:  OSDirectoryForceDelete
 * --------------------
 * Deletes the directory and all Content in it
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_DirectoryNotEmpty
 *	   OSError_AccessDenied
 *	   OSError_DirectoryInvalid
 *	   OSError_PathNotFound
 *	   OSError_FileIsCurrentlyInUse
 *	   OSError_UnknownError
 */
OSError OSDirectoryForceDelete(char* directory);

/*
 * Function:  OSDirectoryForceDeleteP
 * --------------------
 * Deletes the directory and all Content in it
 * --------------------
 *  returns: OSError_NoError
 *	   OSError_DirectoryNotEmpty
 *	   OSError_AccessDenied
 *	   OSError_DirectoryInvalid
 *	   OSError_PathNotFound
 *	   OSError_FileIsCurrentlyInUse
 *	   OSError_UnknownError
 */
OSError OSDirectoryForceDeleteP(Path* path);

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
OSError OSListAllFiles(List* pathList, char* directory);

static OSError ErrnoErrorToOSError(unsigned int errnoAsInt);

#ifdef OSWindows
static wchar_t* stringToWString(char* string);

static OSError windowsErrorToOSError(unsigned long rawError);
#endif

#endif
