#ifndef FileErrorInclude 
#define FileErrorInclude

typedef enum FileError_
{
	FileErrorNotSet,

	FileNoError,
	FileDoesNotExist,
	FileAlreadyExist,
	ProgramNameNotFound
}FileError;

#endif