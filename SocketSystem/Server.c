#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Server.h"
#include "Thread.h"

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

void ServerInitialize(Server* server)
{
    SocketInitialize(&server->Socket);

    server->State = ConnectionInvalid;
    server->ClientList = 0;
    server->NumberOfConnectedClients = 0;
    server->NumberOfMaximalClients = 10;

    //---[Hardcoded]-----------------------------------------------------------
    server->ClientList = malloc(server->NumberOfMaximalClients * sizeof(Client));

    for (size_t i = 0; i < server->NumberOfMaximalClients; i++)
    {
        Client* client = &server->ClientList[i];

        ClientInitialize(client);
    }
    //-------------------------------------------------------------------------
}

Client* GetNextClient(Server* server)
{
    for (unsigned int i = 0; i < server->NumberOfMaximalClients; i++)
    {
        Client* client = &server->ClientList[i];

        if (client->State == ConnectionInvalid || client->State == ConnectionOffline)
        {
            return client;
        }
    }

    return 0;
}

void ServerStart(Server* server, IPVersion ipVersion, unsigned short port)
{
    SocketErrorCode errorCode = SocketOpen(&server->Socket, ipVersion, port);
    
    switch (errorCode)
    {
        case SocketNoError:
        {
            server->State = ConnectionOnline;
            break;
        }
        default:
        {
            server->State = ConnectionOffline;
            break;
        }
    }
}

void ServerStop(Server* server)
{
    char isRunning = server->State == ConnectionOnline;

    if (isRunning)
    {
        server->State = ConnectionOffline;
        
        SocketClose(&server->Socket);
    }
}

Client* ServerWaitForClient(Server* server)
{
    char hasCallBack = server->Socket.OnConnected != 0;
    Client* client = GetNextClient(server);
    
    ClientInitialize(client);

    SocketAwaitConnection(&server->Socket, &client->Socket);
      
    if(client->Socket.ID == -1)
    {
        client->State = ConnectionInvalid;

        return 0;
    }

    client->State = ConnectionOnline;

    if (hasCallBack)
    {
        server->Socket.OnConnected(server->Socket.ID);
    }

    ServerRegisterClient(server, client);
    
    ThreadCreate(&client->CommunicationThread, SocketReadAsync, &client->Socket);

    return client;
}

Client* ServerGetClientViaID(Server* server, int socketID)
{
    for (unsigned int i = 0; i < server->NumberOfMaximalClients; i++)
    {
        Client* client = &server->ClientList[i];
        int clientSocketID = client->Socket.ID;
        char foundTarget = clientSocketID == socketID;

        if (foundTarget)
        {
            return client;
        }
    }

    return 0;
}

void ServerPrint(Server* server)
{
    printf
    (
        "+--------------------+\n"
        "| Socket (Server)    |\n"
        "+--------------------+\n"
        "| ID      : %8i |\n" 
        "| Mode    : %8s |\n"
        "| Port    : %8i |\n"
        "| State   : %8s |\n"
        "| Clients : %8i |\n"
        "+--------------------+\n",
        server->Socket.ID,
        server->Socket.IPMode == IPVersion4 ? "IPv4" : "IPv6",
        server->Socket.Port,
        ConnectionStateToString(server->State),
        server->NumberOfConnectedClients
    );
}

SocketErrorCode ServerSendToClient(Server* server, int clientID, char* message)
{
    // Client LookUp
    Client* client = ServerGetClientViaID(server, clientID);

    if (client == 0)
    {
        // Error: No client with this ID.
        return SocketSendFailure;
    }

    // Sent to Client;
    return SocketWrite(&client->Socket, message);
}

SocketErrorCode ServerBroadcastToClients(Server* server, char* message)
{
    SocketErrorCode errorCode = SocketNoError;

    for (size_t i = 0; i < server->NumberOfMaximalClients; i++)
    {
        Client* client = &server->ClientList[i];

        if (client->Socket.ID != -1)
        {
            SocketErrorCode currentCrrorCode = SocketWrite(&client->Socket, message);

            if (currentCrrorCode != SocketNoError)
            {
                errorCode = currentCrrorCode;
            }
        }     
    }

    return errorCode;
}

void ServerRegisterClient(Server* server, Client* client)
{
    server->NumberOfConnectedClients++;

   // server->ClientList = realloc(server->ClientList, ++server->NumberOfConnectedClients);

    //server->ClientList[server->NumberOfConnectedClients - 1] = *client;  
}

void ServerUnRegisterClient(Server* server, Client* client)
{
    server->NumberOfConnectedClients--;
}