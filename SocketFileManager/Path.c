#include "Path.h"

#include <stdlib.h>
#include <string.h>

void PathInitialize(Path* path, char* stringPath)
{
	path->fullPath = stringPath;
	path->fullPathLength = strlen(stringPath);

	path->directory = calloc(path->fullPathLength +1, sizeof(char));
	memcpy(path->directory, stringPath, path->fullPathLength);
	
	int selector = 0;
	int length = 0;
	while (path->directory[length] != '\0')
	{
		if (path->directory[length] == '/')
			selector = length;

		length++;
	}

	
	if (selector == 0)
	{
		path->file = stringPath + selector;
		path->directory = NULL;
	}
	else
	{
		path->file = stringPath + selector + 1;
		path->directory[selector] = '\0';
	}


	//Get file extension
	selector = 0;
	length = 0;

	while(path->file[selector] != '.' )
	{
		selector++;
	}
	
	unsigned const int fileNameLength = strlen(path->file);
	path->fileName = calloc((fileNameLength + 1) - (selector + 1), sizeof(char));
	memcpy(path->fileName, path->file , selector);
	
	path->fileType = calloc((fileNameLength + 1) - (selector + 1), sizeof(char));
	memcpy(path->fileType, path->file + selector + 1, fileNameLength - selector);
	
}

void PathDestruction(Path* path)
{
	free(path->directory);
	free(path->fileName);
	free(path->fileType);
	*path = (Path){ 0 };
}

char PathCompare(Path* path0, Path* path1)
{
	if (path0->fullPathLength != path1->fullPathLength)
		return -1;

	if (memcmp(path0->fullPath,path1->fullPath,sizeof(char) * strlen(path0->fullPath)) != 0 )
		return -1;
	
	
	return 0;
}
