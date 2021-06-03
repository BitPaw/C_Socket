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


FileManagerErrorCode FM_FileExists_split(char* directory, const char* filePath)
{
	
#ifdef OSUnix
	return FileManager_NotImplemented;
#endif
		
	
	//checks if '.' is in file
	int length = 0;
	while (filePath[length] != '.')
		if (filePath[++length] == '\0')
			return FileManager_NoFileExtension;

	//checks if more then 0 char before .
	if (length < 1)
		return FileManager_ExtensionToShort;

	//checks if more then 0 char after .
	if(filePath[++length] == '\0')
		return FileManager_ExtensionToShort;

	
	//checks File exists
	struct stat st = { 0 };
	char* Path;

	
	if (directory != NULL)
	{

		if (stat(directory, &st) == -1)
			return FileManager_FolderNotFound;


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
			return FileManager_FileNotFound;
		
	}else
	{
		Path = filePath;
		
		if (stat(Path, &st) == -1)
			return FileManager_FileNotFound;
	}
	
	return FileManager_NoError;
}

FileManagerErrorCode FM_FileExists(char* path )
{
	char* tempPath = calloc(strlen(path)+1,sizeof(char));
	strcpy_s(tempPath, strlen(path) + 1,path);
		
	int selector = 0;
	int length = 0;	
	while(tempPath[length] != '\0')
	{		
		if (tempPath[length] == '/')
			selector = length;


		length++;
	}
	
	
	char* file;
	
	if (selector == 0)
	{
		file = tempPath + selector;
		tempPath = NULL;
	}
	else
	{
		file = tempPath + selector + 1;
		tempPath[selector] = '\0';
	}
		
		
	FileManagerErrorCode returnValue = FM_FileExists_split(tempPath,file );

	free(tempPath);

	return returnValue;
}

FileManagerErrorCode FM_DirExists(char* directory)
{

#ifdef OSUnix
	return FileManager_NotImplemented;
#endif

	if (directory == NULL)
		return FileManager_ContentIsNull;
	
	struct stat st = { 0 };
	char* Path;
	
	if (stat(directory, &st) == -1)
		return FileManager_FolderNotFound;

	return FileManager_NoError;
}

FileManagerErrorCode FM_FileWrite(Path* path, char* content)
{

#ifdef OSUnix
	return FileManager_NotImplemented;
#endif
	
	if (content == NULL)
		return FileManager_ContentIsNull;

	const FileManagerErrorCode fileExistOutput = FM_FileExists_split(path->directory,path->file);
	
	if(fileExistOutput != FileManager_NoError)
	{
		switch (fileExistOutput)
		{
			case FileManager_FolderNotFound:
			{
				const FileManagerErrorCode errorCode = FM_DirFullCreate(path->directory);
				
				if (errorCode != FileManager_NoError)
					return errorCode;

				return FM_FileWrite(path, content);
			}
			case FileManager_FileNotFound:
				//TODO: Write in File 
				break;
				
			case FileManager_NoFileExtension: 
			case FileManager_ExtensionToShort:
			case FileManager_CallocWentWrong:
			case FileManager_AccessDenied:
			case FileManager_PathNotFound:
				return fileExistOutput;

				//No Errors or impossible Errors 
			case FileManager_NoError:
			case FileManager_ContentIsNull:
			case FileManager_FolderAlreadyExists:
				break;			
		}
	}
	
	return FileManager_NoError;
}

FileManagerErrorCode FM_FileCreate(char* path)
{

#ifdef OSUnix
	return FileManager_NotImplemented;
#endif
	
	FileManagerErrorCode returnValue = FileManager_NoError;

	#ifdef OSWindows
	
	wchar_t* w_path = stringToWString(path);

	//file to be opened //open for writing //share for writing //default security //Creates file if not exists //archive and impersonate client //no attribute template
	const HANDLE h_file = CreateFile(w_path, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_NEW,FILE_ATTRIBUTE_ARCHIVE | SECURITY_IMPERSONATION, NULL); 
	
	// Check the handle, then open...

	if (h_file == INVALID_HANDLE_VALUE)
	{
		const DWORD lastError = GetLastError();
		returnValue = WindowsErrorToFileManagerError(lastError);
	}

	
	if (CloseHandle(h_file) == 0)
		returnValue = FileManager_UnknownError;

	free(w_path);
	
	#endif
	
	return returnValue;
}

FileManagerErrorCode FM_FileDelete(char* path)
{

#ifdef OSUnix
	return FileManager_NotImplemented;
#endif

	
	FileManagerErrorCode returnValue = FileManager_NoError;

	wchar_t* w_path = stringToWString(path);
	
	if (DeleteFile(w_path) == 0)
	{
		const DWORD lastError = GetLastError();
		returnValue = WindowsErrorToFileManagerError(lastError);		
	}

	free(w_path);
	
	return returnValue;
}

