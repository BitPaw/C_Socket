#include "Client.h"

#include <stdio.h>

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

unsigned long ThreadClientHandleRead(void* clientRaw)
{
    Client* client = (Client*)clientRaw;

    unsigned char readErrorCounter = 0;
    const unsigned char readErrorCounterThreshold = 5;

    while (1)
    {
        const SocketErrorCode errorCode = SocketRead(&client->Socket);

        if (errorCode == NoError)
        {
            readErrorCounter = 0;

            char* message = &client->Socket.Message[0];

            if (memcmp("ACK_QUIT", message, 8) == 0)
            {
                printf("[Server] Accepted quit request\n");
                break;
            }

            printf("[Server] %s\n", &client->Socket.Message[0]);
        }
        else
        {
            printf("[Error] Failed to read message\n");

            if (readErrorCounter++ > readErrorCounterThreshold)
            {
                printf("[Error] Too many read errors in a row. Terminating connection.\n");
                break;
            }
        }
    }

    printf("[System] Closing connection.\n");
    SocketClose(&client->Socket);
    client->State = Offline;
    return 0;
}