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
}Path;


void PathInitialize(Path* path, char* stringPath);

void PathDestruction(Path* path);

#endif

