#include "IOSocket.h"
#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

void SocketInitialize(IOSocket* socket)
{
    socket->ID = -1;
    socket->Port = -1;
    socket->IPMode = IPVersionInvalid;
    socket->AdressIPv6 = 0;

    socket->OnMessage = 0;
    socket->OnConnected = 0;
    socket->OnDisconnected = 0;

    memset(socket->Message, 0, SocketBufferSize);
    memset(&socket->AdressIPv4, 0, sizeof(struct sockaddr_in));

#ifdef OSWindows    
    memset(&socket->WindowsSocketAgentData, 0, sizeof(WSADATA));
#endif
}

char SocketSetupAdress(IOSocket* connectionSocket, IPVersion ipVersion, char* ip, unsigned short port)
{  
    int adressFamily = SocketGetAdressFamily(ipVersion);

    switch (ipVersion)
    {
        case IPVersion4:
        {
            memset(&connectionSocket->AdressIPv4, 0, sizeof(connectionSocket->AdressIPv4));
            connectionSocket->AdressIPv4.sin_family = adressFamily;
            connectionSocket->AdressIPv4.sin_addr.s_addr = ip == 0 ? htonl(ip) : inet_addr(ip);
            connectionSocket->AdressIPv4.sin_port = htons(port);
            break;
        }

        case IPVersion6:
        {
            const int streamType = SOCK_STREAM;
            ADDRINFO adressIPv6Hint;

            memset(&adressIPv6Hint, 0, sizeof(adressIPv6Hint));
            adressIPv6Hint.ai_family = adressFamily;
            adressIPv6Hint.ai_socktype = streamType;
            adressIPv6Hint.ai_flags = AI_NUMERICHOST | AI_PASSIVE;

            char portString[10];
            sprintf(portString, "%i", port);

            int result = getaddrinfo(ip, portString, &adressIPv6Hint, &connectionSocket->AdressIPv6);

            if (result != 0)
            {
                return -1;
            }

            break;
        }
    }

    return 0;
}

SocketErrorCode SocketOpen(IOSocket* ioSocket, IPVersion ipVersion, unsigned short port)
{    
    int adressFamily = SocketGetAdressFamily(ipVersion);
    const int streamType = SOCK_STREAM;
    const int protocol = IPPROTO_TCP;

    SocketInitialize(ioSocket);

    ioSocket->IPMode = ipVersion;
    ioSocket->ID = -1;
    ioSocket->Port = port;

    // Create Socket
    {
#ifdef OSWindows
        SocketErrorCode errorCode = WindowsSocketAgentStartup(ioSocket);

        if (errorCode != SocketNoError)
        {
            return errorCode;
        }
#endif 

        // Create a socket (IPv4) as a stream.
        // Returns -1 on failure. ID if succesful. 
        ioSocket->ID = socket(adressFamily, streamType, protocol);

        if (ioSocket->ID == -1)
        {
            return SocketCreationFailure;
        }
    }

    // Set Socket Options
    {
#ifdef OSUnix
        char* options = SO_REUSEADDR | SO_REUSEPORT;
#elif defined(OSWindows)
        char* options = SO_REUSEADDR;
#endif  
        int opval = 1;
        int optionsocketResult = setsockopt(ioSocket->ID, SOL_SOCKET, options, &opval, sizeof(opval));

        if (optionsocketResult == 1)
        {
            return SocketOptionFailure;
        }
    }
       
    // Bind Socket
    {
        int result;
        int bindingResult = -1;

        SocketSetupAdress(ioSocket, ipVersion, 0, port);

        switch (ipVersion)
        {
            case IPVersion4:
            {
                bindingResult = bind(ioSocket->ID, &ioSocket->AdressIPv4, sizeof(ioSocket->AdressIPv4));
                break;
            }

            case IPVersion6:
            {
                bindingResult = bind(ioSocket->ID, ioSocket->AdressIPv6->ai_addr, ioSocket->AdressIPv6->ai_addrlen);
                break;
            }
        }

        if (bindingResult == -1)
        {
            return SocketBindingFailure;
        }
    }

    // Listen
    {
        int maximalClientsWaitingInQueue = 10;
        int listeningResult = listen(ioSocket->ID, maximalClientsWaitingInQueue);

        if (listeningResult == -1)
        {
            return SocketListeningFailure;
        }
    }

    return SocketNoError;
}

void SocketClose(IOSocket* socket)
{
#ifdef OSWindows
    shutdown(socket->ID, SD_SEND);
    closesocket(socket->ID);
    WSACleanup();
#elif defined(OSUnix)
    close(socket->ID);
#endif  

    SocketInitialize(socket);
}

void SocketAwaitConnection(IOSocket* serverSocket, IOSocket* clientSocket)
{
    switch (serverSocket->IPMode)
    {
        case IPVersion4:
        {
            const int adressDataLength = sizeof(clientSocket->AdressIPv4);
            clientSocket->ID = accept(serverSocket->ID, &clientSocket->AdressIPv4, &adressDataLength);
            break;
        }

        case IPVersion6:
        {
            clientSocket->AdressIPv6 = calloc(1, sizeof(ADDRINFO));
            clientSocket->ID = accept(serverSocket->ID, clientSocket->AdressIPv6->ai_addr, clientSocket->AdressIPv6->ai_addrlen);
            break;
        }
    } 
}

