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

#ifndef FileManagerInclude
#define FileManagerInclude

FileManagerErrorCode FM_DoesFileExist_FULL(char* directory, char* filePath);
FileManagerErrorCode FM_DoesFileExist(char* path);

FileManagerErrorCode FM_WriteInFile(Path* path, char * content);


FileManagerErrorCode FM_CreateFile(char* path);

FileManagerErrorCode FM_DeleteFile(char* path);

/// <summary>
/// Creates the last folder of directory.
/// </summary>
/// <param name="directory"></param>
/// <returns>
/// </returns>
FileManagerErrorCode FM_CreateDir(char* directory);

/// <summary>
/// Creates the full directory.
/// </summary>
/// <param name="directory"></param>
/// <returns>
/// </returns>
FileManagerErrorCode FM_CreateFullDir(char* directory);

FileManagerErrorCode FM_DeleteDir(char* directory);

FileManagerErrorCode FM_ForceDeleteDir(char* directory);

Path* FM_ListAllFiles(char* directory);

#ifdef OSWindows
static wchar_t* stringToWString(char* string);

static FileManagerErrorCode WindowsErrorToFileManagerError(unsigned long rawError);
#endif

#endif
