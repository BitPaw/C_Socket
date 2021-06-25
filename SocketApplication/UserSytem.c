#include "UserSytem.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include "../SocketFileManager/FileManager.h"


char UserCanModifyFile(int clientID, char* fileName)
{
    if (fileName == 0)
    {
        return CommandNoFilePath;
    }

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
    if (fileName == 0)
    {
        return CommandNoFilePath;
    }

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
    if (fileName == 0)
    {
        return CommandNoFilePath;
    }
    char dataBuffer[255];
    char doesFileExist = OSFileExists(fileName) == OSError_NoError;
    char* fileContent = 0;
    char seperator = '\n';
    unsigned int ParseBeginIndex = 0;
    int dataIndex = 0;

    (*amountOfElements) = 0;
    (*targetArray) = 0;

    memset(dataBuffer, 0, 255);
    memcpy(dataBuffer, fileName, strlen(fileName) * sizeof(char));

    ChangeFileExtension(dataBuffer, FileExtensionSubscribed);

    if (doesFileExist)
    {
        OSError fileError = OSFileRead(dataBuffer, &fileContent);

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
                memcpy(socketIDText, &fileContent[0] + ParseBeginIndex, i - ParseBeginIndex);

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
    if (fileName == 0)
    {
        return CommandNoFilePath;
    }

    char dataBuffer[255];
    char canModify = UserCanModifyFile(clientID, fileName);

    memset(dataBuffer, 0, 255);
    memcpy(dataBuffer, fileName, strlen(fileName) * sizeof(char));

    ChangeFileExtension(dataBuffer, FileExtensionLocked);

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
    if (fileName == 0)
    {
        return CommandNoFilePath;
    }

    char canModify = 0;
    char doesFileExist = OSFileExists(fileName) == OSError_NoError;
    char dataBuffer[255];

    if (!doesFileExist)
    {
        return CommandFileDoesNotExist;
    }

    canModify = UserCanModifyFile(clientID, fileName);

    memset(dataBuffer, 0, 255);
    memcpy(dataBuffer, fileName, strlen(fileName) * sizeof(char));

    ChangeFileExtension(dataBuffer, FileExtensionLocked);

    if (canModify)
    {
        char clientIDBuffer[256];

        sprintf(clientIDBuffer, "%i", clientID);

        OSError fileError = OSFileForceWrite(dataBuffer, clientIDBuffer, WriteMode_Overwrite);

        return CommandSuccessful;
    }
    else
    {
        return CommandAccessLocked;
    }
}

CommandError UserReadFromFile(int clientID, char* fileName, char** content)
{
    if (fileName == 0)
    {
        return CommandNoFilePath;
    }

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
    if (fileName == 0)
    {
        return CommandNoFilePath;
    }

    if (content == 0)
    {
        return CommandNoFileData;
    }

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
    if (fileName == 0)
    {
        return CommandNoFilePath;
    }

    char canModify = UserCanModifyFile(clientID, fileName);

    if (canModify)
    {
	    OSError fileError = OSFileDelete(fileName);
        if (fileError == OSError_DirectoryOrFileNotFound)
        {
            fileName[strlen(fileName)-4] = '\0';
	        fileError = OSDirectoryForceDelete(fileName);
        }
            
    	
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
	
    const unsigned int programNameLength = strlen(programName);
    const unsigned int fileNameLength = strlen(fileName);
    const unsigned int redirectLength = strlen(" >");
    const unsigned int redirect2Length = strlen(" 2>&1");
    char* programWithErrorPipe = calloc(programNameLength + fileNameLength + redirectLength + redirect2Length + 1, sizeof(char));
    memcpy(programWithErrorPipe, programName, sizeof(char) * programNameLength);
    memcpy(programWithErrorPipe + programNameLength, " > ", sizeof(char) * redirectLength);
    memcpy(programWithErrorPipe + programNameLength + redirectLength , fileName, sizeof(char) * fileNameLength);
    memcpy(programWithErrorPipe + programNameLength + redirectLength + fileNameLength, " 2>&1", sizeof(char) * redirect2Length);

	
	OSFileDelete(fileName);
	
	
    #ifdef OSWindows
    FILE* pipe = _popen(programWithErrorPipe, "r");
    #elif defined(OSUnix)
    FILE* pipe = popen(programWithErrorPipe, "r");
    #endif

    free(programWithErrorPipe);
	
    if (!pipe)
    {
        return CommandPipeCreationFailure;
    }      

    

    if(!UserCanModifyFile(clientID, fileName))
        return CommandAccessLocked;

	
    /* Close pipe and print return value of pPipe. */

    #ifdef OSWindows
        int returnValue = _pclose(pipe);
    #elif defined(OSUnix)
        int returnValue = pclose(pipe);
    #endif

    if (returnValue == -1)
    {
        return CommandPipeClosingFailure;
    }      
    if (returnValue != 0)
    {
        return CommandPipeProgramFailed;
    }

    return CommandSuccessful;
}