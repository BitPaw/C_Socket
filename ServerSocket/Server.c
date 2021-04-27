#include "Server.h"
#include "Config.h"
#include <errno.h>
#include <string.h>

void ServerInitialize(Server* server)
{
    server->SocketID = -1;
    server->State = Invalid;
    server->NumberOfConnectedClients = 0;
}

void ServerStart(Server* server, unsigned short port)
{
    const int adressFamily = AF_INET;
    const int streamType = SOCK_STREAM;
    const int protocol = 0;
    const int objectSize = sizeof(server->Internal);
	const struct sockaddr* socketAdressPointer = &(server->Internal);

    // Create a socket (IPv4) as a stream.
    // Returns -1 on failure. ID if succesful. 
    server->SocketID = socket(adressFamily, streamType, protocol);  
    //                                   /\--- this fails... why?? Might be some OS problem "No sockets left"


    if (server->SocketID == -1)
    {
        server->State = SocketCreationFailure;
        return;
    }   	
    
	server->Internal.sin_family = AF_INET;
	server->Internal.sin_addr.s_addr = htonl(INADDR_ANY);
	server->Internal.sin_port = htons(port);

    int opval = 1;
    int optionsocketResult = setsockopt(server->SocketID, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opval, sizeof(opval));

    if(optionsocketResult == 1)
    {
        server->State = SocketOptionFailure;
        return;
    }

    int bindingResult = bind(server->SocketID, socketAdressPointer, objectSize);

    if(bindingResult == -1)
    {
        server->State = BindingFailure;
        return;
    }

    int listeningResult = listen(server->SocketID, 10);

    if(listeningResult == -1)
    {
        server->State = ListeningFailure;
        return;
    }    

    server->State = Listening;
}

void ServerStop(Server* server)
{
    server->State = Stopped;
}

void ServerWaitForClient(Server* server)
{
    Client client;
    const unsigned int inputBufferSize = 1024u;
    char inputBuffer[inputBufferSize];

    ClientInitialize(&client);
    
    client.SocketID = accept(server->SocketID, 0, 0u);
      
    if(client.SocketID == -1)
    {
        return;
    }

    printf("Client detected: %i\n", client.SocketID);

    char readError = 0;

    // Read data stream. 
    while (1)
    {
      
        memset(inputBuffer, 0, inputBufferSize);
        unsigned int size = read(client.SocketID, &inputBuffer[0], inputBufferSize-1);
        char endOfFile = size == 0;
        readError = size == -1;

        printf("[IN] %i Bytes. %s\n",size, &inputBuffer[0]);

        if(readError)
        {
            break;
        }

        if((memcmp(&inputBuffer[size-1], "\n\0", 2) == 0) || endOfFile) 
        {
            break;
        }
    } 

    //-------------------------------------------------------------------------
    // Response
    //-------------------------------------------------------------------------
    char httpResponse[] = "HTTP/1.0 200 OK\r\n\r\n\n<HTML>[B]eans</HTML>";
    int size = 41;

    memset(inputBuffer, 0, inputBufferSize); 
    memcpy(inputBuffer, httpResponse, size);

    unsigned int writtenBytes = write(client.SocketID, inputBuffer, size);

    printf("wrode %u Bytes\n", writtenBytes);
    //-------------------------------------------------------------------------


    close(client.SocketID);   
}

void ServerPrint(Server* server)
{
    printf
    (
        "[Server]\n"
        "- Socket : %u\n"
        "- State  : %s\n"
        "- Clients: %u\n",
        server->SocketID,
        ConnectionStateToString(server->State),
        server->NumberOfConnectedClients
    );
}