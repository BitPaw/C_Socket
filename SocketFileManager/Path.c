#include "Path.h"

#include <stdlib.h>
#include <string.h>

void PathInitialize(Path* path, char* stringPath)
{
	if(stringPath == NULL || stringPath[0] == '\0')
	{
		*path = (Path){0};
		return;
	}
	
	path->fullPathLength = strlen(stringPath);
	
	path->fullPath = calloc(path->fullPathLength + 1, sizeof(char));
	strcpy_s(path->fullPath, path->fullPathLength + 1, stringPath);


	path->directory = calloc(path->fullPathLength + 1, sizeof(char));
	strcpy_s(path->directory, path->fullPathLength + 1, path->fullPath);
	
	int selector = 0;
	int length = 0;
	char hasFile = 0;
	while (path->directory[length] != '\0')
	{
		if (path->directory[length] == '/')
			selector = length;

		if(path->directory[length] == '.')
			hasFile = 1;
		
		length++;
	}

	if(hasFile == 1)
	{
		path->hasFile = 1;
		
		if (selector == 0)
		{
			path->hasDirectory = 0;
			
			path->file = path->fullPath + selector;
			free(path->directory);
			path->directory = NULL;
			
		}
		else
		{
			path->hasDirectory = 1;
			
			path->file = path->fullPath + selector + 1;
			path->directory[selector] = '\0';
		}


		//Get file extension
		selector = 0;
		length = 0;

		while (path->file[selector] != '.')
		{
			selector++;
		}

		unsigned const int fileNameLength = strlen(path->file);
		path->fileName = calloc((fileNameLength + 1), sizeof(char));
		memcpy(path->fileName, path->file, selector);

		path->fileType = calloc((fileNameLength + 1) - (selector + 1), sizeof(char));
		memcpy(path->fileType, path->file + selector + 1, fileNameLength - selector);
		
	} else
	{
		path->hasFile = 0;
		path->hasDirectory = 1;
		
		path->fileName = NULL;
		path->file = NULL;
		path->fileType = NULL;
	}	
}

void PathDestruction(Path* path)
{
	free(path->fullPath);
	free(path->directory);
	free(path->fileName);
	free(path->fileType);

	path->fullPathLength = 0;

	path->fullPath = NULL;
	path->directory = NULL;
	path->fileName = NULL;
	path->fileType = NULL;
	path->file = NULL;

	path->hasFile = 0;
	path->hasDirectory = 0;
	
	*path = (Path){ 0 };
}

char PathCompare(Path* path0, Path* path1)
{
	if (path0->fullPathLength != path1->fullPathLength)
		return -1;


	if(!(path0->fullPath == NULL && path1->fullPath == NULL))
	{
		if (path0->fullPath == NULL || path1->fullPath == NULL)
			return -2;
			
		const unsigned int fullPathLength =(strlen(path0->fullPath) > strlen(path1->fullPath)) ? strlen(path0->fullPath) : strlen(path1->fullPath);
		if (memcmp(path0->fullPath, path1->fullPath, sizeof(char) * fullPathLength) != 0)
			return -2;
	}

	if (!(path0->directory == NULL && path1->directory == NULL))
	{
		if (path0->directory == NULL || path1->directory == NULL)
			return -3;

		const unsigned int fullPathLength = (strlen(path0->directory) > strlen(path1->directory)) ? strlen(path0->directory) : strlen(path1->directory);
		if (memcmp(path0->directory, path1->directory, sizeof(char) * fullPathLength) != 0)
			return -3;
	}

	if (!(path0->file == NULL && path1->file == NULL))
	{
		if (path0->file == NULL || path1->file == NULL)
			return -4;

		const unsigned int fullPathLength = (strlen(path0->file) > strlen(path1->file)) ? strlen(path0->file) : strlen(path1->file);
		if (memcmp(path0->file, path1->file, sizeof(char) * fullPathLength) != 0)
			return -4;
	}
	
	if (!(path0->fileName == NULL && path1->fileName == NULL))
	{
		if (path0->fileName == NULL || path1->fileName == NULL)
			return -5;

		const unsigned int fullPathLength = (strlen(path0->fileName) > strlen(path1->fileName)) ? strlen(path0->fileName) : strlen(path1->fileName);
		if (memcmp(path0->fileName, path1->fileName, sizeof(char) * fullPathLength) != 0)
			return -5;
	}

	if (!(path0->fileType == NULL && path1->fileType == NULL))
	{
		if (path0->fileType == NULL || path1->fileType == NULL)
			return -6;

		const unsigned int fullPathLength = (strlen(path0->fileType) > strlen(path1->fileType)) ? strlen(path0->fileType) : strlen(path1->fileType);
		if (memcmp(path0->fileType, path1->fileType, sizeof(char) * fullPathLength) != 0)
			return -6;
	}
	
	return 0;
}

char* PathToString(Path* path)
{
	return path->fullPath;
}