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




FileManagerErrorCode FM_DoesFileExist_FULL(char* directory, const char* filePath)
{
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

		if (stat(Path, &st) == -1)
			return FileManager_FileNotFound;

	}else
	{
		Path = filePath;
		
		if (stat(Path, &st) == -1)
			return FileManager_FileNotFound;
	}


	
	return FileManager_NoError;
}

FileManagerErrorCode FM_DoesFileExist(char* path )
{
	int selector = 0;
	int length = 0;	
	while(path[length] != '\0')
	{		
		if (path[length] == '/')
			selector = length;


		length++;
	}
	
	
	char* file;
	
	if (selector == 0)
	{
		file = path + selector;
		path = NULL;
	}
	else
	{
		file = path + selector + 1;
		path[selector] = '\0';
	}
		
		
	return FM_DoesFileExist_FULL(path ,file );
}

FileManagerErrorCode FM_WriteInFile(Path* path, char* content)
{
	if (content == NULL)
		return FileManager_ContentIsNull;

	const FileManagerErrorCode fileExistOutput = FM_DoesFileExist_FULL(path->directory,path->file);
	
	if(fileExistOutput != FileManager_NoError)
	{
		switch (fileExistOutput)
		{
			case FileManager_FolderNotFound:
			{
				const FileManagerErrorCode errorCode = FM_CreateFullDir(path->directory);
				
				if (errorCode != FileManager_NoError)
					return errorCode;

				return FM_WriteInFile(path, content);
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

FileManagerErrorCode FM_CreateFile(char* path)
{
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

FileManagerErrorCode FM_DeleteFile(char* path)
{
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

FileManagerErrorCode FM_CreateDir(char* directory)
{
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

FileManagerErrorCode FM_CreateFullDir(char* directory)
{
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

		returnValue = FM_CreateDir(partDirectory);
		
		free(partDirectory);
				
	} 	while (directory[counter++] != '\0' && (returnValue == FileManager_NoError || returnValue == FileManager_FolderAlreadyExists));

	return returnValue;
}

FileManagerErrorCode FM_DeleteDir(char* directory)
{
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

FileManagerErrorCode FM_ForceDeleteDir(char* directory)
{
	FileManagerErrorCode returnValue = FileManager_NoError;
	
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(directory, &data);
	
	if (hFind != INVALID_HANDLE_VALUE) {
		
		do {
			
			printf("%s \n", &data.cFileName);
			
		} while (FindNextFileA(hFind, &data));
		
		const unsigned int lastError = GetLastError();

		if (lastError != ERROR_NO_MORE_FILES)
			returnValue = WindowsErrorToFileManagerError(lastError);

		
		FindClose(hFind);
	}
	
	
	return returnValue;
}

Path* FM_ListAllFiles(char * directory)
{
	Path* returnValue;

	int selector;
	const int directoryLength = strlen(directory);

	if (directoryLength < 2)
		return NULL;
	
	const char hasRightEnding = (directory[directoryLength] == '*' && directory[directoryLength - 1] == '/');
		
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(directory, &data);

	if (hFind != INVALID_HANDLE_VALUE) {

		int fileCount = (directoryLength > 4? -1:1);

		while (FindNextFileA(hFind, &data)) 
		{
			fileCount++;
		} 

		
		
		hFind = FindFirstFileA(directory, &data);
		printf("%i \n", fileCount);

		//returnValue = ca
		
		do {
			const int compareLenght = sizeof(char) * strlen(&data.cFileName);
			if(memcmp(&data.cFileName,".", compareLenght) != 0 && memcmp(&data.cFileName, "..", compareLenght) != 0)
				printf("%s \n", &data.cFileName);
			
		} while (FindNextFileA(hFind, &data));
		
		const unsigned int lastError = GetLastError();

		if (lastError != ERROR_NO_MORE_FILES)
			returnValue = NULL;

		
		FindClose(hFind);
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