SocketErrorCode SocketConnect(IOSocket* clientSocket, IOSocket* serverSocket, char* ipAdress, unsigned short port)
{
    SocketInitialize(clientSocket);
    SocketInitialize(serverSocket);

    clientSocket->IPMode = AnalyseIPVersion(ipAdress);
   
    // Create Socket
    {
        const int adressFamily = SocketGetAdressFamily(clientSocket->IPMode);
        const int streamType = SOCK_STREAM;
        const int protocol = 0;

#ifdef OSWindows
        SocketErrorCode errorCode = WindowsSocketAgentStartup(&clientSocket);

        if (errorCode != SocketNoError)
        {
            return errorCode;
        }
#endif       

        clientSocket->ID = socket(adressFamily, streamType, protocol);

        if (clientSocket->ID == -1)
        {
            return SocketCreationFailure;
        }
    }

    // Connect
    {
        SocketSetupAdress(clientSocket, clientSocket->IPMode, ipAdress, port);

        switch (clientSocket->IPMode)
        {
            case IPVersion4:
            {
                serverSocket->ID = connect(clientSocket->ID, &clientSocket->AdressIPv4, sizeof(clientSocket->AdressIPv4));
                break;
            }

            case IPVersion6:
            {
                serverSocket->ID = connect(clientSocket->ID, clientSocket->AdressIPv6->ai_addr, clientSocket->AdressIPv6->ai_addrlen);
                break;
            }
        }


        if (serverSocket->ID == -1)
        {
            return SocketConnectionFailure;
        }
    }

    return SocketNoError;
}

SocketErrorCode SocketRead(IOSocket* socket)
{
    unsigned int byteRead = 0;
    char endOfFile = 0;

    memset(socket->Message, 0, SocketBufferSize);

#ifdef OSUnix
    byteRead = read(socket->ID, &socket->Message[0], SocketBufferSize - 1);
#elif defined(OSWindows)
    byteRead = recv(socket->ID, &socket->Message[0], SocketBufferSize - 1, 0);
#endif

    endOfFile = byteRead == 0;

    if (byteRead == -1)
    {
        return SocketRecieveFailure;
    }

    if (endOfFile)
    {
        return SocketRecieveConnectionClosed;
    }

    return SocketNoError;
}

SocketErrorCode SocketWrite(IOSocket* socket, char* message)
{
    int messageLengh = 0;
    unsigned int writtenBytes = 0;

    while (message[messageLengh++] != '\0') { }

   // memcpy(&message[messageLengh - 1], "\r\n\0", 3 * sizeof(char)); // Add line ending.

    //essageLengh += 2; // add cause of new length.

    if (messageLengh == 0)
    {
        return SocketNoError; // Just send nothing if the message is empty
    }

#ifdef OSUnix
    writtenBytes = write(socket->ID, message, messageLengh);
#elif defined(OSWindows)
    writtenBytes = send(socket->ID, message, messageLengh, 0);
#endif  

    if (writtenBytes == -1)
    {        
        return SocketSendFailure;
    }

    return SocketNoError;
}

#ifdef OSUnix
void* SocketReadAsync(IOSocket* socket)
#endif

#ifdef OSWindows
unsigned long SocketReadAsync(IOSocket* socket)
#endif
{
    char lostConnection = 0;

    // Send & Recieve <Permanent Loop>!
    {
        char* message;
        char quitConnection = 0;
        char readingFailureCounter = 0;
        char readingFailureMaximal = 3;

        do
        {
            SocketErrorCode errorCode = SocketRead(socket);
            message = &socket->Message[0];

            switch (errorCode)
            {
                case SocketNoError:
                {
                    char hasCallBack = socket->OnMessage != 0;

                    readingFailureCounter = 0;

                    if (hasCallBack)
                    {
                        socket->OnMessage(socket->ID, message);
                    }

                    break;
                }
                case SocketRecieveFailure:
                {           
                    if (++readingFailureCounter >= readingFailureMaximal)
                    {
                        lostConnection = 1;
                    }
                    break;
                }

                case SocketRecieveConnectionClosed:
                {
                    lostConnection = 1;
                    break;
                }
            }

            quitConnection = memcmp("QUIT", message, 4) == 0 || lostConnection;

        }
        while (!quitConnection);
    }

    // Handle disconnect
    {
        char hasDisconnectCallBack = socket->OnDisconnected != 0;

        if (!lostConnection)
        {
            SocketWrite(socket, "ACK_QUIT");

            SocketClose(socket);
      
            if (hasDisconnectCallBack)
            {
                socket->OnDisconnected(socket->ID, 0);
            }
        }
        else
        {
            if (hasDisconnectCallBack)
            {
                socket->OnDisconnected(socket->ID, 1);
            }
        }
    }

    return 0;
}

int SocketGetAdressFamily(IPVersion ipVersion)
{
    
    switch (ipVersion)
    {
        case IPVersion4:
            return AF_INET;

        case IPVersion6:
            return AF_INET6;

        default:
            return -1;
    }

    return PF_UNSPEC;
}

#ifdef OSWindows
SocketErrorCode WindowsSocketAgentStartup(IOSocket* socket)
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA* wsaData = &socket->WindowsSocketAgentData;
    int result = WSAStartup(wVersionRequested, wsaData);

    switch (result)
    {
        case WSASYSNOTREADY:
            return SubSystemNotReady;

        case WSAVERNOTSUPPORTED:
            return VersionNotSupported;

        case WSAEINPROGRESS:
            return BlockedByOtherOperation;

        case WSAEPROCLIM:
            return LimitReached;

        case WSAEFAULT:
            return InvalidParameter;

        case 0:
        default:
            return SocketNoError;
    }
}
#endif