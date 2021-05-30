#include "ConnectionState.h"
#include "IOSocket.h"
#include "Thread.h"

#ifndef ClientIncluded
#define ClientIncluded

typedef struct Client_
{
    ConnectionState State;
    char* IP;
    IOSocket Socket;

    int ConnectedServerID;
    IOSocket ConnectedServerData;

    Thread CommunicationThread;
}Client;

void ClientInitialize(Client* client);
void ClientConnect(Client* client, char* ip, unsigned short port);
void ClientSendCommand(Client* client);
void ClientDisconnect(Client* client);

#endif
