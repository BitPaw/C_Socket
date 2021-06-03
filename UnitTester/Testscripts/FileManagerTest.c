#pragma once


#include "../../SocketFileManager/FileManager.h"
#include "../Tester.h"


void test_fileManager(FileManagerErrorCode expectedInput, FileManagerErrorCode input, char* name)
{
	testPrint((expectedInput == input), FileManagerErrorCodeToString(expectedInput), FileManagerErrorCodeToString(input), "FileManagerErrorCode", name);
}



void fileManager_test(char execute)
{
	if (execute == 0)
		return;
	
	//Folder test
	FileManagerErrorCode returnCode;

	returnCode = FM_DirExists("TestFileManagerFolder/Test");
	test_fileManager(FileManager_NoError, returnCode, "FolderExistTest 1");
	
	returnCode = FM_DirExists("TestFileManagerFolder/Test/A");
	if (!(returnCode == FileManager_FolderNotFound))
	{
		returnCode = FM_DirDelete("TestFileManagerFolder/Test/A");
		test_fileManager(FileManager_NoError, returnCode, "FolderDeleteTest 2.5");
	}
		
	returnCode = FM_DirCreate("TestFileManagerFolder/Test/A");
	test_fileManager(FileManager_NoError, returnCode, "FolderCreateTest 2");

	returnCode = FM_DirDelete("TestFileManagerFolder/Test/A");
	test_fileManager(FileManager_NoError, returnCode, "FolderDeleteTest 3");

	//Folder Full Test


	returnCode = FM_DirExists("TestFileManagerFolder/Test/B/B");
	if (!(returnCode == FileManager_FolderNotFound))
	{
		returnCode = FM_DirForceDelete("TestFileManagerFolder/Test/B/B");
		test_fileManager(FileManager_NoError, returnCode, "FolderForceDeleteTest 3.5");
	}

	returnCode = FM_DirFullCreate("TestFileManagerFolder/Test/B/B");
	test_fileManager(FileManager_NoError, returnCode, "FolderCreateTest 4");
	
	returnCode = FM_DirForceDelete("TestFileManagerFolder/Test/B/B");
	test_fileManager(FileManager_NoError, returnCode, "FolderForceDeleteTest 5");

	//File test

	returnCode = FM_FileExists("TestFileManagerFolder/NULL.txt");
	test_fileManager(FileManager_NoError, returnCode, "FileExistTest 6");
	
	returnCode = FM_FileExists("TestFileManagerFolder/test.txt");
	if (!(returnCode == FileManager_FileNotFound))
	{
		returnCode = FM_FileDelete("TestFileManagerFolder/test.txt");
		test_fileManager(FileManager_NoError, returnCode, "FileDeleteTest 6.5");
	}

	returnCode = FM_FileCreate("TestFileManagerFolder/test.txt");
	test_fileManager(FileManager_NoError, returnCode, "FileCreateTest 7");

	returnCode = FM_FileDelete("TestFileManagerFolder/test.txt");
	test_fileManager(FileManager_NoError, returnCode, "FileDeleteTest 8");

	
	
	
}
