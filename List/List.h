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
	unsigned int sizeOfObject;
}List;


void ListInitialize(List* list, unsigned int count, unsigned int sizeOfObject);

void ListDestruction(List* path);

void ListItemInsertAt(List* list, unsigned int indexValue, void* value);

void* ListItemGet(List* list, unsigned int index);

/// <summary>
/// AAAA
/// </summary>
/// <param name="list"></param>
/// <param name="value"></param>
void ListItemAdd(List* list, void* value);

void ListItemRemove(List* list, unsigned int index);

void ListPrint_string(List* list);

void ListPrint_int(List* list);
#endif