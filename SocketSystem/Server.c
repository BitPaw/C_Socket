#include <string.h>
#include <stdio.h>
#include "Server.h"
#include "Thread.h"
#include <stdlib.h>

void OnMessageRecieved(Server* server, CommandToken* commandToken)
{
   printf("[Client][%i] %s\n", commandToken->ClientSocketID, commandToken->CommandRaw);
}

void ServerInitialize(Server* server)
{
    server->State = ConnectionInvalid;
    server->ClientList = 0;
    server->NumberOfConnectedClients = 0;
    server->NumberOfMaximalClients = 10;
    server->ClientList = malloc(server->NumberOfMaximalClients * sizeof(Client));

    for (size_t i = 0; i < server->NumberOfMaximalClients; i++)
    {
        Client* client = &server->ClientList[i];

        ClientInitialize(client);
    }

    SocketInitialize(&server->Socket);
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

void ServerStart(Server* server, unsigned short port)
{
    SocketErrorCode errorCode = SocketOpen(&server->Socket, port);
    
    if (errorCode == NoError)
    {
        server->State = ConnectionOnline;
    }
}

void ServerStop(Server* server)
{
    char isRunning = server->State = ConnectionOnline;

    if (isRunning)
    {
        server->State = ConnectionOffline;
        
        SocketClose(&server->Socket);
    }
}



#if defined(linux) || defined(__APPLE__)
void* ThreadServerHandleClientIO(Client* client)
#endif

#ifdef _WIN32
unsigned long ThreadServerHandleClientIO(Client* client)
#endif
{
    char bzffer[60];

    sprintf
    (
        bzffer,         
        "Connected to a "
#ifdef linux
        "Linux"
#endif

#ifdef __APPLE__
        "MAC_OS"
#endif

#ifdef _WIN32
        "Windows"
#endif    
        " as (%i)",
        client->Socket.ID
    );

    SocketWrite(&client->Socket, bzffer);

    char* message;
	
    do
    {
        SocketRead(&client->Socket);
        message = &client->Socket.Message[0];

        CommandToken commandToken;
        CommandTokenParse(&commandToken, message);
        commandToken.ClientSocketID = client->Socket.ID;

        //TODO: ENTF: Debug show raw Message
        printf("[Client][%i] %s\n", client->Socket.ID, commandToken.CommandRaw);

        //TODO: To main Thread [commandToken]

    } while (memcmp("QUIT", message, 4) != 0);
	
    SocketWrite(&client->Socket, "ACK_QUIT");

	
    SocketClose(&client->Socket);
    client->State = ConnectionOffline;
    printf("[System] Client disconnected %i\n", client->Socket.ID);
	
    //ServerUnRegisterClient(this, &client);
	
    return 0;
}

void ServerWaitForClient(Server* server)
{
    Client* client = GetNextClient(server);
    
    ClientInitialize(client);

    SocketAwaitConnection(&server->Socket, &client->Socket);
      
    if(-1 == client->Socket.ID)
    {
        client->State = ConnectionInvalid;
        return;
    }

    client->State = ConnectionOnline;

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

    printf("[Server] Client (%i) unregistered.\n", client->Socket.ID);

}

void ServerRegisterClient(Server* server, Client* client)
{
    server->NumberOfConnectedClients++;

   // server->ClientList = realloc(server->ClientList, ++server->NumberOfConnectedClients);

    //server->ClientList[server->NumberOfConnectedClients - 1] = *client;  

    printf("[Server] New client (%i) registered.\n",client->Socket.ID);


}