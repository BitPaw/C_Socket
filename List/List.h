#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#ifndef ListInclude
#define ListInclude

#define EMPTYLIST (List){0}

typedef struct List_
{
	void** content;
	unsigned int size;
	//Don`t Touch
	unsigned int sizeOfObject;
}List;

/*
 * Function:  ListInitialize
 * --------------------
 * Acts like a constructor
 * ! A list must be set to EMPTYLIST before each initialization
 * eg: 'List a = EMPTYLIST;'
 * --------------------
 */
void ListInitialize(List* list, unsigned int count, unsigned int sizeOfObject);

void ListDestruction(List* path);

/*
 * Function:  ListItemInsertAt
 * --------------------
 * adds parameter value to index in parameter list->content
 * --------------------
 *  returns: 0 if successful
 *	  -1 List is NULL
 *	  -2 Out of bounds
 */
int ListItemInsertAt(List* list, unsigned int indexValue, void* value);

/*
 * Function:  ListItemGet
 * --------------------
 * adds parameter value to index in parameter list->content
 * --------------------
 *  returns: Value if successful
 *	  NULL List is NULL
 *	  NULL Out of bounds
 */
void* ListItemGet(List* list, unsigned int index);

/*
 * Function:  ListItemAdd
 * --------------------
 * adds parameter value to next free value in parameter list->content
 * --------------------
 *
 * When the List is full, it will be made bigger
 *
 *  returns: 0 if successful
 *	  -1 List is NULL
 *	  -2 Out of bounds
 *	  -9 Calloc failed
 */
int ListItemAdd(List* list, void* value);

/*
 * Function:  ListItemRemove
 * --------------------
 * adds parameter value to index in parameter list->content
 * --------------------
 *  returns: 0 if successful
 *     1 Removed Value already NULL
 *	  -1 List is NULL
 *	  -2 Out of bounds
 */
int ListItemRemove(List* list, unsigned int index);

/*
 * Function:  ListClear
 * --------------------
 * sets all values in list->content = 0
 * --------------------
 *  returns: 0 if successful
 *	  -1 List is NULL
 */
int ListClear(List* list);

void ListPrint_string(List* list);

void ListPrint_int(List* list);
#endif