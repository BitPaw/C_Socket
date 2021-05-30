#include "Command.h"

#ifndef CommandTokenInclude
#define CommandTokenInclude

typedef struct CommandToken_
{
    unsigned int ClientSocketID;
    char* CommandRaw;
    Command CommandType;
    char* Key;
    char* Value;
} CommandToken;

void CommandTokenInitialize(CommandToken* commandToken);
void CommandTokenClear(CommandToken* commandToken);

unsigned char  CommandTokenParse(CommandToken* commandToken, char* dataString);
Command ParseCommand(char* command);
int CommandTokenCompare(CommandToken* commandToken1, CommandToken* commandToken2);

#endif
