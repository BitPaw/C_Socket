#include "CommandManager.h"
#include <stdio.h>

char* LoadHTMLFile(char* filePath)
{
    FILE* file = fopen(filePath, "r");
    int fileLength = -1;
    char* string = 0;
    const char* htmlResponseTag = "HTTP/1.0 200 OK\r\n\r\n";
    const int htmlResponselength = 19;

    if (file == NULL)
    {
        return 0; // File does not exist
    }

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);

    string = calloc(fileLength + htmlResponseTag + 1, sizeof(char));

    if (string == NULL)
    {
        return 0; // calloc failed
    }

    memcpy(string, htmlResponseTag, htmlResponselength);
    fread(string + htmlResponselength, 1, fileLength, file);

    fclose(file);

    return string;
}

char* LoadFile(char* filePath)
{
    FILE* file = fopen(filePath, "r");
    int fileLength = -1;
    char* string = 0;

    /* quit if the file does not exist */
    if (file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);

    string = calloc(fileLength + 1, sizeof(char));

    fread(string, 1, fileLength, file);

    fclose(file);

    return string;
}


FileError FileDataPut(char* filePath, char* dataToWrite)
{
	return FileNoError;
}

FileError FileDataGet(char* filePath, char* targetToWriteTo)
{
	return FileNoError;
}

FileError FileDelete(char* filePath)
{
	return FileNoError;
}

FileError FileLock(char* filePath)
{
	return FileNoError;
}

FileError FileUnlock(char* filePath)
{
	return FileNoError;
}

FileError FileChangePublish(char* filePath)
{
	return FileNoError;
}

FileError FileChangeSubscribe(char* filePath)
{
	return FileNoError;
}

FileError ProgramOpen(char* programName)
{
	return FileNoError;
}

void ApplicationQuit()
{
	// ??
}

void SendHTTPResponse(Server* server, int socketID)
{
	char* htmlFile = LoadHTMLFile("index.html");

	ServerSendToClient(server, socketID, htmlFile);
	ServerKickClient(server, socketID);

	free(htmlFile);
}