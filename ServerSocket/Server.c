#include "Server.h"
#include "Config.h"
#include <string.h>
#include <stdio.h>

void ServerInitialize(Server* server)
{
    server->State = Invalid;
    server->NumberOfConnectedClients = 0;
}

void ServerStart(Server* server, unsigned short port)
{
    SocketErrorCode errorCode = SocketOpen(&server->Socket, port);
    
    if (errorCode == NoError)
    {
        server->State = Online;
    }
}

void ServerStop(Server* server)
{
    char isRunning = server->State = Online;

    if (isRunning)
    {
        server->State = Offline;
        
        SocketClose(&server->Socket);
    }
}

void ServerWaitForClient(Server* server)
{
    Client client;
    
    ClientInitialize(&client);

    SocketAwaitConnection(&server->Socket, &client.Socket);
      
    if(client.Socket.ID == -1)
    {
        return;
    }

    ServerRegisterClient(&server, &client);

    printf("Client detected: %i\n", client.Socket.ID);

    SocketRead(&client.Socket);

    SocketWrite(&client.Socket, "HTTP/1.0 200 OK\r\n\r\n\n<HTML>[B]eans</HTML>");

    SocketClose(&client.Socket);
}

void ServerPrint(Server* server)
{
    printf
    (
        "+--------------------+\n"
        "| Socket (Server)    |\n"
        "+--------------------+\n"
        "| ID      : %8u |\n" 
        "| Port    : %8u |\n"
        "| State   : %8s |\n"
        "| Clients : %8u |\n"
        "+--------------------+\n",
        server->Socket.ID,
        server->Socket.Port,
        ConnectionStateToString(server->State),
        server->NumberOfConnectedClients
    );
}

void ServerRegisterClient(Server* server, Client* client)
{
    server->NumberOfConnectedClients++;

   // server->ClientList = realloc(server->ClientList, ++server->NumberOfConnectedClients);

    //server->ClientList[server->NumberOfConnectedClients - 1] = *client;
}
