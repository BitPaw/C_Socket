#include "Server.h"

#ifdef linux
#include <sys/types.h> // <-- Can't find them?!
#include <sys/socket.h>
#endif

#ifdef _WIN32
#include <winsock.h>
#endif

void ServerInit(Server* server)
{
    // Erzeuge das Socket - Verbindung über TCP/IP
    int socketCreationResult = socket( AF_INET, SOCK_STREAM, 0 );

    if (socketCreationResult < 0) 
    {
        // Fehler beim Erzeugen des Sockets
    }
}

void ServerOpen(Server* server, int port)
{

}

void ServerClose(Server* server)
{

}