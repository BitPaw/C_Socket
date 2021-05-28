#define DEBUGSTATE 1

#define True 1
#define False 0

#include "FileManager.h"
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
