#include "Config.h"
#include "ConnectionState.h"

#ifndef ClientIncluded
#define ClientIncluded

typedef struct Client_
{
    ConnectionState State;
    unsigned int ID;
    char* IP;
    unsigned int Port;

    // Internal
    unsigned int SocketID;
    struct sockaddr_in SocketAddress;
}Client;

extern void ClientInitialize(Client* client);
extern void ClientConnect(Client* client, char* ip, unsigned short port);
extern void ClientSendCommand(Client* client);
extern void ClientDisconnect(Client* client);

#endif