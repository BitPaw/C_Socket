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
	int length = sizeof(client->SocketAddress);
	const struct sockaddr* socketAdressPointer = &(client->SocketAddress);
	
	client->SocketAddress.sin_family = AF_INET;
	client->SocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	client->SocketAddress.sin_port = htons(port);

	client->ID = connect(client->SocketID, socketAdressPointer, length);

	//Connect to remote server
	if (client->ID == -1)
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
