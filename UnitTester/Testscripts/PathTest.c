#include "PathTest.h"


#include <stdlib.h>

#include "../Tester.h"
#include "../../SocketFileManager/PathList.h"
#include "../../SocketFileManager/FileManager.h"

#ifdef OSUnix
#define FolderStructure(Path) "../" Path
#elif defined(OSWindows)
#define FolderStructure(Path) Path
#endif

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
    memcpy(stringPath,"/Users/Test/Desktop/a.txt",26);

	path2 = (Path){ strlen("/Users/Test/Desktop/a.txt") ,"/Users/Test/Desktop/a.txt", "/Users/Test/Desktop", "a.txt","a","txt" };
	PathInitialize(&path1, stringPath);

	free(stringPath);
	
	test_path(&path1, &path2, "Path Test 6 [Pointer]");

	PathDestruction(&path1);

	//Test 7: Test ../a.txt

    path2 = (Path){ strlen("../a.txt"),"../a.txt", ".." ,"a.txt","a","txt" };
    PathInitialize(&path1, "../a.txt");

    test_path(&path1, &path2, "Path Test 7 [../a.txt Directory]");

    PathDestruction(&path1);

    //Test 8: Test ../Test

    path2 = (Path){ strlen("../Test"),"../Test", "../Test" ,NULL,NULL,NULL };
    PathInitialize(&path1, "../Test");

    test_path(&path1, &path2, "Path Test 8 [../Test Directory]");

    PathDestruction(&path1);

}

void path_ListAllFiles_test(char execute)
{
	if (execute == 0)
		return;
	
	testPrintHeader("ListAllFiles-Tests");
	
	Path testPath1, testPath2;
	List test = EMPTYLIST;
	
	//List all Files

	OSListAllFiles(&test, FolderStructure("TestOSFileFolder"));

	test_int(3, test.size, "ListAllFiles-Test 1 [SizeOfList]");

	PathInitialize(&testPath1, FolderStructure("TestOSFileFolder/Test"));
	PathInitialize(&testPath2, FolderStructure("TestOSFileFolder/dontDelete.txt"));
	
	if(test.size == 3)
	{
	    if(testPath1.fullPath == test.content[1]){
            test_path(&testPath1, test.content[1], "ListAllFiles-Test 2 Path1");
            test_path(&testPath2, test.content[0], "ListAllFiles-Test 3 Path2");
	    }else{
            test_path(&testPath1, test.content[0], "ListAllFiles-Test 2 Path1");
            test_path(&testPath2, test.content[1], "ListAllFiles-Test 3 Path2");
	    }

	}
	
	PathDestruction(&testPath1);
	PathDestruction(&testPath2);

	PathListDestruction(&test);

	// Test without '/*'

	test = EMPTYLIST;
	
	OSListAllFiles(&test, FolderStructure("TestOSFileFolder"));

	test_int(3, test.size, "ListAllFiles-Test 4 [SizeOfList]");

	PathInitialize(&testPath1, FolderStructure("TestOSFileFolder/Test"));
	PathInitialize(&testPath2, FolderStructure("TestOSFileFolder/dontDelete.txt"));

	if (test.size == 3)
	{
        if(testPath1.fullPath == test.content[1]){
            test_path(&testPath1, test.content[1], "ListAllFiles-Test 5 Path1");
            test_path(&testPath2, test.content[0], "ListAllFiles-Test 6 Path2");
        }
        else{
            test_path(&testPath1, test.content[0], "ListAllFiles-Test 5 Path1");
            test_path(&testPath2, test.content[1], "ListAllFiles-Test 6 Path2");
        }

	}

	PathDestruction(&testPath1);
	PathDestruction(&testPath2);

	PathListDestruction(&test);
	
	// Test Empty dic

	test = EMPTYLIST;

	OSDirectoryCreate(FolderStructure("TestOSFileFolder/Temp"));
	
	OSListAllFiles(&test, FolderStructure("TestOSFileFolder/Temp"));

	test_int(0, test.size, "ListAllFiles-Test 7 [Empty Folder]");

	PathListDestruction(&test);
	
	OSDirectoryDelete(FolderStructure("TestOSFileFolder/Temp"));
	
}
