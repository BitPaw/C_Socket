#pragma once


#include <stdlib.h>

#include "../../SocketFileManager/FileManager.h"
#include "../Tester.h"


void test_fileManager(OSError expectedInput, OSError input, char* name)
{
	testPrint((expectedInput == input), OSErrorToString(expectedInput), OSErrorToString(input), "OSError", name);
}



void fileManager_test(char execute)
{
	if (execute == 0)
		return;
	
	//Folder test
	OSError returnCode;

	testPrintHeader("FileManager-Tests");
	
	returnCode = OSDirectoryExists("TestOSFileFolder/Test");
	test_fileManager(OSError_NoError, returnCode, "FolderExistTest 1");
	
	returnCode = OSDirectoryExists("TestOSFileFolder/Test/A");
	if (!(returnCode == OSError_DirectoryNotFound))
	{
		returnCode = OSDirectoryDelete("TestOSFileFolder/Test/A");
		test_fileManager(OSError_NoError, returnCode, "FolderDeleteTest 2.5");
	}
		
	returnCode = OSDirectoryCreate("TestOSFileFolder/Test/A");
	test_fileManager(OSError_NoError, returnCode, "FolderCreateTest 2");

	returnCode = OSDirectoryDelete("TestOSFileFolder/Test/A");
	test_fileManager(OSError_NoError, returnCode, "FolderDeleteTest 3");

	//Folder Full Test


	returnCode = OSDirectoryExists("TestOSFileFolder/Test/B/B");
	if (!(returnCode == OSError_DirectoryNotFound))
	{
		returnCode = OSDirectoryForceDelete("TestOSFileFolder/Test/B");
		test_fileManager(OSError_NoError, returnCode, "FolderForceDeleteTest 3.5");
	}

	returnCode = OSDirectoryFullCreate("TestOSFileFolder/Test/B/B");
	test_fileManager(OSError_NoError, returnCode, "FolderCreateTest 4");
	
	returnCode = OSDirectoryForceDelete("TestOSFileFolder/Test/B");
	test_fileManager(OSError_NoError, returnCode, "FolderForceDeleteTest 5");

	//File test

	returnCode = OSFileExists("TestOSFileFolder/dontDelete.txt");
	test_fileManager(OSError_NoError, returnCode, "FileExistTest 6");
	
	returnCode = OSFileExists("TestOSFileFolder/test.txt");
	if (!(returnCode == OSError_FileNotFound))
	{
		returnCode = OSFileDelete("TestOSFileFolder/test.txt");
		test_fileManager(OSError_NoError, returnCode, "FileDeleteTest 6.5");
	}

	returnCode = OSFileCreate("TestOSFileFolder/test.txt");
	test_fileManager(OSError_NoError, returnCode, "FileCreateTest 7");

	returnCode = OSFileDelete("TestOSFileFolder/test.txt");
	test_fileManager(OSError_NoError, returnCode, "FileDeleteTest 8");

	//File write /read
	
	returnCode = OSFileForceWrite("TestOSFileFolder/A/B/C/a.txt", "Hallo Dennis??!$55&778", WriteMode_Overwrite);
	test_fileManager(OSError_NoError, returnCode, "FileDeleteTest 9");


	char* content = 0;

	returnCode = OSFileRead("TestOSFileFolder/A/B/C/a.txt", &content);
	test_string("Hallo Dennis??!$55&778", content, "FileDeleteTest 10");
	test_fileManager(OSError_NoError, returnCode, "FileDeleteTest 11");

	free(content);

	returnCode = OSDirectoryForceDelete("TestOSFileFolder/A");
	test_fileManager(OSError_NoError, returnCode, "FileDeleteTest 12");

	returnCode = OSDirectoryForceDelete("TestOSFileFolder/A");
	test_fileManager(OSError_FileNotFound, returnCode, "FileDeleteTest 13");

	//

	content = 0;

	returnCode = OSFileRead("TestOSFileFolder/DontExists/a.txt", &content);
	test_fileManager(OSError_DirectoryNotFound, returnCode, "FileDeleteTest 14");
}
