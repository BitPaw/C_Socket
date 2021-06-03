#include "PathList.h"

#include <stddef.h>
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

void PathListToString(List* pathList)
{

	for (int i = 0; i < pathList->size; ++i)
	{
		printf("%s\n",PathToString(PathListItemGet(pathList, i)));
	}

	printf("\n\n");
}
