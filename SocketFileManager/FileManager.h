#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#include <wchar.h>

#include "FileManagerErrorCodes.h"
#include "Path.h"
#include "../List/List.h"

#ifndef FileManagerInclude
#define FileManagerInclude

/*
 * Function:  FM_FileExists_split
 * --------------------
 * checks if (directory + filePath) exists
 * --------------------
 *  returns: FileManager_NoError
 *	   FileManager_NoFileExtension
 *	   FileManager_ExtensionToShort
 *	   FileManager_FolderNotFound
 *	   FileManager_FileNotFound
 */
FileManagerErrorCode FM_FileExists_spit(char* directory, char* filePath);

/*
 * Function:  FM_FileExists
 * --------------------
 * checks if path exists
 * --------------------
 *  returns: FileManager_NoError
 *	   FileManager_NoFileExtension
 *	   FileManager_ExtensionToShort
 *	   FileManager_FolderNotFound
 *	   FileManager_FileNotFound
 */
FileManagerErrorCode FM_FileExistsA(char* path);

//FileManagerErrorCode FM_FileExists_path(Path path);

/*
 * Function:  FM_DirExists
 * --------------------
 * checks if directory exists
 * --------------------
 *  returns: FileManager_NoError
 *	   FileManager_ContentIsNull
 *	   FileManager_FolderNotFound
 */
FileManagerErrorCode FM_DirExists(char* directory);

//FileManagerErrorCode FM_DirExists(Path directory);

/*
 * Function:  FM_FileWrite
 * --------------------
 * writes content in path
 * --------------------
 *  returns: FileManager_NoError
 *	  FileManager_ContentIsNull
 *	  FileManager_FolderNotFound
 *	  FileManager_NoFileExtension
 *	  FileManager_ExtensionToShort
 */
FileManagerErrorCode FM_FileWrite(Path* path, char* content);

FileManagerErrorCode FM_FileWriteBase(char* path, char* content);

/*
 * Function:  FM_FileCreate
 * --------------------
 * Creates a File. If the File exists, it wont be overwritten
 * --------------------
 *  returns: FileManager_NoError
 *	   FileManager_FileAlreadyExists
 *	   FileManager_AccessDenied
 *	   FileManager_InvalidDirectory
 *	   FileManager_PathNotFound
 *	   FileManager_UnknownError
 */
FileManagerErrorCode FM_FileCreate(char* path);

/*
 * Function:  FM_FileDelete
 * --------------------
 * Deletes File
 * --------------------
 *  returns: FileManager_NoError
 *	   FileManager_AccessDenied
 *	   FileManager_InvalidDirectory
 *	   FileManager_PathNotFound
 *	   FileManager_FileIsCurrentlyInUse
 *	   FileManager_UnknownError
 */
FileManagerErrorCode FM_FileDelete(char* path);

/*
 * Function:  FM_DirCreate
 * --------------------
 * Creates Folder
 * --------------------
 *  returns: FileManager_NoError
 *	   FileManager_PathNotFound
 *	   FileManager_AccessDenied
 *	   FileManager_FolderAlreadyExists
 *	   FileManager_InvalidDirectory
 *	   FileManager_UnknownError
 */
FileManagerErrorCode FM_DirCreate(char* directory);

/*
 * Function:  FM_DirFullCreate
 * --------------------
 * Creates Folder hierarchy
 * --------------------
 *  returns: FileManager_NoError
 *	   FileManager_PathNotFound
 *	   FileManager_CallocWentWrong
 *	   FileManager_AccessDenied
 *	   FileManager_FolderAlreadyExists
 *	   FileManager_InvalidDirectory
 *	   FileManager_UnknownError
 */
FileManagerErrorCode FM_DirFullCreate(char* directory);

/*
 * Function:  FM_DirDelete
 * --------------------
 * Deletes a empty directory
 * --------------------
 *  returns: FileManager_NoError
 *	   FileManager_DirectoryNotEmpty
 *	   FileManager_AccessDenied
 *	   FileManager_InvalidDirectory
 *	   FileManager_PathNotFound
 *	   FileManager_UnknownError
 */
FileManagerErrorCode FM_DirDelete(char* directory);

/*
 * Function:  FM_DirForceDelete
 * --------------------
 * Deletes the directory and all Content in it
 * --------------------
 *  returns: FileManager_NoError
 *	   FileManager_DirectoryNotEmpty
 *	   FileManager_AccessDenied
 *	   FileManager_InvalidDirectory
 *	   FileManager_PathNotFound
 *	   FileManager_FileIsCurrentlyInUse
 *	   FileManager_UnknownError
 */
FileManagerErrorCode FM_DirForceDelete(char* directory);

/*
 * Function:  FM_ListAllFiles
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
void FM_ListAllFiles(List* pathList, char* directory);

#ifdef OSWindows
static wchar_t* stringToWString(char* string);

static FileManagerErrorCode WindowsErrorToFileManagerError(unsigned long rawError);
#endif

#endif
