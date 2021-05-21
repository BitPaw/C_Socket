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

#if defined(linux) || defined(__APPLE__)
void* ThreadClientHandleRead(Client* client);
#endif

#ifdef _WIN32
unsigned long ThreadClientHandleRead(Client* client);
#endif


#endif
