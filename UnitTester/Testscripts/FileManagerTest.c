#pragma once
#include "FileManagerTest.h"

#include <stdlib.h>
#include <stdio.h>

#include "../../SocketFileManager/FileManager.h"
#include "../Tester.h"

#ifdef OSUnix
#define FolderStructure(Path) "../" Path
#elif defined(OSWindows)
#define FolderStructure(Path) Path
#endif

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

	returnCode = OSDirectoryExists(FolderStructure( "TestOSFileFolder/Test"));
	test_fileManager(OSError_NoError, returnCode, "FolderExistTest 1");
	
	returnCode = OSDirectoryExists(FolderStructure("TestOSFileFolder/Test/A"));
	if (!(returnCode == OSError_DirectoryNotFound))
	{
		returnCode = OSDirectoryDelete(FolderStructure("TestOSFileFolder/Test/A"));
		test_fileManager(OSError_NoError, returnCode, "FolderDeleteTest 2.5");
	}
		
	returnCode = OSDirectoryCreate(FolderStructure("TestOSFileFolder/Test/A"));
	test_fileManager(OSError_NoError, returnCode, "FolderCreateTest 2");

	returnCode = OSDirectoryDelete(FolderStructure("TestOSFileFolder/Test/A"));
	test_fileManager(OSError_NoError, returnCode, "FolderDeleteTest 3");

	//Folder Full Test


	returnCode = OSDirectoryExists(FolderStructure("TestOSFileFolder/Test/B/B"));
	if (!(returnCode == OSError_DirectoryNotFound))
	{
		returnCode = OSDirectoryForceDelete(FolderStructure("TestOSFileFolder/Test/B"));
		test_fileManager(OSError_NoError, returnCode, "FolderForceDeleteTest 3.5");
	}

	returnCode = OSDirectoryFullCreate(FolderStructure("TestOSFileFolder/Test/B/B"));
	test_fileManager(OSError_NoError, returnCode, "FolderCreateTest 4");
	
	returnCode = OSDirectoryForceDelete(FolderStructure("TestOSFileFolder/Test/B"));
	test_fileManager(OSError_NoError, returnCode, "FolderForceDeleteTest 5");

	//File test

	returnCode = OSFileExists(FolderStructure("TestOSFileFolder/dontDelete.txt"));
	test_fileManager(OSError_NoError, returnCode, "FileExistTest 6");
	
	returnCode = OSFileExists(FolderStructure("TestOSFileFolder/test.txt"));
	if (!(returnCode == OSError_FileNotFound))
	{
		returnCode = OSFileDelete(FolderStructure("TestOSFileFolder/test.txt"));
		test_fileManager(OSError_NoError, returnCode, "FileDeleteTest 6.5");
	}

	returnCode = OSFileCreate(FolderStructure("TestOSFileFolder/test.txt"));
	test_fileManager(OSError_NoError, returnCode, "FileCreateTest 7");

	returnCode = OSFileDelete(FolderStructure("TestOSFileFolder/test.txt"));
	test_fileManager(OSError_NoError, returnCode, "FileDeleteTest 8");

	//File write /read
	
	returnCode = OSFileForceWrite(FolderStructure("TestOSFileFolder/A/B/C/a.txt"), "Hallo Dennis??!$55&778", WriteMode_Overwrite);
	test_fileManager(OSError_NoError, returnCode, "FileDeleteTest 9");


	char* content = 0;

	returnCode = OSFileRead(FolderStructure("TestOSFileFolder/A/B/C/a.txt"), &content);
	test_string("Hallo Dennis??!$55&778", content, "FileDeleteTest 10");
	test_fileManager(OSError_NoError, returnCode, "FileDeleteTest 11");

	free(content);

	returnCode = OSDirectoryForceDelete(FolderStructure("TestOSFileFolder/A"));
	test_fileManager(OSError_NoError, returnCode, "FileDeleteTest 12");

	returnCode = OSDirectoryForceDelete(FolderStructure("TestOSFileFolder/A"));
	test_fileManager(OSError_FileNotFound, returnCode, "FileDeleteTest 13");

	//

	content = 0;

	returnCode = OSFileRead(FolderStructure("TestOSFileFolder/DontExists/a.txt"), &content);
	test_fileManager(OSError_DirectoryNotFound, returnCode, "FileDeleteTest 14");
}
