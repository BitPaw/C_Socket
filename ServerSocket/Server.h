#include "ConnectionState.h"
#include "Config.h"
#include "Client.h"
#include "IOSocket.h"

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

void ServerInitialize(Server* server);
void ServerStart(Server* server, unsigned short port);
void ServerStop(Server* server);
void ServerWaitForClient(Server* server);
void ServerPrint(Server* server);
void ServerRegisterClient(Server* server, Client* client);
void ServerUnRegisterClient(Server* server, Client* client);
unsigned long ThreadServerHandleClientIO(Server* client);
Client* GetNextClient(Server* server);

#endif
