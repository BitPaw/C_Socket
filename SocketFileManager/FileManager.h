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

FileManagerErrorCode DoesFileExist_FULL(char* path, char* file);
FileManagerErrorCode DoesFileExist(char* path);

#endif
