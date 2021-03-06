#ifndef IOSocketInclude
#define IOSocketInclude

#include "OSDefine.h"
#include "SocketError.h"
#include "IPVersion.h"

#ifdef OSUnix
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#elif defined(OSWindows)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <WS2tcpip.h>
#endif

#define SocketBufferSize 2048u

typedef struct IOSocket_
{
	unsigned int ID;
	unsigned short Port;
	char Message[SocketBufferSize];

	IPVersion IPMode;

	//---[ Events ]------------------------------------------------------------
	void (*OnMessage)(int socketID, char* message);
	void (*OnConnected)(int socketID);
	void (*OnDisconnected)(int socketID);
	//-------------------------------------------------------------------------

	struct sockaddr_in AdressIPv4; // Used only in IPv4

#ifdef OSUnix
    struct addrinfo AdressIPv6;
#elif defined(OSWindows)
    ADDRINFO* AdressIPv6;
#endif

}IOSocket;

char SocketIsCurrentlyUsed(IOSocket* socket);
void SocketInitialize(IOSocket* socket);
SocketError SocketOpen(IOSocket* socket, IPVersion ipVersion, unsigned short port);
void SocketClose(IOSocket* socket);
void SocketAwaitConnection(IOSocket* serverSocket, IOSocket* clientSocket);
SocketError SocketConnect(IOSocket* clientSocket, IOSocket* serverSocket, char* ipAdress, unsigned short port);
SocketError SocketRead(IOSocket* socket);
SocketError SocketWrite(IOSocket* socket, char* message);

// Private
static int SocketGetAdressFamily(IPVersion ipVersion);
static char SocketSetupAdress(IOSocket* connectionSocket, IPVersion ipVersion, char* ip, unsigned short port);

#ifdef OSUnix
void* SocketReadAsync(IOSocket* socket);
#elif defined(OSWindows)
unsigned long SocketReadAsync(IOSocket* socket);
SocketError WindowsSocketAgentStartup();
int WindowsSocketAgentShutdown();
#endif

#endif