#pragma once

#include "../List/List.h"
#include "Path.h"


#ifndef PathListInclude
#define PathListInclude

/*
 * Function:  PathListInitialize
 * --------------------
 * Acts like a constructor
 * ! A list must be set to EMPTYLIST before each initialization
 * eg: 'List a = EMPTYLIST;'
 * --------------------
 */
void PathListInitialize(List* pathList, unsigned int count);

void PathListDestruction(List* pathList);

/*
 * Function:  PathListItemInsertAt
 * --------------------
 * adds parameter value to index in parameter list->content
 * --------------------
 *  returns: 0 if successful
 *	  -1 List is NULL
 *	  -2 Out of bounds
 */
int PathListItemInsertAt(List* pathList, unsigned int indexValue, Path* value);

/*
 * Function:  PathListItemGet
 * --------------------
 * adds parameter value to index in parameter list->content
 * --------------------
 *  returns: Value if successful
 *	  NULL List is NULL
 *	  NULL Out of bounds
 */
Path* PathListItemGet(List* pathList, unsigned int index);

/*
 * Function:  PathListItemAdd
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
int PathListItemAdd(List* pathList, Path* value);

/*
 * Function:  PathListItemRemove
 * --------------------
 * adds parameter value to index in parameter list->content
 * --------------------
 *  returns: 0 if successful
 *     1 Removed Value already NULL
 *	  -1 List is NULL
 *	  -2 Out of bounds
 */
int PathListItemRemove(List* pathList, unsigned int index);

void PathListToString(List* pathList, char* buffer);



#endif



