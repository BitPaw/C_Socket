#include "IOSocket.h"
#include <stdio.h>
#include <string.h>


char SocketIsCurrentlyUsed(IOSocket* socket)
{
    return socket->ID != -1;
}

void SocketInitialize(IOSocket* socket)
{
    socket->ID = -1;
    socket->Port = -1;
    socket->IPMode = IPVersionInvalid;

    socket->OnMessage = 0;
    socket->OnConnected = 0;
    socket->OnDisconnected = 0;

    memset(socket->Message, 0, SocketBufferSize);
    memset(&socket->AdressIPv4, 0, sizeof(struct sockaddr_in));

#ifdef OSUnix
    memset(&socket->AdressIPv6, 0, sizeof(socket->AdressIPv6));
#elif defined(OSWindows)
    socket->AdressIPv6 = 0;
#endif
}

char SocketSetupAdress(IOSocket* connectionSocket, IPVersion ipVersion, char* ip, unsigned short port)
{  
    int adressFamily = SocketGetAdressFamily(ipVersion);

    connectionSocket->IPMode = ipVersion;
    connectionSocket->Port = port;

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
#ifdef OSUnix
            struct addrinfo adressIPv6Hint;
            struct addrinfo* adressIPv6Adress = &connectionSocket->AdressIPv6;
            struct addrinfo** adressIPv6HintPointer = &adressIPv6Adress;
#elif defined(OSWindows)
            ADDRINFO adressIPv6Hint;
            ADDRINFO** adressIPv6HintPointer = &connectionSocket->AdressIPv6;
#endif

            char portString[10];
            int result;

            sprintf(portString, "%i", port);
            memset(&adressIPv6Hint, 0, sizeof(adressIPv6Hint));
  
            adressIPv6Hint.ai_family = adressFamily; //    AF_INET / AF_INET6:
            adressIPv6Hint.ai_socktype = SOCK_STREAM;
            adressIPv6Hint.ai_flags = AI_NUMERICHOST | AI_PASSIVE;
            adressIPv6Hint.ai_protocol = IPPROTO_TCP;

            result = getaddrinfo(ip, portString, &adressIPv6Hint, adressIPv6HintPointer);

#ifdef OSUnix
            connectionSocket->AdressIPv6 = **adressIPv6HintPointer;
#endif

            switch (result)
            {
                case 0:
                    return SocketNoError;

                case EAI_AGAIN: 	// A temporary failure in name resolution occurred.
                {
                    break;
                }
                case EAI_BADFLAGS: // An invalid value was provided for the ai_flags member of the pHints parameter.
                {
                    break;
                }
                case EAI_FAIL: // A nonrecoverable failure in name resolution occurred.
                {
                    break;
                }
                case EAI_FAMILY: // The ai_family member of the pHints parameter is not supported.
                {
                    break;
                }
                case EAI_MEMORY: // A memory allocation failure occurred.
                {
                    break;
                }
                case EAI_NONAME: // The name does not resolve for the supplied parameters or the pNodeName and pServiceName parameters were not provided.
                {
                    break;
                }
                case EAI_SERVICE: // The pServiceName parameter is not supported for the specified ai_socktype member of the pHints parameter.
                {
                    break;
                }
                case EAI_SOCKTYPE: // The ai_socktype member of the pHints parameter is not supported.
                {
                    break;
                }
            }

            break;
        }
    }

    return SocketNoError; // Delete this
}

SocketError SocketOpen(IOSocket* serverSocket, IPVersion ipVersion, unsigned short port)
{    
    SocketInitialize(serverSocket);

#ifdef OSWindows
    SocketError errorCode = WindowsSocketAgentStartup();

    if (errorCode != SocketNoError)
    {
        return errorCode;
    }
#endif 

    SocketSetupAdress(serverSocket, ipVersion, 0, port);

    // Create Socket
    {
        int adressFamily;
        int streamType;
        int protocol;

        switch (serverSocket->IPMode)
        {
            default:
            case IPVersion4:
            {
                adressFamily = serverSocket->AdressIPv4.sin_family;
                streamType = SOCK_STREAM;
                protocol = 0;
                break;
            }
            case IPVersion6:
            {
#ifdef OSUnix
                adressFamily = serverSocket->AdressIPv6.ai_family;
                streamType = serverSocket->AdressIPv6.ai_socktype;
                protocol = serverSocket->AdressIPv6.ai_protocol;
#elif defined(OSWindows)
                adressFamily = serverSocket->AdressIPv6->ai_family;
                streamType = serverSocket->AdressIPv6->ai_socktype;
                protocol = serverSocket->AdressIPv6->ai_protocol;
#endif

                break;
            }
        }

        serverSocket->ID = socket(adressFamily, streamType, protocol);

        if (serverSocket->ID == -1)
        {
            return SocketCreationFailure;
        }
    }

    // Set Socket Options
    {
        const int level = SOL_SOCKET;

#ifdef OSUnix
        const int optionName = SO_REUSEADDR;      // Do not use SO_REUSEADDR, else the port can be hacked. SO_REUSEPORT
#elif defined(OSWindows)
        const int optionName = SO_EXCLUSIVEADDRUSE;
#endif
        int opval = 1;
        int optionsocketResult = setsockopt(serverSocket->ID, level, optionName, &opval, sizeof(opval));

        if (optionsocketResult == 1)
        {
            return SocketOptionFailure;
        }
    }
       
    // Bind Socket
    {
        int bindingResult = -1;
        switch (ipVersion)
        {
            case IPVersion4:
            {
                bindingResult = bind(serverSocket->ID, &serverSocket->AdressIPv4, sizeof(serverSocket->AdressIPv4));
                break;
            }

            case IPVersion6:
            {
#ifdef OSUnix
                bindingResult = bind(serverSocket->ID, serverSocket->AdressIPv6.ai_addr, serverSocket->AdressIPv6.ai_addrlen);
#elif defined(OSWindows)
                bindingResult = bind(serverSocket->ID, serverSocket->AdressIPv6->ai_addr, serverSocket->AdressIPv6->ai_addrlen);
#endif


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
        int listeningResult = listen(serverSocket->ID, maximalClientsWaitingInQueue);

        if (listeningResult == -1)
        {
            return SocketListeningFailure;
        }
    }

    return SocketNoError;
}

void SocketClose(IOSocket* socket)
{
    char isSocketUsed = SocketIsCurrentlyUsed(socket);
    char hasOnDisconnectCallBack = socket->OnDisconnected != 0;

    if (!isSocketUsed)
    {
        return;
    }

#ifdef OSWindows
    shutdown(socket->ID, SD_SEND);
    closesocket(socket->ID);
#elif defined(OSUnix)
    close(socket->ID);
#endif     

    if (hasOnDisconnectCallBack)
    {
        socket->OnDisconnected(socket->ID);
    }

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
#ifdef OSUnix
            clientSocket->ID = accept(serverSocket->ID, clientSocket->AdressIPv6.ai_addr, clientSocket->AdressIPv6.ai_addrlen);
#elif defined(OSWindows)
            clientSocket->AdressIPv6 = calloc(1, sizeof(ADDRINFO));
            clientSocket->ID = accept(serverSocket->ID, clientSocket->AdressIPv6->ai_addr, clientSocket->AdressIPv6->ai_addrlen);
#endif
            break;
        }
    }
}

