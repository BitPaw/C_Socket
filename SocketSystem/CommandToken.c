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

unsigned char CommandTokenParse(CommandToken* commandToken, char* dataString)
{
    int length = 0;
    const char seperator = ';';
    int seperatorCounter = 0;
    int seperatorIndex[2];
        
    CommandTokenClear(commandToken);

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

    commandToken->Key = &dataString[seperatorIndex[0] + 1];
    commandToken->Value = &dataString[seperatorIndex[1] + 1];

    // Copy raw String
    commandToken->CommandRaw = calloc(length+1 , sizeof(char));
    memcpy(commandToken->CommandRaw, dataString, length);   

    commandToken->CommandType = ParseCommand(dataString);
    
    return 0;
}

Command ParseCommand(char* command)
{
    if (memcmp("GET", command, 3) == 0)
        return CommandGet;

    if (memcmp("PUT", command, 3) == 0) 
        return CommandPut;

    if (memcmp("DEL", command, 3) == 0)
        return CommandDelete;

    if (memcmp("ULC", command, 3) == 0) 
        return CommandLockFile;

    if (memcmp("LCK", command, 3) == 0)
        return CommandUnlockFile;

    if (memcmp("PUB", command, 3) == 0)
        return CommandPublish;

    if (memcmp("SUB", command, 3) == 0)         
        return CommandSubscribe;

    if (memcmp("OPG", command, 3) == 0)
        return CommandOpenProgram;

    if (memcmp("QUIT", command, 4) == 0) 
        return CommandQuit;

    return CommandInvalid;
}


