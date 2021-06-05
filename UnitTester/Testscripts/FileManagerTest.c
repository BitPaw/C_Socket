#pragma once


#include "../../SocketFileManager/FileManager.h"
#include "../Tester.h"


void test_fileManager(OSFileError expectedInput, OSFileError input, char* name)
{
	testPrint((expectedInput == input), OSFileErrorToString(expectedInput), OSFileErrorToString(input), "OSFileError", name);
}



void fileManager_test(char execute)
{
	if (execute == 0)
		return;
	
	//Folder test
	OSFileError returnCode;

	testPrintHeader("FileManager-Tests");
	
	returnCode = OSDirectoryExists("TestOSFileFolder/Test");
	test_fileManager(OSFileError_NoError, returnCode, "FolderExistTest 1");
	
	returnCode = OSDirectoryExists("TestOSFileFolder/Test/A");
	if (!(returnCode == OSFileError_FolderNotFound))
	{
		returnCode = OSDirectoryDelete("TestOSFileFolder/Test/A");
		test_fileManager(OSFileError_NoError, returnCode, "FolderDeleteTest 2.5");
	}
		
	returnCode = OSDirectoryCreate("TestOSFileFolder/Test/A");
	test_fileManager(OSFileError_NoError, returnCode, "FolderCreateTest 2");

	returnCode = OSDirectoryDelete("TestOSFileFolder/Test/A");
	test_fileManager(OSFileError_NoError, returnCode, "FolderDeleteTest 3");

	//Folder Full Test


	returnCode = OSDirectoryExists("TestOSFileFolder/Test/B/B");
	if (!(returnCode == OSFileError_FolderNotFound))
	{
		returnCode = OSDirectoryForceDelete("TestOSFileFolder/Test/B");
		test_fileManager(OSFileError_NoError, returnCode, "FolderForceDeleteTest 3.5");
	}

	returnCode = OSDirectoryFullCreate("TestOSFileFolder/Test/B/B");
	test_fileManager(OSFileError_NoError, returnCode, "FolderCreateTest 4");
	
	returnCode = OSDirectoryForceDelete("TestOSFileFolder/Test/B");
	test_fileManager(OSFileError_NoError, returnCode, "FolderForceDeleteTest 5");

	//File test

	returnCode = OSFileExists("TestOSFileFolder/dontDelete.txt");
	test_fileManager(OSFileError_NoError, returnCode, "FileExistTest 6");
	
	returnCode = OSFileExists("TestOSFileFolder/test.txt");
	if (!(returnCode == OSFileError_FileNotFound))
	{
		returnCode = OSFileDelete("TestOSFileFolder/test.txt");
		test_fileManager(OSFileError_NoError, returnCode, "FileDeleteTest 6.5");
	}

	returnCode = OSFileCreate("TestOSFileFolder/test.txt");
	test_fileManager(OSFileError_NoError, returnCode, "FileCreateTest 7");

	returnCode = OSFileDelete("TestOSFileFolder/test.txt");
	test_fileManager(OSFileError_NoError, returnCode, "FileDeleteTest 8");	
}
