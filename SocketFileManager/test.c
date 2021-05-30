#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Path.h"
#include "FileManagerErrorCodes.h"
#include "FileManager.h"

unsigned int testCount;

void test_int(int expectedInput, int input)
{
	printf("\n------ Test [%i] [INT] --------\n", testCount++);
	
	if (expectedInput != input)
		printf("[X] Test failed:\n   -Expected input '%i', actual '%i'\n", input, expectedInput);
	else
		printf("    Test completed\n");
	
	printf("------------------------------\n");
}

void test_string(char* expectedInput, char* input)
{
	printf("\n------ Test [%i] [String] -----\n", testCount++);

	if (memcmp(input,expectedInput,sizeof(char)* (strlen(input)< strlen(expectedInput))? strlen(input) : strlen(expectedInput)))
		printf("[X] Test failed:\n   -Expected input '%s', actual '%s'\n", input, expectedInput);
	else
		printf("    Test completed\n");

	printf("------------------------------\n");
}

void test_path(Path* expectedInput, Path* input)
{
	printf("\n------ Test [%i] [Path] -------\n", testCount++);

	if (PathCompare(expectedInput, input) != 0)
		printf("[X] Test failed:\n   -Expected input '%s', actual '%s'\n", input->fullPath, expectedInput->fullPath);
	else
		printf("    Test completed\n");

	printf("------------------------------\n");
}


int main()
{
	printf("---------------------------------\n");
	printf(" Unit Tests:\n");
	printf("---------------------------------\n");


	test_int(0,0);
	test_int(1, 0);
	test_string("test", "test");
	test_string("test", "test123");

	
	Path a,b;
	PathInitialize(&a, "C:/Users/Merdo/Desktop/aaa.txt");
	PathInitialize(&b, "C:/Users/Merdo/Desop/aaa.txt");

	test_path(&a, &b);
	
	PathDestruction(&a);
	PathDestruction(&b);
	
	printf("\n\n\n");

	
#ifdef OSWindows
	system("pause");
#else
	printf("Terminated\n");
#endif
}
