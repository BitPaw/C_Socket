#include "FileError.h"

#include "../SocketSystem/Server.h"

#ifndef CommandManagerInclude 
#define CommandManagerInclude

FileError FileDataPut(char* filePath, char* dataToWrite);
FileError FileDataGet(char* filePath, char* targetToWriteTo);
FileError FileDelete(char* filePath);
FileError FileLock(char* filePath);
FileError FileUnlock(char* filePath);
FileError FileChangePublish(char* filePath);
FileError FileChangeSubscribe(char* filePath);
FileError ProgramOpen(char* programName);
void ApplicationQuit();
void SendHTTPResponse(Server* server, int socketID);

#endif