#define True 1
#define False 0

#include "FileManager.h"


#ifdef OSWindows
#include <windows.h>
#include <fileapi.h>

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

#include "PathList.h"


OSError OSFileExists_splitParameter(char* directory, char* filePath)
{

	//checks if '.' is in file
	int length = 0;
	while (filePath[length] != '.')
		if (filePath[++length] == '\0')
			return OSError_NoFileExtension;

	//checks if more then 0 char before .
	if (length < 1)
		return OSError_ExtensionToShort;

	//checks if more then 0 char after .
	if(filePath[++length] == '\0')
		return OSError_ExtensionToShort;

	
	//checks File exists
	struct stat st = { 0 };
	char* Path;

	
	if (directory != NULL)
	{

		if (stat(directory, &st) == -1)
			return OSError_DirectoryNotFound;


		//checks File exists

		const int pathLength = strlen(directory) + 1;
		const int fileLength = strlen(filePath);
		const int filePathLength = pathLength + fileLength + 1;

		Path = calloc(filePathLength, sizeof(char));

		memcpy(Path, directory, (pathLength - 1) * sizeof(char));
		Path[pathLength - 1] = '/';
		memcpy(Path + pathLength, filePath, fileLength * sizeof(char));

		const char checkValue = stat(Path, &st) == -1;

		free(Path);
		if (checkValue)
			return OSError_FileNotFound;
		
	}else
	{
		Path = filePath;
		
		if (stat(Path, &st) == -1)
			return OSError_FileNotFound;
	}
	
	return OSError_NoError;
}

OSError OSFileExists(char* path)
{
	Path tempPath;

	PathInitialize(&tempPath, path);

	const OSError returnValue = OSFileExistsP(&tempPath);

	PathDestruction(&tempPath);
	
	return returnValue;
}

OSError OSFileExistsP(Path* path)
{
	return OSFileExists_splitParameter(path->directory, path->file);
}

OSError OSDirectoryExists(char* directory)
{

	if (directory == NULL)
		return OSError_ContentIsNull;
	
	struct stat st = { 0 };

	if (stat(directory, &st) == -1)
		return OSError_DirectoryNotFound;

	return OSError_NoError;
}

OSError OSDirectoryExistsP(Path* path)
{
	return OSDirectoryExists(path->directory);
}

OSError OSFileForceWrite(char* path, char* content, char writeMode)
{
	Path tempPath;

	PathInitialize(&tempPath, path);

	const OSError returnValue = OSFileForceWriteP(&tempPath, content, writeMode);

	PathDestruction(&tempPath);

	return returnValue;
}

OSError OSFileForceWriteP(Path* path, char* content, char writeMode)
{

	if (content == NULL)
		return OSError_ContentIsNull;

	const OSError fileExistOutput = OSFileExists_splitParameter(path->directory,path->file);
	
	if(fileExistOutput != OSError_NoError)
	{
		switch (fileExistOutput)
		{
			case OSError_DirectoryNotFound:
			{
				const OSError errorCode = OSDirectoryFullCreate(path->directory);
				
				if (errorCode != OSError_NoError)
					return errorCode;

				return OSFileForceWriteP(path, content, writeMode);
			}
			case OSError_FileNotFound:
			{
				const OSError errorCode = OSFileCreate(path->fullPath);

				if (errorCode != OSError_NoError)
					return errorCode;
					
				return OSFileForceWriteP(path, content, writeMode);
			}
			case OSError_NoFileExtension:
			case OSError_ExtensionToShort:
			case OSError_CallocWentWrong:
			case OSError_AccessDenied:
			case OSError_PathNotFound:
			case OSError_FileIsCurrentlyInUse:
			case OSError_FileToBig:
			case OSError_FileNameToLong:
			case OSError_FileNameInvalid:
			case OSError_DirectoryInvalid:
			case OSError_WrittenContentIsCorrupted:
			case OSError_UnknownError:
			case OSError_ParameterIsNull:
			case OSError_ParameterInvalid:

				//No Errors or impossible Errors 
			case OSError_ContentIsNull:
			case OSError_FolderAlreadyExists:
			case OSError_FileAlreadyExists:
			case OSError_DirectoryNotEmpty:
			case OSError_NotImplemented:
			case OSError_NoError:
			default:
				return fileExistOutput;
			

		}
	}
	
	return OSFileWriteBaseP(path,content,writeMode);
}

