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
            return CommandErrorSuccessful;

        default:
            return CommandErrorNotSet;
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

        switch (fileError != OSError_NoError)
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

        return CommandErrorSuccessful;
    }
    else
    {
        return CommandErrorAccessLocked;
    }
}

CommandError UserLockFile(int clientID, char* fileName)
{
    char canModify = 0;
    char doesFileExist = OSFileExists(fileName) == OSError_NoError;

    if (doesFileExist)
    {
        return CommandErrorFileDoesNotExist;
    }

    canModify = UserCanModifyFile(clientID, fileName);

    ChangeFileExtension(fileName, FileExtensionLocked);

    if (canModify)
    {
        char dataBuffer[256];

        sprintf(dataBuffer, "%i", clientID);

        OSError fileError = OSFileForceWrite(fileName, dataBuffer, WriteMode_Overwrite);

        return CommandErrorSuccessful;
    }
    else
    {
        return CommandErrorAccessLocked;
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
                return CommandErrorSuccessful;
            }
            case OSError_DirectoryOrFileNotFound:
            {
                return CommandErrorFileDoesNotExist;
            }
        }
    }
    else
    {
        return CommandErrorAccessLocked;
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
                return CommandErrorSuccessful;
            }
        }
    }
    else
    {
        return CommandErrorAccessLocked;
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
                return CommandErrorSuccessful;

            case OSError_DirectoryOrFileNotFound:
                return CommandErrorFileDoesNotExist;
        }
    }
    else
    {
        return CommandErrorAccessLocked;
    }
}

#ifdef OSWindows
//Todo: Dennis
static CommandError executeProgram(char* program, char** output)
{

    output = "Hallo";
    return CommandErrorSuccessful;
}
#endif

#ifdef OSUnix
//Todo: Jona 
static CommandError executeProgram(char* program, char** output)
{
    output = "Hallo";
    return CommandErrorSuccessful;
}
#endif

//Todo: Dennis
CommandError UserOpenProgram(char* filePath, char* programName)
{
    char* output;
	
    CommandError returnValue = executeProgram("Hallo", &output) == CommandErrorSuccessful;
	
    if (returnValue != CommandErrorSuccessful)
        return returnValue;

    //Todo: Output write in File

	
    return returnValue;
}

