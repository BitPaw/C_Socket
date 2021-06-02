#ifndef ClientIncluded
#define ClientIncluded

#include "IOSocket.h"
#include "Thread.h"

typedef struct Client_
{
    char* IP;
    IOSocket Socket;

    int ConnectedServerID;
    IOSocket ConnectedServerData;

    Thread CommunicationThread;
}Client;

void ClientInitialize(Client* client);
char ClientConnect(Client* client, char* ip, unsigned short port);
void ClientSendCommand(Client* client);
void ClientDisconnect(Client* client);

#endif