FileManagerErrorCode FM_DirCreate(char* directory)
{

#ifdef OSUnix
	return FileManager_NotImplemented;
#endif

	
	FileManagerErrorCode returnValue = FileManager_NoError;

	
	#ifdef OSWindows
	
	wchar_t* w_directory = stringToWString(directory);

	
	returnValue = CreateDirectory(w_directory,NULL)? 0 : -1;

	if(returnValue != 0)
	{
		const DWORD lastError = GetLastError();
		returnValue = WindowsErrorToFileManagerError(lastError);
	}
	
	free(w_directory);
	
	#endif
	
	#ifdef OSUnix

	
	#endif
	
	return returnValue;
}

FileManagerErrorCode FM_DirFullCreate(char* directory)
{

#ifdef OSUnix
	return FileManager_NotImplemented;
#endif

	
	FileManagerErrorCode returnValue = FileManager_NoError;
	
	unsigned int counter = 0;

	if (directory[counter] == '\0')
		return FileManager_PathNotFound;
	
	do
	{
		while (directory[counter] != '/' && directory[counter] != '\0')
		{
			counter++;
		}
		
		char* partDirectory = calloc(counter+1, sizeof(char));

		if (partDirectory == NULL)
			return FileManager_CallocWentWrong;
		
		memcpy(partDirectory, directory, (counter) * sizeof(char));

		returnValue = FM_DirCreate(partDirectory);
		
		free(partDirectory);
				
	} 	while (directory[counter++] != '\0' && (returnValue == FileManager_NoError || returnValue == FileManager_FolderAlreadyExists));

	return returnValue;
}

FileManagerErrorCode FM_DirDelete(char* directory)
{
#ifdef OSUnix
	return FileManager_NotImplemented;
#endif

	
	FileManagerErrorCode returnValue = FileManager_NoError;
	
	wchar_t* w_directory = stringToWString(directory);
	
	if (RemoveDirectory(w_directory) == 0)
	{
		const DWORD lastError = GetLastError();
		returnValue = WindowsErrorToFileManagerError(lastError);
	}

	free(w_directory);
	
	return returnValue;
}

FileManagerErrorCode FM_DirForceDelete(char* directory)
{
	#ifdef OSUnix
	return FileManager_NotImplemented;
	#endif

	
	FileManagerErrorCode returnValue = FileManager_NoError;
	
	List dirContent;

	PathListInitialize(&dirContent, 1);

	FM_ListAllFiles(&dirContent,directory);

	PathListToString(&dirContent);

	
	if(dirContent.size > 0)
	{
		for (int i = 0; i < dirContent.size; ++i)
		{
			Path* tempPath = PathListItemGet(&dirContent, i);
			
			if (tempPath != NULL)
			{
				if(tempPath->hasFile == 1)
					FM_FileDelete(tempPath->fullPath);
				else
				{
					FileManagerErrorCode tempErrorCode = FM_DirDelete(tempPath->fullPath);

					if (tempErrorCode == FileManager_DirectoryNotEmpty)
					{
						FM_DirForceDelete(tempPath->fullPath);
						FM_DirDelete(tempPath->fullPath);
					}
				}
			}
		}
	}
	
	PathListDestruction(&dirContent);

	FM_DirDelete(directory);
	
	return returnValue;
}

void FM_ListAllFiles(List* emptyList,char * directory)
{
#ifdef OSUnix
	return FileManager_NotImplemented;
#endif
	

	int selector;
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
	

		PathListInitialize(emptyList, fileCount);

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
				PathListItemAdd(emptyList, newPath);

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

static FileManagerErrorCode WindowsErrorToFileManagerError(unsigned long rawError)
{
	switch (rawError)
	{
	case ERROR_ACCESS_DENIED:
		return FileManager_AccessDenied;
	case ERROR_ALREADY_EXISTS:
		return FileManager_FolderAlreadyExists;
	case ERROR_DIRECTORY:
		return FileManager_InvalidDirectory;
	case ERROR_DIR_NOT_EMPTY:
		return FileManager_DirectoryNotEmpty;
	case ERROR_FILE_NOT_FOUND:
		return FileManager_FileNotFound;
	case ERROR_FILE_EXISTS:
		return FileManager_FileAlreadyExists;
	case ERROR_INVALID_NAME:
		return FileManager_InvalidDirectory;
	case ERROR_PATH_NOT_FOUND:
		return FileManager_PathNotFound;
	case ERROR_SHARING_VIOLATION:
		return FileManager_FileIsCurrentlyInUse;
	default:
		return FileManager_UnknownError;
	}
}
#endif




