#include "PathTest.h"

#include "../Tester.h"


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
}

