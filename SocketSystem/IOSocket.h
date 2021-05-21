#pragma once

#if defined(linux) || defined(__APPLE__)
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#ifdef _WIN32
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

#ifdef _WIN32
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

#ifdef _WIN32
SocketErrorCode WindowsSocketAgentStartup(IOSocket* socket);
#endif

#endif