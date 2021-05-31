#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#ifndef FileManagerInclude
#define FileManagerInclude

typedef struct List_
{
	void** content;
	unsigned int size;
	//Don`t Touch
	unsigned int addLocation;
	unsigned int sizeOfObject;
}List;


void ListInitialize(List* list, unsigned int count, unsigned int sizeOfObject);

void ListDestruction(List* path);

void ListInsertAt(List* list, unsigned int indexValue, void* value);

void* ListGet(List* list, unsigned int index);

void ListAdd(List* list, void* value);

#endif