#include "ConnectionState.h"
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

//---[Public]------------------------------------------------------------------
void ServerInitialize(Server* server);
void ServerStart(Server* server, IPVersion ipVersion, unsigned short port);
void ServerStop(Server* server);
char ServerIsRunning(Server* server);
void ServerKickClient(Server* server, int socketID);
Client* ServerWaitForClient(Server* server);
Client* ServerGetClientViaID(Server* server, int socketID);
SocketErrorCode ServerSendToClient(Server* server, int clientID, char* message);
SocketErrorCode ServerBroadcastToClients(Server* server, char* message);
void ServerRegisterClient(Server* server, Client* client);
void ServerUnRegisterClient(Server* server, Client* client);
void ServerPrint(Server* server);
//---[Private]-----------------------------------------------------------------
static Client* GetNextClient(Server* server);
//-----------------------------------------------------------------------------

#endif
