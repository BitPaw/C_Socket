#include "Server.h"
#include "Thread.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void ServerInitialize(Server* server)
{
    SocketInitialize(&server->Socket);

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
        char isUsed = SocketIsCurrentlyUsed(&client->Socket);

        if (!isUsed)
        {
            return client;
        }
    }

    return 0;
}

char ServerStart(Server* server, IPVersion ipVersion, unsigned short port)
{
    SocketError errorCode = SocketOpen(&server->Socket, ipVersion, port);
    
    return errorCode == SocketNoError;
}

void ServerStop(Server* server)
{
    char isRunning = SocketIsCurrentlyUsed(&server->Socket);

    if (isRunning)
    {        
        SocketClose(&server->Socket);
    }
}

void ServerKickClient(Server* server, int socketID)
{
    Client* client = ServerGetClientViaID(server, socketID);

    ClientDisconnect(client);
}

Client* ServerWaitForClient(Server* server)
{
    char hasCallBack = server->Socket.OnConnected != 0;
    Client* client = GetNextClient(server);
    
    ClientInitialize(client);

    SocketAwaitConnection(&server->Socket, &client->Socket);
      
    if(client->Socket.ID == -1)
    {
        return 0;
    }

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
        SocketIsCurrentlyUsed(&server->Socket) ? "ONLINE" : "OFFLINE",
        server->NumberOfConnectedClients
    );
}

SocketError ServerSendToClient(Server* server, int clientID, char* message)
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

SocketError ServerBroadcastToClients(Server* server, char* message)
{
    SocketError errorCode = SocketNoError;

    for (size_t i = 0; i < server->NumberOfMaximalClients; i++)
    {
        Client* client = &server->ClientList[i];

        if (client->Socket.ID != -1)
        {
            SocketError currentCrrorCode = SocketWrite(&client->Socket, message);

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