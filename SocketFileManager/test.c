#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Path.h"
#include "FileManagerErrorCodes.h"
#include "FileManager.h"


int main()
{
	
	//FM_WriteInFile(&testPath,"Lukkkkkkas");

	//const FileManagerErrorCode returnCode = FM_CreateFile("C:/Users/Merdo/Desktop/a.txt");
	//const FileManagerErrorCode returnCode2 = FM_DeleteFile("C:/Users/Merdo/Desktop/a.docx");
	//const FileManagerErrorCode returnCode2 = FM_ForceDeleteDir("C:/Users/Merdo/Desktop/AA/*");

	//Path* returnPath = FM_ListAllFiles("C:/Users/Merdo/Desktop/AA/*");
	Path* returnPath = FM_ListAllFiles("D:/*");
	//printf("create: %s\n", FileManagerErrorCodeToString(returnCode));
	//printf("delete: %s\n", FileManagerErrorCodeToString(returnCode2));


	
	printf("\n\n");
	
#ifdef OSWindows
	system("pause");
#else
	printf("Terminated\n");
#endif
}
