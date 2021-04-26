#include "ConnectionState.h"
#include "Config.h"

#ifndef ServerIncluded
#define ServerIncluded

typedef struct Server_
{
    unsigned int ID;
    ConnectionState State;
    struct sockaddr_in Internal;
}Server;

extern void ServerInitialize(Server* server);
extern void ServerStart(Server* server, unsigned short port);
extern void ServerStop(Server* server);

#endif