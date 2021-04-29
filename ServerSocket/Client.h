#include "Config.h"
#include "ConnectionState.h"
#include "IOSocket.h"

#ifndef ClientIncluded
#define ClientIncluded

typedef struct Client_
{
    ConnectionState State;
    int ID;
    char* IP;
    IOSocket Socket;
}Client;

void ClientInitialize(Client* client);
void ClientConnect(Client* client, char* ip, unsigned short port);
void ClientSendCommand(Client* client);
void ClientDisconnect(Client* client);

#endif
