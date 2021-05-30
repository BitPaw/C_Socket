#define DEBUGSTATE 1

#define True 1
#define False 0

#include "FileManager.h"

#ifdef OSWindows
#include <windows.h>
#include <fileapi.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

FileManagerErrorCode DoesFileExist_FULL(char* directory, const char* filePath)
{
	if(DEBUGSTATE)
	{
		printf("-------------------------------------\n");
		printf("- Folder Path: \"%s\"\n", directory);
		printf("- File Path: \"%s\"\n", filePath);
		printf("-------------------------------------\n");
	}

	//checks if '.' is in file
	int length = 0;
	while (filePath[length] != '.')
		if (filePath[++length] == '\0')
			return FileManager_NoFileExtension;

	//checks if more then 0 char before .
	if (length < 1)
		return FileManager_ExtensionToShort;

	//checks if more then 0 char after .
	if(filePath[++length] == '\0')
		return FileManager_ExtensionToShort;

	
	//checks File exists
	struct stat st = { 0 };
	char* Path;

	
	if (directory != NULL)
	{

		if (stat(directory, &st) == -1)
			return FileManager_FolderNotFound;


		//checks File exists

		const int pathLength = strlen(directory) + 1;
		const int fileLength = strlen(filePath);
		const int filePathLength = pathLength + fileLength + 1;

		Path = calloc(filePathLength, sizeof(char));

		memcpy(Path, directory, (pathLength - 1) * sizeof(char));
		Path[pathLength - 1] = '/';
		memcpy(Path + pathLength, filePath, fileLength * sizeof(char));

		if (stat(Path, &st) == -1)
			return FileManager_FileNotFound;

	}else
	{
		Path = filePath;
		
		if (stat(Path, &st) == -1)
			return FileManager_FileNotFound;
	}


	
	return FileManager_NoError;
}

FileManagerErrorCode DoesFileExist(char* path )
{
	int selector = 0;
	int length = 0;	
	while(path[length] != '\0')
	{		
		if (path[length] == '/')
			selector = length;


		length++;
	}
	
	
	char* file;
	
	if (selector == 0)
	{
		file = path + selector;
		path = NULL;
	}
	else
	{
		file = path + selector + 1;
		path[selector] = '\0';
	}
		
		
	return DoesFileExist_FULL(path ,file );
}

FileManagerErrorCode WriteInFile(char* directory, char* filePath, char* content)
{
	if (content == NULL)
		return FileManager_ContentIsNull;

	const FileManagerErrorCode fileExistOutput = DoesFileExist_FULL(directory, filePath);
	
	if(fileExistOutput != FileManager_NoError)
	{
		switch (fileExistOutput)
		{
		case FileManager_FolderNotFound: 
			mkdir("/some/directory", 0700);
			
			break;
			
		case FileManager_FileNotFound: break;
			
		case FileManager_NoFileExtension: 
		case FileManager_ExtensionToShort:
			return fileExistOutput;

			//No Errors or impossible Errors 
		case FileManager_NoError:
		case FileManager_ContentIsNull:
			break;
		}
	}
	
	return FileManager_NoError;
}

char CreateDir(char* directory)
{
	char returnValue = -1;

	
	#ifdef OSWindows

	const int directoryLength = strlen(directory)+1;
	
	wchar_t* w_directory = calloc(directoryLength, sizeof(wchar_t));

	if (w_directory == NULL)
		return 9;

	mbstowcs(w_directory, directory, directoryLength );

	
	returnValue = CreateDirectory(w_directory,NULL)? 0 : -1;

	if(returnValue != 0)
	{
		const DWORD lastError = GetLastError();

		if (lastError == ERROR_ALREADY_EXISTS)
			returnValue = 1;
		if (lastError == ERROR_PATH_NOT_FOUND)
			returnValue = 2;
		if (lastError == ERROR_ACCESS_DENIED)
			returnValue = 3;
	}
	
	free(w_directory);
	
	#endif
	
	#ifdef OSUnix

	
	#endif
	
	return returnValue;
}

char CreateFullDir(char* directory)
{
	char returnValue = 0;
	
	unsigned int counter = 0;

	while(directory[counter] != '\0' && (returnValue == 0 || returnValue == 1 ))
	{
		while (directory[counter] != '/' && directory[counter] != '\0')
		{
			counter++;
		}
			
		
		char* partDirectory = calloc(counter+1, sizeof(char));

		if (partDirectory == NULL)
			return 9;
		
		memcpy(partDirectory, directory, counter * sizeof(char));

		returnValue = CreateDir(partDirectory);
		
		free(partDirectory);

		counter++;
	}

	return returnValue;
}

