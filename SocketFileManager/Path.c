#include "Path.h"

#include <stdlib.h>
#include <string.h>

void PathInitialize(Path* EmptyPath, char* stringPath)
{
	if(stringPath == NULL || stringPath[0] == '\0')
	{
		*EmptyPath = (Path){0};
		return;
	}
	
	EmptyPath->fullPathLength = strlen(stringPath);
	
	EmptyPath->fullPath = calloc(EmptyPath->fullPathLength + 1, sizeof(char));
    memcpy(EmptyPath->fullPath,stringPath,EmptyPath->fullPathLength * sizeof(char));

	EmptyPath->directory = calloc(EmptyPath->fullPathLength + 1, sizeof(char));
    memcpy(EmptyPath->directory,EmptyPath->fullPath,EmptyPath->fullPathLength * sizeof(char));

	int selector = 0;
	int length = 0;
	char hasFile = 0;
	while (EmptyPath->directory[length] != '\0')
	{
		if (EmptyPath->directory[length] == '/')
			selector = length;

		if(EmptyPath->directory[length] == '.')
			hasFile = 1;
		
		length++;
	}

	if(hasFile == 1)
	{
		EmptyPath->hasFile = 1;
		
		if (selector == 0)
		{
			EmptyPath->hasDirectory = 0;
			
			EmptyPath->file = EmptyPath->fullPath + selector;
			free(EmptyPath->directory);
			EmptyPath->directory = NULL;
			
		}
		else
		{
			EmptyPath->hasDirectory = 1;
			
			EmptyPath->file = EmptyPath->fullPath + selector + 1;
			EmptyPath->directory[selector] = '\0';
		}


		//Get file extension
		selector = 0;
		length = 0;

		while (EmptyPath->file[selector] != '.')
		{
			selector++;
		}

		unsigned const int fileNameLength = strlen(EmptyPath->file);
		EmptyPath->fileName = calloc((fileNameLength + 1), sizeof(char));
		memcpy(EmptyPath->fileName, EmptyPath->file, selector);

		EmptyPath->fileType = calloc((fileNameLength + 1) - (selector + 1), sizeof(char));
		memcpy(EmptyPath->fileType, EmptyPath->file + selector + 1, fileNameLength - selector);
		
	} else
	{
		EmptyPath->hasFile = 0;
		EmptyPath->hasDirectory = 1;
		
		EmptyPath->fileName = NULL;
		EmptyPath->file = NULL;
		EmptyPath->fileType = NULL;
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