SocketError SocketConnect(IOSocket* clientSocket, IOSocket* serverSocket, char* ipAdress, unsigned short port)
{
    SocketInitialize(clientSocket);
    SocketInitialize(serverSocket); 

#ifdef OSWindows
    SocketError errorCode = WindowsSocketAgentStartup();

    if (errorCode != SocketNoError)
    {
        return errorCode;
    }
#endif  

    SocketSetupAdress(clientSocket, AnalyseIPVersion(ipAdress) ,ipAdress, port);

    // Create Socket
    {
        int adressFamily;
        int streamType;
        int protocol;       

        switch (clientSocket->IPMode)
        {
            case IPVersion4:
            {
                adressFamily = clientSocket->AdressIPv4.sin_family;
                streamType = SOCK_STREAM;
                protocol = 0;
                break;                
            }   
            case IPVersion6:
            {
#ifdef OSUnix
                adressFamily = clientSocket->AdressIPv6.ai_family;
                streamType = clientSocket->AdressIPv6.ai_socktype;
                protocol = clientSocket->AdressIPv6.ai_protocol;
#elif defined(OSWindows)
                adressFamily = clientSocket->AdressIPv6->ai_family;
                streamType = clientSocket->AdressIPv6->ai_socktype;
                protocol = clientSocket->AdressIPv6->ai_protocol;
#endif

                break;
            }
            default:
            {
                return SocketCreationFailure;
            }
        }

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
#ifdef OSUnix
                serverSocket->ID = connect(clientSocket->ID, clientSocket->AdressIPv6.ai_addr, clientSocket->AdressIPv6.ai_addrlen);
#elif defined(OSWindows)
                serverSocket->ID = connect(clientSocket->ID, clientSocket->AdressIPv6->ai_addr, clientSocket->AdressIPv6->ai_addrlen);
#endif

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

SocketError SocketRead(IOSocket* socket)
{
    unsigned int byteRead = 0;

    memset(socket->Message, 0, SocketBufferSize);

#ifdef OSUnix
    byteRead = read(socket->ID, &socket->Message[0], SocketBufferSize - 1);
#elif defined(OSWindows)
    byteRead = recv(socket->ID, &socket->Message[0], SocketBufferSize - 1, 0);
#endif

    if (byteRead == -1)
    {
        return SocketRecieveFailure;
    }

    if (byteRead == 0) // endOfFile
    {
        return SocketRecieveConnectionClosed;
    }

    return SocketNoError;
}

SocketError SocketWrite(IOSocket* socket, char* message)
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
#elif defined(OSWindows)
unsigned long SocketReadAsync(IOSocket* socket)
#endif
{
    // Send & Recieve <Permanent Loop>!
    while (1)
    {
        SocketError errorCode = SocketRead(socket);
        char* message = &socket->Message[0];

        if (errorCode == SocketNoError)
        {
            char hasCallBack = socket->OnMessage != 0;

            if (hasCallBack)
            {
                socket->OnMessage(socket->ID, message);
            }
        }
        else
        {
            break;
        }
    }

    SocketClose(socket);

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
SocketError WindowsSocketAgentStartup()
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    int result = -1;

    memset(&wsaData, 0, sizeof(WSADATA));

    result = WSAStartup(wVersionRequested, &wsaData);

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
int WindowsSocketAgentShutdown()
{
    int result = WSACleanup();

    switch (result)
    {
        case WSANOTINITIALISED:
        {
            return SubSystemNotInitialised;
        }
        case WSAENETDOWN:
        {
            return SubSystemNetworkFailed;
        }
        case WSAEINPROGRESS:
        {
            return SocketIsBlocking;
        }   
        case 0:
        default:
            return SocketNoError;
    }
}
#endif