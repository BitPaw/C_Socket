#include "Server.h"
#include "Config.h"
#include <errno.h>

void ServerInitialize(Server* server)
{
    server->State = Invalid;
}

void ServerStart(Server* server, unsigned short port)
{
    // Create a socket (IPv4) as a stream.
    // Returns -1 on failure. ID if succesful.     
    int sock;
    size_t size;

    unsigned int socketCreationResult = socket(AF_INET, SOCK_STREAM, 0);
    //                                   /\--- this fails... why?? Might be some OS problem "No sockets left"

    // Set up data? IP & Port
    server->Internal.sin_family = AF_INET;
    server->Internal.sin_port = htons(port);
    server->Internal.sin_addr.s_addr = INADDR_ANY;

    // Connect socket to server??
    int connectionStatus = connect(socketCreationResult, (struct sockadrr*) &server->Internal, sizeof(server->Internal));
        
    if (socketCreationResult == -1)
    {
        server->State = SocketFailure;
        return;
    }

    server->State = Listening;
}

void ServerStop(Server* server)
{
    server->State = Stopped;
}