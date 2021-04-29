#include "ConnectionState.h"
#include "Config.h"
#include "Client.h"

#ifndef ServerIncluded
#define ServerIncluded

typedef struct Server_
{
    unsigned int SocketID;
    ConnectionState State;
    struct sockaddr_in Internal;    

    Client* ClientList;
    unsigned int NumberOfConnectedClients;

}Server;

void ServerInitialize(Server* server);
void ServerStart(Server* server, unsigned short port);
void ServerStop(Server* server);
void ServerWaitForClient(Server* server);
void ServerPrint(Server* server);

#endif
