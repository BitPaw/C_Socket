#include "PathTest.h"


#include <stdlib.h>

#include "../Tester.h"
#include "../../SocketFileManager/PathList.h"
#include "../../SocketFileManager/FileManager.h"

void test_path(Path* expectedInput, Path* input, char* name)
{
	testPrint(PathCompare(expectedInput, input) == 0,PathToString(expectedInput),PathToString(input),"Path",name);
}


void path_test(char execute)
{
	if(execute == 0)
		return;

	testPrintHeader("Path-Tests");
	
	Path path1, path2;

	//Test 1: Path Test
	path2 = (Path){ strlen("/Users/Test/Desktop/a.txt") ,"/Users/Test/Desktop/a.txt", "/Users/Test/Desktop", "a.txt","a","txt" };
	PathInitialize(&path1, "/Users/Test/Desktop/a.txt");

	test_path(&path1, &path2,"Path Test 1");

	PathDestruction(&path1);

	//Test 2: No File
	path2 = (Path){ strlen("/Users/Test/Desktop"),"/Users/Test/Desktop", "/Users/Test/Desktop", NULL,NULL,NULL };
	PathInitialize(&path1, "/Users/Test/Desktop");

	test_path(&path1, &path2, "Path Test 2 [No File]");

	PathDestruction(&path1);

	//Test 3: No Directory

	path2 = (Path){ strlen("a.txt"),"a.txt", NULL ,"a.txt","a","txt" };
	PathInitialize(&path1, "a.txt");

	test_path(&path1, &path2, "Path Test 3 [No Directory]");

	PathDestruction(&path1);

	//Test 4: No Directory && No File

	path2 = (Path){ 0,NULL, NULL ,NULL,NULL,NULL };
	PathInitialize(&path1, NULL);

	test_path(&path1, &path2, "Path Test 4 [NULL]");

	PathDestruction(&path1);

	//Test 5: No Directory && No File 2

	path2 = (Path){ 0 };
	PathInitialize(&path1, "");

	test_path(&path1, &path2, "Path Test 5 [NULL 2]");

	PathDestruction(&path1);

	//Test 6: Memcopy

	char* stringPath = calloc(27,sizeof(char));
	strcpy_s(stringPath,27 , "/Users/Test/Desktop/a.txt");
	
	path2 = (Path){ strlen("/Users/Test/Desktop/a.txt") ,"/Users/Test/Desktop/a.txt", "/Users/Test/Desktop", "a.txt","a","txt" };
	PathInitialize(&path1, stringPath);

	free(stringPath);
	
	test_path(&path1, &path2, "Path Test 6 [Pointer]");

	PathDestruction(&path1);

	
}

void path_ListAllFiles_test(char execute)
{
	if (execute == 0)
		return;
	
	testPrintHeader("ListAllFiles-Tests");
	
	Path testPath1, testPath2;
	List test;
	
	//List all Files

	FM_ListAllFiles(&test, "TestFileManagerFolder/*");

	test_int(2, test.size, "ListAllFiles-Test 1 [SizeOfList]");

	PathInitialize(&testPath1, "TestFileManagerFolder/Test");
	PathInitialize(&testPath2, "TestFileManagerFolder/dontDelete.txt");
	
	if(test.size == 2)
	{
		test_path(&testPath1, test.content[1], "ListAllFiles-Test 2 Path1");
		test_path(&testPath2, test.content[0], "ListAllFiles-Test 3 Path2");
	}
	
	PathDestruction(&testPath1);
	PathDestruction(&testPath2);

	PathListDestruction(&test);

	// Test without '/*'

	FM_ListAllFiles(&test, "TestFileManagerFolder");

	test_int(2, test.size, "ListAllFiles-Test 4 [SizeOfList]");

	PathInitialize(&testPath1, "TestFileManagerFolder/Test");
	PathInitialize(&testPath2, "TestFileManagerFolder/dontDelete.txt");

	if (test.size == 2)
	{
		test_path(&testPath1, test.content[1], "ListAllFiles-Test 5 Path1");
		test_path(&testPath2, test.content[0], "ListAllFiles-Test 6 Path2");
	}

	PathDestruction(&testPath1);
	PathDestruction(&testPath2);

	PathListDestruction(&test);
	
	// Test Empty dic

	FM_ListAllFiles(&test, "TestFileManagerFolder/Test");

	test_int(0, test.size, "ListAllFiles-Test 7 [Empty Folder]");

	PathListDestruction(&test);

	
}
