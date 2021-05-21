#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#if OSUnix
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif defined(OSWindows)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#endif

#include "SocketErrorCode.h"
#define SocketBufferSize 1024u

#ifndef IOSocketInclude
#define IOSocketInclude

typedef struct IOSocket_
{
	unsigned int ID;
	unsigned short Port;
	char Message[SocketBufferSize];

	struct sockaddr_in Adress;

#ifdef OSWindows
	WSADATA WindowsSocketAgentData;
#endif
}IOSocket;


void SocketInitialize(IOSocket* socket);
SocketErrorCode SocketOpen(IOSocket* socket, unsigned short port);
void SocketClose(IOSocket* socket);
void SocketAwaitConnection(IOSocket* serverSocket, IOSocket* clientSocket);
SocketErrorCode SocketConnect(IOSocket* clientSocket, IOSocket* serverSocket, char* ipAdress, unsigned short port);
SocketErrorCode SocketRead(IOSocket* socket);
SocketErrorCode SocketWrite(IOSocket* socket, char* message);
char IsValidIPv4(char* ipAdress);

#ifdef OSWindows
SocketErrorCode WindowsSocketAgentStartup(IOSocket* socket);
#endif

#endif