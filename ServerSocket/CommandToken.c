#include "CommandToken.h"

void CommandTokenInitialize(CommandToken* commandToken)
{
    commandToken->CommandType = Invalid;
    commandToken->Key = 0;
    commandToken->Value = 0;
}

void CommandTokenParse(CommandToken* commandToken, char* dataString)
{

}