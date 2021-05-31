#include "List.h"

#include <stdlib.h>

void ListInitialize(List* list, size_t count, size_t sizeOfObject)
{
	list->content = calloc(count, sizeOfObject);
	list->size = count;
	list->sizeOfObject = sizeOfObject;
	list->addLocation = 0;
	
}

void ListDestruction(List* list)
{
	free(list->content);
}

void ListInsertAt(List* list, int indexValue, void* value)
{
	if(list == NULL)
		return;

	if(indexValue < 0 || indexValue > (list->size-1))
		return;
	
	list->content[indexValue] = value;
}

void* ListGet(List* list, unsigned int index)
{
	if (index > list->size - 1)
		return NULL;

	if (list == NULL)
		return NULL;

	return list->content[index];
}

void ListAdd(List* list, void* value)
{
	
	if(list->addLocation >= list->size)
	{
		list->size = (int)(1.5 * (list->size + 1));
		list->content = realloc(list->content, list->size * list->sizeOfObject) ;

		for (int i = list->addLocation; i < list->size; ++i)
			list->content[i] = NULL;
		
	}
	
	ListInsertAt(list,list->addLocation,value);

	list->addLocation++;
}