OSError OSFileWriteBase(char* path, char* content, char writeMode)
{
	Path tempPath;

	PathInitialize(&tempPath, path);

	const OSError returnValue = OSFileWriteBaseP(&tempPath, content, writeMode);

	PathDestruction(&tempPath);

	return returnValue;
}

OSError OSFileWriteBaseP(Path* path, char* content, char writeMode)
{
	if (path == NULL)
		return OSError_ParameterIsNull;
	
	if(path->hasFile == 0)
		return OSError_ParameterInvalid;
		
	FILE* file;
	errno = 0;
	
	switch (writeMode)
	{
		//content will be overwritten.
		case 0:
			file = fopen(path->fullPath, "w");
			break;
		//content is added to the end of the file.
		case 1:
			file = fopen(path->fullPath, "a");
			break;
		default:
			return OSError_ParameterInvalid;
	}	

	if(errno != 0)
	{
		return ErrnoErrorToOSError(errno);
	}
		
	if (file == NULL)
		return OSError_UnknownError;

	fprintf(file, "%s", content);	
	
	fclose(file);

	return OSError_NoError;
}

OSError OSFileRead(char* path, char** readContent)
{
	Path tempPath;

	PathInitialize(&tempPath, path);

	const OSError returnValue = OSFileReadP(&tempPath, readContent);

	PathDestruction(&tempPath);

	return returnValue;
}

OSError OSFileReadP(Path* path, char** readContent)
{
	if (path == NULL)
		return OSError_ParameterIsNull;

	if (path->hasFile == 0)
		return OSError_ParameterInvalid;
	
	errno = 0;
	FILE* file = fopen(path->fullPath, "r");

	if (errno != 0)
	{
		return ErrnoErrorToOSError(errno);
	}
	
	fseek(file, 0, SEEK_END); // Jump to end of file
	const unsigned int fileLength = ftell(file); // Get length of file
	fseek(file, 0, SEEK_SET); // jump to beginning
	
	*readContent = calloc(fileLength + 1 , sizeof(char));
	
	if (!readContent)
	{
		fclose(file);
		return OSError_CallocWentWrong;
	}

	unsigned int readSize = fread(*readContent, sizeof(char), fileLength, file);
	
	fclose(file);
	
	return OSError_NoError;
}

OSError OSFileCreate(char* path)
{
	Path tempPath;

	PathInitialize(&tempPath, path);

	const OSError returnValue = OSFileCreateP(&tempPath);

	PathDestruction(&tempPath);

	return returnValue;
}

OSError OSFileCreateP(Path* path)
{
	if (path == NULL)
		return OSError_ParameterIsNull;
	
	OSError returnValue = OSError_NoError;

	errno = 0;
	
	FILE* file = fopen(path->fullPath, "a");

	if (errno != 0)
	{
		return ErrnoErrorToOSError(errno);
	}

	if (file == NULL)
		return OSError_UnknownError;

	fclose(file);
		
	return returnValue;
}

OSError OSFileDelete(char* path)
{
	errno = 0;

	if(remove(path)!= 0)
	{
		return ErrnoErrorToOSError(errno);
	}
	
	return OSError_NoError;
}

OSError OSFileDeleteP(Path* path)
{
	return OSFileDelete(path->fullPath);
}

OSError OSDirectoryCreate(char* directory)
{
	if(!directory)
        return OSError_ParameterIsNull;

	OSError returnValue = OSError_NoError;

    #ifdef OSUnix

    errno = 0;

    if(mkdir(directory,0777) != 0){
        return ErrnoErrorToOSError(errno);
    }

    return returnValue;


    #endif

	#ifdef OSWindows
	
	returnValue = CreateDirectoryA(directory,NULL)? 0 : -1;

	if(returnValue != 0)
	{
		const DWORD lastError = GetLastError();
		returnValue = windowsErrorToOSError(lastError);
	}
	
	#endif
	

	
	return returnValue;
}

