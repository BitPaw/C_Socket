#include "Client.h"
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
	//ServerInitialize(&client->ConnectedServer);

	SocketErrorCode errorCode = SocketConnect(&client->Socket, &client->ConnectedServerData, ip, port);

	if (errorCode != NoError)
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
