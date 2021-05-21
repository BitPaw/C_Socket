#include "ConnectionState.h"
#include "Client.h"
#include "IOSocket.h"
#include "CommandToken.h"

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#ifndef ServerIncluded
#define ServerIncluded

typedef struct Server_
{ 
    ConnectionState State; 
    IOSocket Socket;

    Client* ClientList;
    unsigned int NumberOfConnectedClients;
    unsigned int NumberOfMaximalClients;
}Server;

void OnCommandRecieved(Server* server, CommandToken* commandToken);

void ServerInitialize(Server* server);
void ServerStart(Server* server, unsigned short port);
void ServerStop(Server* server);
void ServerWaitForClient(Server* server);
void ServerPrint(Server* server);
void ServerRegisterClient(Server* server, Client* client);
void ServerUnRegisterClient(Server* server, Client* client);

#if OSUnix
void* ThreadServerHandleClientIO(Client* client);
#elif defined(OSWindows)
unsigned long ThreadServerHandleClientIO(Client* client);
#endif

Client* GetNextClient(Server* server);

#endif
