#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ListInitialize(List* list, size_t count, size_t sizeOfObject)
{
	list->content = calloc(count, sizeOfObject);
	list->size = count;
	list->sizeOfObject = sizeOfObject;
}

void ListDestruction(List* list)
{
	free(list->content);
}

void ListItemInsertAt(List* list, int indexValue, void* value)
{
	if(list == NULL)
		return;

	if(indexValue < 0 || indexValue > (list->size-1))
		return;
	
	list->content[indexValue] = value;
}

void* ListItemGet(List* list, unsigned int index)
{
	if (index > list->size - 1)
		return NULL;

	if (list == NULL)
		return NULL;

	return list->content[index];
}

void ListItemAdd(List* list, void* value)
{
	int unsigned addLocation = 0;

	while (list->content[addLocation] != NULL && addLocation <= list->size - 1)
		addLocation++;


	if(addLocation >= list->size)
	{
		const unsigned int oldSize = list->size;
		
		list->size = (int)(1.5 * (list->size + 1));

		void* reallocOutput = realloc(list->content, list->size * list->sizeOfObject) ;

		if(reallocOutput == NULL)
			return;

		
		list->content = reallocOutput;
		
		for (int i = oldSize; i < list->size; ++i)
			list->content[i] = NULL;
	}
	
	ListItemInsertAt(list, addLocation,value);
}

void ListPrint_string(List* list)
{
	printf("{");
	for (int i = 0; i < list->size; ++i)
	{
		if (i != 0)
			printf(",");

		printf("%s", ListItemGet(list, i));
	}
	printf("}");
}

void ListPrint_int(List* list)
{
	printf("{");
	for (int i = 0; i < list->size; ++i)
	{
		if (i != 0)
			printf(",");
		
		printf("%i", ListItemGet(list, i));
	}
	printf("}");
}