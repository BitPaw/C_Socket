#include "Client.h"
#include "Config.h"

void ClientInitialize(Client* client)
{
	client->State = Invalid;
	client->ID = -1;
	client->IP = 0;
	client->Port = -1;

	client->SocketID = -1;
}

void ClientConnect(Client* client, char* ip, unsigned short port)
{
	const int length = sizeof(struct sockaddr_in);
	int connectResult;

	client->SocketAddress.sin_addr.S_un.S_addr = inet_addr(ip);
	client->SocketAddress.sin_family = AF_INET;
	client->SocketAddress.sin_port = htons(port);

	connectResult = connect(client->SocketID, &client->SocketAddress, length);

	//Connect to remote server
	if (connectResult == -1)
	{
		client->State = ConnectionFailure;
		return;
	}

	client->State = Connected;
}

void ClientSendCommand(Client* client)
{

}

void ClientDisconnect(Client* client)
{
	client->State = Disconnected;
}