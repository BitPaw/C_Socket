#ifndef UserSystemInclude
#define UserSystemInclude

#include "CommandError.h"

#define FileExtensionData "txt"
#define FileExtensionLocked "lck"
#define FileExtensionSubscribed "sub"

char UserCanModifyFile(int clientID, char* fileName);
CommandError UserSubscribeToFile(int clientID, char* fileName);
CommandError UserUnSubscribeToFile(int clientID, char* fileName);
CommandError UserOpenProgram(char* programName, char * value);
void UserUnlockAllFiles(int clientID);
void UserGetAllSubscribers(int actorClientID, char* fileName, int** targetArray, int* amountOfElements);

CommandError UserUnlockFile(int clientID, char* fileName);
CommandError UserLockFile(int clientID, char* fileName);
CommandError UserReadFromFile(int clientID, char* fileName, char** content);
CommandError UserWriteInFile(int clientID, char* fileName, char* content);
CommandError UserDeleteFile(int clientID, char* fileName);

void ChangeFileExtension(char* fileName, char* fileExtension);

#endif