#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#ifndef PathIncluded
#define PathIncluded

typedef struct Path_
{
	unsigned int fullPathLength;

	char* fullPath;
	char* directory;
	
	char* file;
	char* fileName;
	char* fileType;

	char hasDirectory;
	char hasFile;
}Path;


void PathInitialize(Path* EmptyPath, char* stringPath);

void PathDestruction(Path* path);


/*
* Function:  PathCompare
* --------------------
* compares path0 to path1
* --------------------
*  returns: 0: Equal
*	 -1: lengthIsNotMatching
*	 -2: fullPathIsNotMatching
*	 -3: directoryIsNotMatching
*	 -4: fileIsNotMatching
*	 -5: fileNameIsNotMatching
*	 -6: fileTypeIsNotMatching
 */
char PathCompare(Path* path0, Path* path1);


char* PathToString(Path* path);

#endif

