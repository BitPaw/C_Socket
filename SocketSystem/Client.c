#include "Client.h"
#include "Server.h"

#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


void ClientInitialize(Client* client)
{
	client->IP = 0;
	client->ConnectedServerID = -1;

	SocketInitialize(&client->Socket);
	SocketInitialize(&client->ConnectedServerData);
}

char ClientConnect(Client* client, char* ip, unsigned short port)
{
	SocketError errorCode = SocketConnect(&client->Socket, &client->ConnectedServerData, ip, port);

	return errorCode == SocketNoError;
}

void ClientSendCommand(Client* client)
{

}

void ClientDisconnect(Client* client)
{
	SocketClose(&client->Socket);

	ClientInitialize(client);		
}