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

	char compareValue = PathCompare(expectedInput, input);
	
	if (compareValue != 0)
		printf("[X] Test failed:\n   -Expected input '%s', actual '%s' ERROR_CODE[%i]\n", input->fullPath, expectedInput->fullPath, compareValue);
	else
		printf("    Test completed\n");

	printf("------------------------------\n");
}


void PathTest()
{
	Path path1,path2;

	//Test 1: Path Test
	path2 = (Path){ strlen("/Users/Test/Desktop/a.txt") ,"/Users/Test/Desktop/a.txt", "/Users/Test/Desktop", "a.txt","a","txt" };
	PathInitialize(&path1, "/Users/Test/Desktop/a.txt");

	test_path(&path1, &path2);

	PathDestruction(&path1);
	
	//Test 2: No File
	path2 = (Path){ strlen("/Users/Test/Desktop"),"/Users/Test/Desktop", "/Users/Test/Desktop", NULL,NULL,NULL};
	PathInitialize(&path1, "/Users/Test/Desktop");
	
	test_path(&path1, &path2);
	
	PathDestruction(&path1);

	//Test 3: No Directory
	
	path2 = (Path){ strlen("a.txt"),"a.txt", NULL ,"a.txt","a","txt" };
	PathInitialize(&path1, "a.txt");

	test_path(&path1, &path2);

	PathDestruction(&path1);

	//Test 4: No Directory && No File

	path2 = (Path){ 0,NULL, NULL ,NULL,NULL,NULL };
	PathInitialize(&path1, NULL);

	test_path(&path1, &path2);

	PathDestruction(&path1);
	
	//Test 5: No Directory && No File 2

	path2 = (Path){ 0 };
	PathInitialize(&path1, "");

	test_path(&path1, &path2);

	PathDestruction(&path1);
}

int main()
{
	printf("---------------------------------\n");
	printf(" [PATH] Unit Tests:\n");
	printf("---------------------------------\n");

	PathTest();

	printf("\n\n");

	printf("---------------------------------\n");
	printf(" [File or Dic exists] Unit Tests:\n");
	printf("---------------------------------\n");

	Path testPath;
	PathInitialize(&testPath, "AAA/Test/a.txt");
	
	//FM_WriteInFile(&testPath,"Lukkkkkkas");

	//const FileManagerErrorCode returnCode = FM_CreateFile("C:/Users/Merdo/Desktop/a.txt");
	const FileManagerErrorCode returnCode2 = FM_DeleteFile("C:/Users/Merdo/Desktop/a.docx");
	
	//printf("create: %s\n", FileManagerErrorCodeToString(returnCode));
	printf("delete: %s\n", FileManagerErrorCodeToString(returnCode2));

	printf("\n\n");
	
#ifdef OSWindows
	system("pause");
#else
	printf("Terminated\n");
#endif
}
