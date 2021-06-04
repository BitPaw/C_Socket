#ifndef FileErrorInclude 
#define FileErrorInclude

typedef enum FileError_
{
	FileErrorNotSet,

	FileNotEnoghMemory,

	FileNoError,
	FileDoesNotExist,
	FileAlreadyExist,

	FileEmptyMessage,
	FileEmptyFileName,

	ProgramNameNotFound
}FileError;

#endif