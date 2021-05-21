#include "ConnectionState.h"
#include "Client.h"
#include "IOSocket.h"
#include "CommandToken.h"

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

#if defined(linux) || defined(__APPLE__)
void* ThreadServerHandleClientIO(Client* client);
#endif

#ifdef _WIN32
unsigned long ThreadServerHandleClientIO(Client* client);
#endif

Client* GetNextClient(Server* server);

#endif
