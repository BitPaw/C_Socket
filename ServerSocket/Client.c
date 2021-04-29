#include "Client.h"
#include "Config.h"
#include "Server.h"

void ClientInitialize(Client* client)
{
	client->State = Invalid;
	client->ID = -1;
	client->IP = 0;

	SocketInitialize(&client->Socket);
}

void ClientConnect(Client* client, char* ip, unsigned short port)
{
	Server server;

	ServerInitialize(&server);

	SocketConnect(&client->Socket, &server.Socket, ip, port);

	if (client->Socket.ID == -1)
	{
		client->State = Offline;
		return;
	}

	client->State = Online;
}

void ClientSendCommand(Client* client)
{

}

void ClientDisconnect(Client* client)
{
		client->State = Offline;
}
