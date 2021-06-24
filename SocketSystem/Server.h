#ifndef ServerIncluded
#define ServerIncluded

#include "Client.h"
#include "IOSocket.h"

typedef struct Server_
{ 
    IOSocket Socket;

    Client* ClientList;
    unsigned int NumberOfConnectedClients;
    unsigned int NumberOfMaximalClients;
}Server;

//---[Public]------------------------------------------------------------------
void ServerInitialize(Server* server);
char ServerStart(Server* server, IPVersion ipVersion, unsigned short port);
void ServerStop(Server* server);
void ServerKickClient(Server* server, int socketID);
Client* ServerWaitForClient(Server* server);
Client* ServerGetClientViaID(Server* server, int socketID);
SocketError ServerSendToClient(Server* server, int clientID, char* message);
SocketError ServerBroadcastToClients(Server* server, char* message);
void ServerRegisterClient(Server* server, Client* client);
void ServerUnRegisterClient(Server* server, Client* client);

//---[Private]-----------------------------------------------------------------
static Client* GetNextClient(Server* server);
//-----------------------------------------------------------------------------

#endif
