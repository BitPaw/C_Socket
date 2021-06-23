#include "UserSytem.h"
#include "../SocketFileManager/FileManager.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char UserCanModifyFile(int clientID, char* fileName)
{
    char lockFilePath[255];
    char canModify = 0;
    char doesFileExists = 0;

    memset(lockFilePath, 0, 255);
    memcpy(lockFilePath, fileName, strlen(fileName));

    ChangeFileExtension(lockFilePath, FileExtensionLocked);

    doesFileExists = OSFileExists(lockFilePath) == OSError_NoError;

    if (doesFileExists)
    {
        char* data = 0;

        OSError fileError = OSFileRead(lockFilePath, &data);

        int id = atoi(data);

        free(data);

        return id == clientID;
    }
    else
    {
        return 1;
    }
}

CommandError UserSubscribeToFile(int clientID, char* fileName)
{
    ChangeFileExtension(fileName, FileExtensionSubscribed);

    char doesFileExist = OSFileExists(fileName) == OSError_NoError;
    char dataBuffer[255];
    char* dataContext = doesFileExist ? "%i\n" : "%i\n";

    memset(dataBuffer, 0, 255);

    sprintf(dataBuffer, dataContext, clientID);  

    OSError fileError = OSFileForceWrite(fileName, dataBuffer, WriteMode_AddToEnd);

    switch (fileError)
    {
        case OSError_NoError:
            return CommandSuccessful;

        default:
            return CommandFileWriteFailure;
    }
}

CommandError UserUnSubscribeToFile(int clientID, char* fileName)
{
    // unused, will/is not implemented
}

void UserUnlockAllFiles(int clientID)
{
    // ToDo, implement

    // Delete all files that the user used. So that he can not block others forever.
    
    // Look into all .lck files, delete the files that contain the given 'clientID'.
}

void UserGetAllSubscribers(int actorClientID, char* fileName, int** targetArray, int* amountOfElements)
{
    char doesFileExist = OSFileExists(fileName) == OSError_NoError;
    char* fileContent = 0;
    char seperator = '\n';
    unsigned int ParseBeginIndex = 0;
    int dataIndex = 0;

    (*amountOfElements) = 0;
    (*targetArray) = 0;

    ChangeFileExtension(fileName, FileExtensionSubscribed);

    if (doesFileExist)
    {
        OSError fileError = OSFileRead(fileName, &fileContent);

        if (fileError != OSError_NoError)
        {
            return;
        }

        for (int i = 0; fileContent[i] != '\0';  i++)
        {
            char isSeperator = fileContent[i] == seperator;

            if (isSeperator)
            {
                (*amountOfElements)++;
            }
        }

        (*targetArray) = calloc((*amountOfElements), sizeof(int));

        for (int i = 0; fileContent[i] != '\0';  i++)
        {
            char isSeperator = fileContent[i] == seperator;

            if (isSeperator)
            {
                char socketIDText[255];

                memset(socketIDText, 0, 255);
                memcpy(socketIDText, &fileContent[0] , i - ParseBeginIndex);

                int value = atoi(socketIDText);

                (*targetArray)[dataIndex++] = value;

                ParseBeginIndex = i + 1;
            }
        }
    }
}

void ChangeFileExtension(char* fileName, char* fileExtension)
{
    unsigned int i = strlen(fileName);

    memcpy(fileName + i - 3, fileExtension, 3);
}

CommandError UserUnlockFile(int clientID, char* fileName)
{
    char canModify = UserCanModifyFile(clientID, fileName);

    ChangeFileExtension(fileName, FileExtensionLocked);

    if (canModify)
    {
        OSError fileError = OSFileDelete(fileName);

        return CommandSuccessful;
    }
    else
    {
        return CommandAccessLocked;
    }
}

CommandError UserLockFile(int clientID, char* fileName)
{
    char canModify = 0;
    char doesFileExist = OSFileExists(fileName) == OSError_NoError;

    if (!doesFileExist)
    {
        return CommandFileDoesNotExist;
    }

    canModify = UserCanModifyFile(clientID, fileName);

    ChangeFileExtension(fileName, FileExtensionLocked);

    if (canModify)
    {
        char dataBuffer[256];

        sprintf(dataBuffer, "%i", clientID);

        OSError fileError = OSFileForceWrite(fileName, dataBuffer, WriteMode_Overwrite);

        return CommandSuccessful;
    }
    else
    {
        return CommandAccessLocked;
    }
}

CommandError UserReadFromFile(int clientID, char* fileName, char** content)
{
    char canModify = UserCanModifyFile(clientID, fileName);

    if (canModify)
    {
        OSError fileError = OSFileRead(fileName, content);

        switch (fileError)
        {
            case OSError_NoError:
            {
                return CommandSuccessful;
            }
            case OSError_DirectoryOrFileNotFound:
            {
                return CommandFileDoesNotExist;
            }
        }
    }
    else
    {
        return CommandAccessLocked;
    }
}

CommandError UserWriteInFile(int clientID, char* fileName, char* content)
{
    char canModify = UserCanModifyFile(clientID, fileName);

    if (canModify)
    {
        OSError fileError = OSFileForceWrite(fileName, content, WriteMode_Overwrite);

        switch (fileError)
        {
            case OSError_NoError:
            {
                return CommandSuccessful;
            }
        }
    }
    else
    {
        return CommandAccessLocked;
    }
}

CommandError UserDeleteFile(int clientID, char* fileName)
{
    char lockFilePath[255];
    char canModify = 0;

    memcpy(lockFilePath, fileName, strlen(fileName));

    ChangeFileExtension(lockFilePath, FileExtensionLocked);

    canModify = UserCanModifyFile(clientID, lockFilePath);

    if (canModify)
    {
        OSError fileError = OSFileDelete(fileName);

        switch (fileError)
        {
            case OSError_NoError:
                return CommandSuccessful;

            case OSError_DirectoryOrFileNotFound:
                return CommandFileDoesNotExist;
        }
    }
    else
    {
        return CommandAccessLocked;
    }
}

CommandError UserOpenProgram(int clientID, char* fileName, char* programName)
{
    char psBuffer[256];

    #ifdef OSWindows
    FILE* pipe = _popen(programName, "rt");
    #elif defined(OSUnix)
    FILE* pipe = popen(programName, "r");
    #endif

    if (!pipe)
    {
        return CommandPipeCreationFailure;
    }      

    OSFileDelete(fileName);

    if(!UserCanModifyFile(clientID, fileName))
        return CommandAccessLocked;
	
    /* Read pipe until end of file, or an error occurs. */
    while (fgets(psBuffer, 256, pipe))
    {

        const OSError returnError = OSFileForceWrite(fileName, psBuffer, WriteMode_AddToEnd);

		if(returnError != OSError_NoError)
			return CommandFileWriteFailure;
                 
    }

    /* Close pipe and print return value of pPipe. */
    if (feof(pipe))
    { 
    #ifdef OSWindows
        int returnValue = _pclose(pipe);
    #elif defined(OSUnix)
        int returnValue = pclose(pipe);
    #endif

        if (returnValue != 0)
        {
            return CommandPipeClosingFailure;
        }      
    }
    else
    {
        return CommandPipeReadError;
    }

    return CommandSuccessful;
}