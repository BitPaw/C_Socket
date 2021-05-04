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
    SocketErrorCode errorCode = WindowsSocketAgentStartup(&ioSocket);

    if (errorCode != NoError)
    {
        return errorCode;
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

#if linux
    char* options = SO_REUSEADDR | SO_REUSEPORT;
#elif _WIN32
    char* options = SO_REUSEADDR;
#endif  

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
    shutdown(socket->ID, SD_SEND);
    closesocket(socket->ID);
    //WSACleanup();
#endif // _WIN32  

#ifdef linux
    close(socket->ID);
#endif // linux    

    SocketInitialize(socket);
}

void SocketAwaitConnection(IOSocket* serverSocket, IOSocket* clientSocket)
{
    // &clientSocket->Adress, sizeof(clientSocket->Adress)

    clientSocket->ID = accept(serverSocket->ID, 0, 0);
  
}

SocketErrorCode SocketConnect(IOSocket* clientSocket, IOSocket* serverSocket, char* ipAdress, unsigned short port)
{
    SocketErrorCode errorCode;
    const int adressFamily = AF_INET;
    const int streamType = SOCK_STREAM;
    const int protocol = 0;
    int length = sizeof(clientSocket->Adress);
    const struct sockaddr* socketAdressPointer = &(clientSocket->Adress);
   
#ifdef _WIN32
    errorCode = WindowsSocketAgentStartup(&clientSocket);

    if (errorCode != NoError)
    {
        return errorCode;
    }
#endif // _WIN32

    clientSocket->Adress.sin_family = adressFamily;
    clientSocket->Adress.sin_addr.s_addr = inet_addr(ipAdress);
    clientSocket->Adress.sin_port = htons(port);

    clientSocket->ID = socket(adressFamily, streamType, protocol);

    if (clientSocket->ID == 1)
    {
        return SocketCreationFailure;
    }

    serverSocket->ID = connect(clientSocket->ID, socketAdressPointer, length);

    if (serverSocket->ID == -1)
    {
        return SocketConnectionFailure;
    }

    return NoError;
}

SocketErrorCode SocketRead(IOSocket* socket)
{
    unsigned int byteRead = 0;
    char endOfFile = 0;

    memset(socket->Message, 0, SocketBufferSize);

#ifdef linux
    byteRead = read(socket->ID, &inputBuffer[0], inputBufferSize - 1);
#elif _WIN32
    byteRead = recv(socket->ID, &socket->Message[0], SocketBufferSize - 1, 0);
#endif

    endOfFile = byteRead == 0;

    if (byteRead == -1)
    {
        return SocketRecieveFailure;
    }

    if (endOfFile)
    {
        memset(socket->Message, 0, SocketBufferSize);
    }

    return NoError;
}

SocketErrorCode SocketWrite(IOSocket* socket, char* message)
{
    int messageLengh = 0;
    unsigned int writtenBytes = 0;

    while (message[messageLengh++] != '\0') { }

   // memcpy(&message[messageLengh - 1], "\r\n\0", 3 * sizeof(char)); // Add line ending.

    //essageLengh += 2; // add cause of new length.

#if linux
    writtenBytes = write(socket->ID, message, messageLengh);
#elif _WIN32
    writtenBytes = send(socket->ID, message, messageLengh, 0);
#endif  

    if (writtenBytes == -1)
    {        
        return SocketSendFailure;
    }

    return NoError;
}

char IsValidIP(char* ipAdress)
{
    const unsigned int expectedDots = 3;
    const unsigned int minimalSize = 7; // 0.0.0.0
    const unsigned int maximalSize = 15; //255.255.255.255
    unsigned int index = 0;
    unsigned int length = 0;
    unsigned int countedDots = 0;
    unsigned char hasValidLength = 0;
    unsigned char hasEnigthDots = 0;

    unsigned short octetValue = 0;
    unsigned short exponent = 100;

    if (ipAdress == 0)
    {
        return 0;
    }

    for ( ; ipAdress[index] != '\0'; index++)
    {
        char character = ipAdress[index] ;
        char isDot = character == '.';
        char isInRange = (character >= '0' && character <= '9') || character;

        if (!isInRange)
        {
            return 0;
        }

        if (isDot)
        {  
            countedDots++;
            octetValue = 0;
            exponent = 100;
        }
        else
        {       
            octetValue += (character - '0') * exponent;

            if (octetValue > 255)
            {
                return 0;
            }

            exponent /= 10;
        }

        length++;
    }

    hasValidLength = length >= minimalSize && length <= maximalSize;
    hasEnigthDots = countedDots == expectedDots;

    if (!hasValidLength)
    {
        return 0;
    }

    if (!hasEnigthDots)
    {
        return 0;
    }


    return 1;
}



#ifdef _WIN32
SocketErrorCode WindowsSocketAgentStartup(IOSocket* socket)
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    int result = WSAStartup(wVersionRequested, &socket->WindowsSocketAgentData);

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
            return NoError;
    }
}
#endif // !_WIN32