OSError OSDirectoryCreateP(Path* path)
{
	return OSDirectoryCreate(path->directory);
}

OSError OSDirectoryFullCreate(char* directory)
{

	OSError returnValue = OSError_NoError;
	
	unsigned int counter = 0;

	if (directory[counter] == '\0')
		return OSError_PathNotFound;
	
	do
	{
		while (directory[counter] != '/' && directory[counter] != '\0')
		{
			counter++;
		}
		
		char* partDirectory = calloc(counter+1, sizeof(char));

		if (partDirectory == NULL)
			return OSError_CallocWentWrong;
		
		memcpy(partDirectory, directory, (counter) * sizeof(char));


        if(memcmp(partDirectory,"..", 3 * sizeof(char)) != 0 && memcmp(partDirectory,".", 2 * sizeof(char)))
		    returnValue = OSDirectoryCreate(partDirectory);
		
		free(partDirectory);
				
	} 	while (directory[counter++] != '\0' && (returnValue == OSError_NoError || returnValue == OSError_FolderAlreadyExists || returnValue == OSError_FileAlreadyExists));

	return returnValue;
}

OSError OSDirectoryFullCreateP(Path* path)
{
	return OSDirectoryFullCreate(path->directory);
}

OSError OSDirectoryDelete(char* directory)
{
    OSError returnValue = OSError_NoError;

#ifdef OSUnix
    errno = 0;

    if(rmdir(directory) != 0)
    {
        return ErrnoErrorToOSError(errno);
    }

    return returnValue;
#endif

#ifdef OSWindows

	
	wchar_t* w_directory = stringToWString(directory);
	
	if (RemoveDirectory(w_directory) == 0)
	{
		const DWORD lastError = GetLastError();
		returnValue = windowsErrorToOSError(lastError);
	}

	free(w_directory);
	
	return returnValue;
#endif
}

OSError OSDirectoryDeleteP(Path* path)
{
	return OSDirectoryFullCreate(path->directory);
}

OSError OSDirectoryForceDelete(char* directory)
{
	#ifdef OSUnix


    return OSError_NotImplemented;

    #endif
	
	OSError returnValue = OSError_NoError;
	
	List dirContent = EMPTYLIST;
	
	OSListAllFiles(&dirContent,directory);
	
	if(dirContent.size > 0)
	{
		for (int i = 0; i < dirContent.size; ++i)
		{
			Path* tempPath = PathListItemGet(&dirContent, i);

			if(returnValue != OSError_NoError)
				continue;
			
			if (tempPath != NULL)
			{
				if(tempPath->hasFile == 1)
					returnValue = OSFileDelete(tempPath->fullPath);
				else
				{
					const OSError tempErrorCode = OSDirectoryDelete(tempPath->fullPath);

					if (tempErrorCode == OSError_DirectoryNotEmpty)
						returnValue = OSDirectoryForceDelete(tempPath->fullPath);
					else
						if (tempErrorCode != OSError_NoError)
							returnValue = tempErrorCode;
					
				}
			}
		}
	}
	
	PathListDestruction(&dirContent);

	if (returnValue == OSError_NoError)
		returnValue = OSDirectoryDelete(directory);
	
	return returnValue;
}

OSError OSDirectoryForceDeleteP(Path* path)
{
	return OSDirectoryForceDelete(path->directory);
}

