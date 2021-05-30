#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

#include "FileManagerErrorCodes.h"

#ifndef FileManagerInclude
#define FileManagerInclude

FileManagerErrorCode DoesFileExist_FULL(char* directory, char* filePath);
FileManagerErrorCode DoesFileExist(char* path);

FileManagerErrorCode WriteInFile(char* directory, char* filePath, char * content);

/// <summary>
/// Creates the last folder of directory.
/// </summary>
/// <param name="directory"></param>
/// <returns>
///	 0: NO_ERROR
///	 1: ERROR_ALREADY_EXISTS
///	 2: ERROR_PATH_NOT_FOUND
///	 3: ERROR_ACCESS_DENIED
///	 9: CALLOC_WENT_WRONG
///	-1: UNKNOWN_ERROR
/// </returns>
char CreateDir(char* directory);

/// <summary>
/// Creates the full directory.
/// </summary>
/// <param name="directory"></param>
/// <returns>
///	 0: NO_ERROR
///	 1: ERROR_ALREADY_EXISTS
///	 2: ERROR_PATH_NOT_FOUND
///	 3: ERROR_ACCESS_DENIED
///	 9: CALLOC_WENT_WRONG
///	-1: UNKNOWN_ERROR
/// </returns>
char CreateFullDir(char* directory);

#endif
