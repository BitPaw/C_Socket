#include "IOSocket.h"

#include <stdio.h>

void SocketInitialize(IOSocket* socket)
{
    socket->ID = -1;
    //socket->Adress = 0; 
    socket->Port = -1;

#ifdef _WIN32
    //socket->WindowsSocketAgentData;
#endif
}

SocketErrorCode SocketOpen(IOSocket* ioSocket, unsigned short port)
{
    const int adressFamily = AF_INET;
    const int streamType = SOCK_STREAM;
    const int protocol = 0;
    const int objectSize = sizeof(ioSocket->Adress);
    const struct sockaddr* socketAdressPointer = &(ioSocket->Adress);

    ioSocket->ID = -1;
    ioSocket->Port = port;

#ifdef _WIN32
    WORD wVersionRequested = MAKEWORD(2, 2);
    int result = WSAStartup(wVersionRequested, &ioSocket->WindowsSocketAgentData);

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
            // Do nothing
            break;
    }
#endif // _WIN32

    // Create a socket (IPv4) as a stream.
    // Returns -1 on failure. ID if succesful. 
    ioSocket->ID = socket(adressFamily, streamType, protocol);

    if (ioSocket->ID == -1)
    {
        return SocketCreationFailure;
    }

    ioSocket->Adress.sin_family = AF_INET;
    ioSocket->Adress.sin_addr.s_addr = htonl(INADDR_ANY);
    ioSocket->Adress.sin_port = htons(port);

    int opval = 1;
    char* options = SO_REUSEADDR;

#if linux
    options |= SO_REUSEPORT;
#endif // linux

    int optionsocketResult = setsockopt(ioSocket->ID, SOL_SOCKET, options, &opval, sizeof(opval));

    if (optionsocketResult == 1)
    {
        return SocketOptionFailure;
    }

    int bindingResult = bind(ioSocket->ID, socketAdressPointer, objectSize);

    if (bindingResult == -1)
    {
        return SocketBindingFailure;
    }

    int listeningResult = listen(ioSocket->ID, 10);

    if (listeningResult == -1)
    {
        return SocketListeningFailure;
    }

    return NoError;
}

void SocketClose(IOSocket* socket)
{
#ifdef _WIN32
    //WSACleanup();
    closesocket(socket->ID);
#endif // _WIN32  

#ifdef linux
    close(socket->ID);
#endif // linux    

   // SocketInitialize(socket);
}

void SocketAwaitConnection(IOSocket* serverSocket, IOSocket* clientSocket)
{
    // &clientSocket->Adress, sizeof(clientSocket->Adress)

    clientSocket->ID = accept(serverSocket->ID, 0, 0);
}

void SocketConnect(IOSocket* clientSocket, IOSocket* serverSocket, char* ipAdress, unsigned short port)
{
    int length = sizeof(clientSocket->Adress);
    const struct sockaddr* socketAdressPointer = &(clientSocket->Adress);

    clientSocket->Adress.sin_family = AF_INET;
    clientSocket->Adress.sin_addr.s_addr = htonl(ipAdress);
    clientSocket->Adress.sin_port = htons(port);

    serverSocket->ID = connect(clientSocket->ID, socketAdressPointer, length);
}

void SocketRead(IOSocket* socket)
{
    const unsigned int inputBufferSize = SocketBufferSize;
    char inputBuffer[SocketBufferSize];
    char readError = 0;
    unsigned int byteReadCurrent;
    unsigned int byteReadPrivoly = 0;
    char didChange = 0;     

#ifdef linux
    while (1)
    {
        memset(inputBuffer, 0, inputBufferSize);

        unsigned int size = read(socket->ID, &inputBuffer[0], inputBufferSize - 1);
        char endOfFile = size == 0;
        readError = size == -1;

        if (readError)
        {
            break;
        }

        if ((memcmp(&inputBuffer[size - 1], "\n\0", 2) == 0) || endOfFile)
        {
            break;
        }
    }     
#endif // linux


#if _WIN320
    memset(inputBuffer, 0, inputBufferSize);

    do
    {
        byteReadCurrent = recv(socket->ID, &inputBuffer[0], inputBufferSize - 1, 0);

        if (byteReadCurrent == 0)
        {
            break;
        }

        //memset(inputBuffer, 0, inputBufferSize);

        //byteReadCurrent = recv(socket->ID, &inputBuffer[0], byteReadCurrent, 0);

        for (size_t i = 0; i < byteReadCurrent; i++)
        {
            printf("%c", inputBuffer[i]);
        }


    }
    while (didChange);
#endif // _WIN32    
}

void SocketWrite(IOSocket* socket, char* message)
{
    int messageLengh = 0;
    unsigned int writtenBytes = 0;

    while (message[messageLengh++] != '\0') { }

#if linux
    writtenBytes = write(socket->ID, message, messageLengh);
#elif _WIN32
    writtenBytes = send(socket->ID, message, messageLengh, MSG_OOB);
#endif  
}
