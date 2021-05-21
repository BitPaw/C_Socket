#include "CommandToken.h"
#include <stdlib.h>

void CommandTokenInitialize(CommandToken* commandToken)
{
    commandToken->ClientSocketID = -1;
    commandToken->CommandType = CommandInvalid;
    commandToken->Key = 0;
    commandToken->Value = 0;
}

void CommandTokenParse(CommandToken* commandToken, char* dataString)
{
    int lengh = 0;

    for (; dataString[lengh] != '\0' ; lengh++)
    {
      
    }

    memset(commandToken->CommandRaw, 0, lengh+1);
    memcpy(commandToken->CommandRaw, dataString, lengh);     
}
