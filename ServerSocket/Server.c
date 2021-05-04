#include <string.h>
#include <stdio.h>
#include "Server.h"
#include "Thread.h"

void ServerInitialize(Server* server)
{
    server->State = Invalid;
    server->ClientList = 0;
    server->NumberOfConnectedClients = 0;
    server->NumberOfMaximalClients = 10;
    server->ClientList = calloc(server->NumberOfMaximalClients, sizeof(Client));

    for (size_t i = 0; i < server->NumberOfMaximalClients; i++)
    {
        ClientInitialize(&server->ClientList[i]);
    }

    SocketInitialize(&server->Socket);
}

Client* GetNextClient(Server* server)
{
    for (unsigned int i = 0; i < server->NumberOfMaximalClients; i++)
    {
        Client* client = &server->ClientList[i];

        if (client->State == Invalid || client->State == Offline)
        {
            return client;
        }
    }

    return 0;
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

unsigned long ThreadServerHandleClientIO(Client* client)
{
    SocketRead(&client->Socket);

    SocketWrite
    (
        &client->Socket,
        "HTTP/1.0 200 OK\r\n\r\n\n"
        "<HTML>"
        "<h1> Hello from the Socket</h1>"
#ifdef linux
        "<h2>Linux</h2>"
#endif    

#ifdef _WIN32
        "<h2>Windows</h2>"
#endif     
        "</HTML>"
    );

    

    SocketClose(&client->Socket);

    client->State = Offline;    

    //ServerUnRegisterClient(server, &client);
}

void ServerWaitForClient(Server* server)
{
    Client* client = GetNextClient(server);
    
    ClientInitialize(client);

    SocketAwaitConnection(&server->Socket, &client->Socket);
      
    if(client->Socket.ID == -1)
    {
        client->State = Invalid;
        return;
    }

    client->State = Online;

    ServerRegisterClient(server, client);
    
    ThreadCreate(&client->CommunicationThread, ThreadServerHandleClientIO, client);
}

void ServerPrint(Server* server)
{
    printf
    (
        "+--------------------+\n"
        "| Socket (Server)    |\n"
        "+--------------------+\n"
        "| ID      : %8i |\n" 
        "| Port    : %8i |\n"
        "| State   : %8s |\n"
        "| Clients : %8i |\n"
        "+--------------------+\n",
        server->Socket.ID,
        server->Socket.Port,
        ConnectionStateToString(server->State),
        server->NumberOfConnectedClients
    );
}

void ServerUnRegisterClient(Server* server, Client* client)
{
    server->NumberOfConnectedClients--;

    printf("[Server] Client(%i) unregistered: %i\n", client->ID, client->Socket.ID);

    client->ID = -1;
}

void ServerRegisterClient(Server* server, Client* client)
{
    client->ID = server->NumberOfConnectedClients++;

   // server->ClientList = realloc(server->ClientList, ++server->NumberOfConnectedClients);

    //server->ClientList[server->NumberOfConnectedClients - 1] = *client;  

    printf("[Server] New client(%i) registered: %i\n", client->ID, client->Socket.ID);


}