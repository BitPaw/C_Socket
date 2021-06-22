#include "CommandToken.h"
#include <stdlib.h>
#include <string.h>

void CommandTokenInitialize(CommandToken* commandToken)
{
    commandToken->ClientSocketID = -1;
    commandToken->CommandRaw = 0;
    commandToken->CommandType = CommandInvalid;
    commandToken->Key = 0;
    commandToken->Value = 0;
}

void CommandTokenClear(CommandToken* commandToken)
{
    if (commandToken->CommandRaw != 0)
    {
        free(commandToken->CommandRaw);
        CommandTokenInitialize(commandToken);
    }
}

unsigned char CommandTokenParse(CommandToken* commandToken, char* message)
{
    int length = 0;
    const char seperator = ';';
    int seperatorCounter = 0;
    int seperatorIndex[2] = {-1, -1};
    int stringLength = strnlen(message, 1024);
    char* dataString = 0;
        
    CommandTokenClear(commandToken);

    commandToken->CommandType = ParseCommand(message);

    switch (commandToken->CommandType)
    {
        case CommandMinecraftServerList:
        case CommandHTTPRequest:
        {
            return 0;
        }
    }

    commandToken->CommandRaw = calloc(stringLength + 1, sizeof(char));
    dataString = commandToken->CommandRaw;

    if (dataString == 0)
    {
        return 0;
    }

    memcpy(dataString, message, stringLength * sizeof(char));

    for (; dataString[length] != '\0' ; length++)
    {
        char isSeperator = dataString[length] == seperator;

        if (isSeperator)
        {
            if (seperatorCounter == 2)
            {
                return 1;
            }

            seperatorIndex[seperatorCounter++] = length;
            dataString[length] = '\0';
        }
    }

    if (seperatorIndex[0] != -1)
    {
        commandToken->Key = &dataString[seperatorIndex[0] + 1];
    }

    if (seperatorIndex[1] != -1)
    {
        commandToken->Value = &dataString[seperatorIndex[1] + 1];
    }
    
    return 0;
}

Command ParseCommand(char* command)
{   
   

    /*
    *  unsigned int length = 0;
    * 
    for ( ; command[length] != '\0' && length < 3; length++)
    {
        char character = command[length];
        char isLowerCase = character >= 'a' && character <= 'z';

        if (isLowerCase)
        {
            command[length] -= 32; // toUpperCase
        }

            if (length < 3)
    {
        return CommandInvalid;
    }
    }*/

    if (memcmp("\x10", command, 1) == 0)
        return CommandMinecraftServerList;

    if (memcmp("GET /", command, 5) == 0)
        return CommandHTTPRequest;

    if (memcmp("GET;", command, 4) == 0)
        return CommandFileDataGet;

    if (memcmp("PUT;", command, 4) == 0) 
        return CommandFileDataPut;

    if (memcmp("DEL;", command, 4) == 0)
        return CommandFileDelete;

    if (memcmp("BEG;", command, 4) == 0)
        return CommandFileLock;

    if (memcmp("END;", command, 4) == 0)
        return CommandFileUnlock;

    if (memcmp("SUB;", command, 4) == 0)         
        return CommandFileChangeSubscribe;

    if (memcmp("OP;", command, 3) == 0)
        return CommandOpenProgram;

    if (memcmp("QUIT", command, 4) == 0) 
        return CommandQuit;

    return CommandInvalid;
}

/*
Compares CommandToken and returns how much they line up.
0 if they are the same.
-1 if they different in 1 Values.
-2 if they different in 2 Values.
-3 if they different in 3 Values.
-4 if they different in 4 Values.
-5 if they are Totaly different.
*/
int CommandTokenCompare(CommandToken* commandToken1, CommandToken* commandToken2)
{
    int result = 0;

    if (commandToken1->CommandType != commandToken2->CommandType)
    {
        result--;
    }

    char samelengthKey = strlen(commandToken1->Key) == strlen(commandToken2->Key);

    if (samelengthKey)
    {
        if (strcmp(commandToken1->Key,commandToken2->Key))
        {
            result--;
        }        
    }
    else
    {
        result--;
    }

    char samelengthValue = strlen(commandToken1->Value) == strlen(commandToken2->Value);

    if (samelengthValue)
    {
        if (strcmp(commandToken1->Value, commandToken2->Value))
        {
            result--;
        }
    }
    else
    {
        result--;
    }

    if (result != 0)
    {
        result--;
    }

    if (commandToken1->ClientSocketID != commandToken2->ClientSocketID)
    {
        result--;
    }

    return result;
}


