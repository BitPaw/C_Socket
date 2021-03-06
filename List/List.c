#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ListInitialize(List* list, unsigned int count, unsigned int sizeOfObject)
{
	if( list->content != NULL || list->sizeOfObject != 0)
		return;
	
	list->content = calloc(count, sizeOfObject);
	list->size = count;
	list->sizeOfObject = sizeOfObject;
}

void ListDestruction(List* list)
{
	if(list == NULL) // Parameter NULL
		return;

	if (list->content == NULL) // No data to delete
		return;
	
	for (int i = 0; i < list->size; ++i)
	{
		void* element = list->content[i];
		
		if(element != NULL)
		{
			free(element);
			list->content[i] = NULL;
		}
	}
		
	free(list->content);
	list->content = NULL;
}

int ListItemInsertAt(List* list, unsigned int indexValue, void* value)
{
	if(list == NULL)
		return -1;

	if(indexValue < 0 || indexValue > (list->size-1))
		return -2;
	
	list->content[indexValue] = value;

	return 0;
}

void* ListItemGet(List* list, unsigned int index)
{
	if (index > list->size - 1)
		return NULL;

	if (list == NULL)
		return NULL;

	return list->content[index];
}

int ListItemAdd(List* list, void* value)
{
	if (list == NULL)
		return -1;
	
	int unsigned addLocation = 0;

	while (list->content[addLocation] != NULL && addLocation <= list->size - 1)
		addLocation++;

	
	if(addLocation >= list->size)
	{
		const unsigned int oldSize = list->size;
		
		list->size = (int)(1.5 * (list->size + 1));


		void* reallocOutput = realloc(list->content, list->size * list->sizeOfObject) ;

		if(reallocOutput == NULL)
			return -9;

		
		list->content = reallocOutput;
		
		for (int i = oldSize; i < list->size; ++i)
			list->content[i] = NULL;
	}
	
	return ListItemInsertAt(list, addLocation,value);
}

int ListItemRemove(List* list, unsigned int index)
{
	if (index > list->size - 1)
		return -2;

	if (list == NULL)
		return -1;
	
	if (list->content[index] == NULL)
		return 1;

	if(list->content[index] != NULL)
	{
		free(list->content[index]);
		list->content[index] = NULL;
	}
	
	
	
	return 0;
}

int ListClear(List* list)
{
	if (list == NULL)
		return -1;

	for (int i = 0; i < list->size; ++i)
		ListItemRemove(list, i);

	return 0;
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