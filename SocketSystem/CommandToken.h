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

extern void CommandTokenInitialize(CommandToken* commandToken);
extern void CommandTokenParse(CommandToken* commandToken, char* dataString);

#endif