OSError OSListAllFiles(List* pathList,char* directory)
{
	if (!pathList || !directory)
		return OSError_ParameterIsNull;
	
#ifdef OSUnix
	return OSError_NotImplemented;
#endif
#ifdef OSWindows

	int selector = 0;
	const int directoryLength = strlen(directory);

	if (directoryLength < 2)
		return;

	const char hasRightEnding = (directory[directoryLength - 1] == '*') && (directory[directoryLength - 2] == '/');

	char* tempDirectory;
	
	if(hasRightEnding == 1)
	{
		tempDirectory = directory;
	}
	else
	{
		tempDirectory = calloc(directoryLength + 3, sizeof(char));
		if (tempDirectory == NULL)
			return OSError_CallocWentWrong;
		
		strcpy_s(tempDirectory, (directoryLength + 1) * sizeof(char), directory);
		strcpy_s(tempDirectory + directoryLength, (3) * sizeof(char), "/*");
	}

	
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(tempDirectory, &data);

	if (hFind != INVALID_HANDLE_VALUE) {

		int fileCount = (directoryLength > 4 ? -1 : 1);

		while (FindNextFileA(hFind, &data))
		{
			fileCount++;
		}
	

		PathListInitialize(pathList, fileCount);

		if(fileCount == 0)
		{
			FindClose(hFind);
			
			if (hasRightEnding == 0)
				free(tempDirectory);
			
			return;
		}

		FindClose(hFind);
		hFind = FindFirstFileA(tempDirectory, &data);
		
		do {

			char* fileName = data.cFileName;
			
			const unsigned int compareLenght = sizeof(char) * strlen(fileName);
			if (memcmp(fileName, ".", compareLenght) != 0 && memcmp(fileName, "..", compareLenght) != 0)
			{
				const unsigned int directoryLength = strlen(tempDirectory);
				const unsigned int FileNameLength = strlen(fileName);
				
				char* stringPath = calloc(directoryLength + FileNameLength +1,sizeof(char));
				if (stringPath == NULL)
					return OSError_CallocWentWrong;
				
				memcpy(stringPath, tempDirectory, directoryLength * sizeof(char));
				memcpy(stringPath + directoryLength -1, fileName, FileNameLength * sizeof(char));
				
				Path* newPath = calloc(1,sizeof(Path));
				PathInitialize(newPath, stringPath);
				PathListItemAdd(pathList, newPath);

				free(stringPath);
			}
		} while (FindNextFileA(hFind, &data));	
	}

	if(hasRightEnding == 0)
		free(tempDirectory);

	FindClose(hFind);

	return OSError_NoError;
#endif
}


static OSError ErrnoErrorToOSError(unsigned int errnoAsInt)
{
	switch (errnoAsInt)
	{
        case ENOENT:
            return OSError_DirectoryNotFound;
        case EAGAIN:
            return OSError_CallocWentWrong;
        case EACCES:
            return OSError_AccessDenied;
	    case EEXIST:
            return OSError_FileAlreadyExists;
        case EISDIR:
		return OSError_ParameterInvalid;
        case EINVAL:
            return OSError_FileNameInvalid;
        case EFBIG:
            return OSError_FileToBig;
        case ENAMETOOLONG:
            return OSError_FileNameToLong;

	default:
		printf("errno: %i", errnoAsInt);
		return OSError_UnknownError;
	}
	
}

#ifdef OSWindows
static wchar_t* stringToWString(char* string)
{
	const int pathLength = strlen(string) + 1;

	wchar_t* w_path = calloc(pathLength, sizeof(wchar_t));

	mbstowcs(w_path, string, pathLength);

	return w_path;
}

static OSError windowsErrorToOSError(unsigned long rawError)
{
	switch (rawError)
	{
	case ERROR_ACCESS_DENIED:
		return OSError_AccessDenied;
	case ERROR_ALREADY_EXISTS:
		return OSError_FolderAlreadyExists;
	case ERROR_DIRECTORY:
		return OSError_DirectoryInvalid;
	case ERROR_DIR_NOT_EMPTY:
		return OSError_DirectoryNotEmpty;
	case ERROR_FILE_NOT_FOUND:
		return OSError_FileNotFound;
	case ERROR_FILE_EXISTS:
		return OSError_FileAlreadyExists;
	case ERROR_INVALID_NAME:
		return OSError_DirectoryInvalid;
	case ERROR_PATH_NOT_FOUND:
		return OSError_PathNotFound;
	case ERROR_SHARING_VIOLATION:
		return OSError_FileIsCurrentlyInUse;
	default:
		return OSError_UnknownError;
	}
}
#endif




