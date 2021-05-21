#include "ConnectionState.h"
#include "IOSocket.h"
#include "Thread.h"

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


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

#ifdef OSUnix
void* ThreadClientHandleRead(Client* client);
#endif

#ifdef OSWindows
unsigned long ThreadClientHandleRead(Client* client);
#endif


#endif
