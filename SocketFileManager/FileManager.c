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

#include "PathList.h"


OSFileError OSFileExists_splitParameter(char* directory, const char* filePath)
{
	
#ifdef OSUnix
	return OSFileError_NotImplemented;
#endif
		
	
	//checks if '.' is in file
	int length = 0;
	while (filePath[length] != '.')
		if (filePath[++length] == '\0')
			return OSFileError_NoFileExtension;

	//checks if more then 0 char before .
	if (length < 1)
		return OSFileError_ExtensionToShort;

	//checks if more then 0 char after .
	if(filePath[++length] == '\0')
		return OSFileError_ExtensionToShort;

	
	//checks File exists
	struct stat st = { 0 };
	char* Path;

	
	if (directory != NULL)
	{

		if (stat(directory, &st) == -1)
			return OSFileError_FolderNotFound;


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
			return OSFileError_FileNotFound;
		
	}else
	{
		Path = filePath;
		
		if (stat(Path, &st) == -1)
			return OSFileError_FileNotFound;
	}
	
	return OSFileError_NoError;
}

OSFileError OSFileExists(char* path)
{
	
	Path tempPath;

	PathInitialize(&tempPath, path);

	const OSFileError returnValue = OSFileExistsP(tempPath);

	PathDestruction(&tempPath);
	
	return returnValue;
}

OSFileError OSFileExistsP(Path path)
{
	return OSFileExists_splitParameter(path.directory, path.file);
}

OSFileError OSDirectoryExists(char* directory)
{

#ifdef OSUnix
	return OSFileError_NotImplemented;
#endif

	if (directory == NULL)
		return OSFileError_ContentIsNull;
	
	struct stat st = { 0 };
	char* Path;
	
	if (stat(directory, &st) == -1)
		return OSFileError_FolderNotFound;

	return OSFileError_NoError;
}

OSFileError OSFileWrite(char* path, char* content)
{
	Path tempPath;

	PathInitialize(&tempPath, path);

	const OSFileError returnValue = OSFileExistsP(tempPath);

	PathDestruction(&tempPath);

	return returnValue;
}

OSFileError OSFileWriteP(Path* path, char* content)
{

#ifdef OSUnix
	return OSFileError_NotImplemented;
#endif
	
	if (content == NULL)
		return OSFileError_ContentIsNull;

	const OSFileError fileExistOutput = OSFileExists_splitParameter(path->directory,path->file);
	
	if(fileExistOutput != OSFileError_NoError)
	{
		switch (fileExistOutput)
		{
			case OSFileError_FolderNotFound:
			{
				const OSFileError errorCode = OSDirectoryFullCreate(path->directory);
				
				if (errorCode != OSFileError_NoError)
					return errorCode;

				return OSFileWriteP(path, content);
			}
			case OSFileError_FileNotFound:
			{
				const OSFileError errorCode = OSFileCreate(path->fullPath);

				if (errorCode != OSFileError_NoError)
					return errorCode;
					
				return OSFileWriteP(path, content);
			}
			case OSFileError_NoFileExtension: 
			case OSFileError_ExtensionToShort:
			case OSFileError_CallocWentWrong:
			case OSFileError_AccessDenied:
			case OSFileError_PathNotFound:
				return fileExistOutput;

				//No Errors or impossible Errors 
			case OSFileError_NoError:
			case OSFileError_ContentIsNull:
			case OSFileError_FolderAlreadyExists:
				break;			
		}

		//if directory and File exists

		
		
	}
	
	return OSFileError_NoError;
}

OSFileError OSFileWriteBase(char* path, char* content)
{
	OSFileError returnValue = OSFileError_NoError;

	BOOL bErrorFlag = FALSE;
	DWORD dwBytesToWrite = (DWORD)strlen(content);
	DWORD dwBytesWritten = 0;
	HANDLE h_File = CreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h_File == INVALID_HANDLE_VALUE)
	{
		const DWORD lastError = GetLastError();
		CloseHandle(h_File);
		return WindowsErrorToOSFileError(lastError);
	}

	bErrorFlag = WriteFile(h_File, content, dwBytesToWrite, &dwBytesWritten, NULL);

	if (FALSE == bErrorFlag)
	{
		const DWORD lastError = GetLastError();
		returnValue = WindowsErrorToOSFileError(lastError);
	}
	else
	{
		// This is an error because a synchronous write that results in
		// success (WriteFile returns TRUE) should write all data as
		// requested. This would not necessarily be the case for
		// asynchronous writes.
		if (dwBytesWritten != dwBytesToWrite)
			returnValue = OSFileError_WrittenContentIsCorrupted;
	}

	CloseHandle(h_File);

	return returnValue;
}

OSFileError OSFileCreate(char* path)
{

#ifdef OSUnix
	return OSFileError_NotImplemented;
#endif
	
	OSFileError returnValue = OSFileError_NoError;

	#ifdef OSWindows
	
	wchar_t* w_path = stringToWString(path);

	//file to be opened //open for writing //share for writing //default security //Creates file if not exists //archive and impersonate client //no attribute template
	const HANDLE h_file = CreateFile(w_path, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_NEW,FILE_ATTRIBUTE_ARCHIVE | SECURITY_IMPERSONATION, NULL); 
	
	// Check the handle, then open...

	if (h_file == INVALID_HANDLE_VALUE)
	{
		const DWORD lastError = GetLastError();
		returnValue = WindowsErrorToOSFileError(lastError);
	}

	
	if (CloseHandle(h_file) == 0)
		returnValue = OSFileError_UnknownError;

	free(w_path);
	
	#endif
	
	return returnValue;
}

