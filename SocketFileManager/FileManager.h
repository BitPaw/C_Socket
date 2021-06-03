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

FileManagerErrorCode FM_FileExists_split(char* directory, char* filePath);
FileManagerErrorCode FM_FileExists(char* path);

FileManagerErrorCode FM_DirExists(char* directory);

FileManagerErrorCode FM_FileWrite(Path* path, char * content);


FileManagerErrorCode FM_FileCreate(char* path);

FileManagerErrorCode FM_FileDelete(char* path);

/// <summary>
/// Creates the last folder of directory.
/// </summary>
/// <param name="directory"></param>
/// <returns>
/// </returns>
FileManagerErrorCode FM_DirCreate(char* directory);

/// <summary>
/// Creates the full directory.
/// </summary>
/// <param name="directory"></param>
/// <returns>
/// </returns>
FileManagerErrorCode FM_DirFullCreate(char* directory);

FileManagerErrorCode FM_DirDelete(char* directory);

FileManagerErrorCode FM_DirForceDelete(char* directory);

void FM_ListAllFiles(List* emptyList, char* directory);

#ifdef OSWindows
static wchar_t* stringToWString(char* string);

static FileManagerErrorCode WindowsErrorToFileManagerError(unsigned long rawError);
#endif

#endif
