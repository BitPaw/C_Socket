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
	client->State = ConnectionInvalid;
	client->IP = 0;

	client->ConnectedServerID = -1;

	SocketInitialize(&client->Socket);
	SocketInitialize(&client->ConnectedServerData);
}

void ClientConnect(Client* client, char* ip, unsigned short port)
{
	//ServerInitialize(&client->ConnectedServer);

	SocketErrorCode errorCode = SocketConnect(&client->Socket, &client->ConnectedServerData, ip, port);

	if (errorCode != NoError)
	{
		client->State = ConnectionOffline;
		return;
	}

	client->State = ConnectionOnline;
}

void ClientSendCommand(Client* client)
{

}

void ClientDisconnect(Client* client)
{
		client->State = ConnectionOffline;
}




#ifdef OSUnix
void* ThreadClientHandleRead(Client* client)
#endif

#ifdef OSWindows
unsigned long ThreadClientHandleRead(Client* client)
#endif

{
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
    client->State = ConnectionOffline;
    return 0;
}