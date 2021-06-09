#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

#ifndef OSFileTestInclude
#define OSFileTestInclude

void fileManager_test(char execute);


#endif
