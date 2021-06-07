#include "PathList.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void PathListInitialize(List* pathList, unsigned int count){
	ListInitialize(pathList, count, sizeof(Path*));
}

void PathListDestruction(List* pathList)
{
	if(pathList == NULL)
		return;
			
	for (int i = 0; i < pathList->size; ++i)
	{
		if (pathList->content[i] != NULL)
		{
			PathDestruction(pathList->content[i]);
			free(pathList->content[i]);
			pathList->content[i] = NULL;
		}
	}
	
	ListDestruction(pathList);
}

int PathListItemInsertAt(List* pathList, unsigned int indexValue, Path* value)
{
	return ListItemInsertAt(pathList, indexValue, value);
}

Path* PathListItemGet(List* pathList, unsigned int index)
{
	return ListItemGet(pathList, index);
}

int PathListItemAdd(List* pathList, Path* value)
{
	return ListItemAdd(pathList, value);
}

int PathListItemRemove(List* pathList, unsigned int index)
{
	ListDestruction(PathListItemGet(pathList, index));
	return ListItemRemove(pathList, index);
}

void PathListToString(List* pathList, char* buffer)
{
	int length = 0;
	for (int i = 0; i < pathList->size; ++i)
	{
		char* PathAsString = PathToString(PathListItemGet(pathList, i));
		if(PathAsString != NULL)
		{
			const int pathStringLength = strlen(PathAsString);
            memcpy(buffer + length,PathAsString,pathStringLength + 1 * sizeof(char));

			length += pathStringLength;
			buffer[length++] = '\n';
		}	
	}

}
