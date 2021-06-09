#pragma once

#include "../../SocketFileManager/Path.h"


#ifndef PathTestInclude
#define PathTestInclude

void test_path(Path* expectedInput, Path* input, char* name);
void path_test(char execute);
void path_ListAllFiles_test(char execute);

#endif