OSFileError OSFileDelete(char* path)
{

#ifdef OSUnix
	return OSFileError_NotImplemented;
#endif

	
	OSFileError returnValue = OSFileError_NoError;

	wchar_t* w_path = stringToWString(path);
	
	if (DeleteFile(w_path) == 0)
	{
		const DWORD lastError = GetLastError();
		returnValue = WindowsErrorToOSFileError(lastError);		
	}

	free(w_path);
	
	return returnValue;
}

OSFileError OSDirectoryCreate(char* directory)
{

#ifdef OSUnix
	return OSFileError_NotImplemented;
#endif

	
	OSFileError returnValue = OSFileError_NoError;

	
	#ifdef OSWindows
	
	wchar_t* w_directory = stringToWString(directory);

	
	returnValue = CreateDirectory(w_directory,NULL)? 0 : -1;

	if(returnValue != 0)
	{
		const DWORD lastError = GetLastError();
		returnValue = WindowsErrorToOSFileError(lastError);
	}
	
	free(w_directory);
	
	#endif
	

	
	return returnValue;
}

OSFileError OSDirectoryFullCreate(char* directory)
{

#ifdef OSUnix
	return OSFileError_NotImplemented;
#endif

	
	OSFileError returnValue = OSFileError_NoError;
	
	unsigned int counter = 0;

	if (directory[counter] == '\0')
		return OSFileError_PathNotFound;
	
	do
	{
		while (directory[counter] != '/' && directory[counter] != '\0')
		{
			counter++;
		}
		
		char* partDirectory = calloc(counter+1, sizeof(char));

		if (partDirectory == NULL)
			return OSFileError_CallocWentWrong;
		
		memcpy(partDirectory, directory, (counter) * sizeof(char));

		returnValue = OSDirectoryCreate(partDirectory);
		
		free(partDirectory);
				
	} 	while (directory[counter++] != '\0' && (returnValue == OSFileError_NoError || returnValue == OSFileError_FolderAlreadyExists));

	return returnValue;
}

OSFileError OSDirectoryDelete(char* directory)
{
#ifdef OSUnix
	return OSFileError_NotImplemented;
#endif

	
	OSFileError returnValue = OSFileError_NoError;
	
	wchar_t* w_directory = stringToWString(directory);
	
	if (RemoveDirectory(w_directory) == 0)
	{
		const DWORD lastError = GetLastError();
		returnValue = WindowsErrorToOSFileError(lastError);
	}

	free(w_directory);
	
	return returnValue;
}

OSFileError OSDirectoryForceDelete(char* directory)
{
	#ifdef OSUnix
	return OSFileError_NotImplemented;
	#endif
	
	OSFileError returnValue = OSFileError_NoError;
	
	List dirContent = EMPTYLIST;
	
	OSListAllFiles(&dirContent,directory);
	
	if(dirContent.size > 0)
	{
		for (int i = 0; i < dirContent.size; ++i)
		{
			Path* tempPath = PathListItemGet(&dirContent, i);

			if(returnValue != OSFileError_NoError)
				continue;
			
			if (tempPath != NULL)
			{
				if(tempPath->hasFile == 1)
					returnValue = OSFileDelete(tempPath->fullPath);
				else
				{
					const OSFileError tempErrorCode = OSDirectoryDelete(tempPath->fullPath);

					if (tempErrorCode == OSFileError_DirectoryNotEmpty)
						returnValue = OSDirectoryForceDelete(tempPath->fullPath);
					else
						if (tempErrorCode != OSFileError_NoError)
							returnValue = tempErrorCode;
					
				}
			}
		}
	}
	
	PathListDestruction(&dirContent);

	if (returnValue == OSFileError_NoError)
		returnValue = OSDirectoryDelete(directory);
	
	return returnValue;
}

void OSListAllFiles(List* pathList,char * directory)
{
#ifdef OSUnix
	return OSFileError_NotImplemented;
#endif
	

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
}

#ifdef OSWindows
static wchar_t* stringToWString(char* string)
{
	const int pathLength = strlen(string) + 1;

	wchar_t* w_path = calloc(pathLength, sizeof(wchar_t));

	mbstowcs(w_path, string, pathLength);

	return w_path;
}

static OSFileError WindowsErrorToOSFileError(unsigned long rawError)
{
	switch (rawError)
	{
	case ERROR_ACCESS_DENIED:
		return OSFileError_AccessDenied;
	case ERROR_ALREADY_EXISTS:
		return OSFileError_FolderAlreadyExists;
	case ERROR_DIRECTORY:
		return OSFileError_InvalidDirectory;
	case ERROR_DIR_NOT_EMPTY:
		return OSFileError_DirectoryNotEmpty;
	case ERROR_FILE_NOT_FOUND:
		return OSFileError_FileNotFound;
	case ERROR_FILE_EXISTS:
		return OSFileError_FileAlreadyExists;
	case ERROR_INVALID_NAME:
		return OSFileError_InvalidDirectory;
	case ERROR_PATH_NOT_FOUND:
		return OSFileError_PathNotFound;
	case ERROR_SHARING_VIOLATION:
		return OSFileError_FileIsCurrentlyInUse;
	default:
		return OSFileError_UnknownError;
	}
}
#endif




