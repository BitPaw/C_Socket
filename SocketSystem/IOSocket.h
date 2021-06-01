#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#ifdef OSUnix
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif defined(OSWindows)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#endif

#include "SocketErrorCode.h"
#include "IPVersion.h"

#define SocketBufferSize 1024u

#ifndef IOSocketInclude
#define IOSocketInclude

typedef struct IOSocket_
{
	unsigned int ID;
	unsigned short Port;
	char Message[SocketBufferSize];

	IPVersion IPMode;

	//---[ Events ]------------------------------------------------------------
	void (*OnMessage)(int socketID, char* message);
	void (*OnConnected)(int socketID);
	void (*OnDisconnected)(int socketID, char disconnectionCause);
	//-------------------------------------------------------------------------

	struct sockaddr_in AdressIPv4; // Used only in IPv4


#ifdef OSWindows
	ADDRINFO* AdressIPv6;
	WSADATA WindowsSocketAgentData;
#endif
}IOSocket;


void SocketInitialize(IOSocket* socket);
SocketErrorCode SocketOpen(IOSocket* socket, IPVersion ipVersion, unsigned short port);
void SocketClose(IOSocket* socket);
void SocketAwaitConnection(IOSocket* serverSocket, IOSocket* clientSocket);
SocketErrorCode SocketConnect(IOSocket* clientSocket, IOSocket* serverSocket, char* ipAdress, unsigned short port);
SocketErrorCode SocketRead(IOSocket* socket);
SocketErrorCode SocketWrite(IOSocket* socket, char* message);

#ifdef OSUnix
void* SocketReadAsync(IOSocket* socket);
#endif

#ifdef OSWindows
unsigned long SocketReadAsync(IOSocket* socket);
#endif


// Private
static int SocketGetAdressFamily(IPVersion ipVersion);
static char SocketSetupAdress(IOSocket* connectionSocket, IPVersion ipVersion, char* ip, unsigned short port);

#ifdef OSWindows
SocketErrorCode WindowsSocketAgentStartup(IOSocket* socket);
#endif

#endif