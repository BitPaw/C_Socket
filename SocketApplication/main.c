#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "CommandManager.h"
#include "CommandToken.h"

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif
#include "CommunicationRole.h"

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif
#include "ApplicationState.h"

void ChangeState(ApplicationState applicationState)
{
    printf
    (
        "[System] State changed from <%s> to <%s>.\n",
        ApplicationStateToString(_currentApplicationState),
        ApplicationStateToString(applicationState)
    );

    _currentApplicationState = applicationState;
}

int main(int numberOfArguments, char* arguments[])
{
    CommunicationRole mode = ModeInvalid;
    IPVersion ipVersion = -1;
    Thread thread;
    char* ip = 0;    
    unsigned short port = -1;
    char inputBuffer[1024];

    _currentApplicationState = StateNeutralIDLE;

    ClientInitialize(&_client);
    ServerInitialize(&_server);

    printf(ASCIIArtLogo);

    //system("color 0B");

    switch (numberOfArguments)
    {
        case 1:
        {
            ChangeState(StateSelectingDefaultPort);
            break;
        }

        case 4:
        {
            char* portText = arguments[3];

            port = atoi(portText);

            if (port == 0)
            {
                printf("[Error] Invalid port");
                return -1;
            }

            // no break, fall thoutghhh
        }

        case 3:
        {
            char* operatingMode = arguments[1];
            char* ipOption = arguments[2];
            char ipModeChar = ipOption[0];
            char isFirstLetterComma = operatingMode[0] == '-';
            char commandLetter = 0;

            if (!isFirstLetterComma)
            {
                printf("[Error] Invalid Parameters");
                return -1;
            }

            commandLetter = operatingMode[1];

            switch (commandLetter)
            {
                case 'C':
                case 'c':
                {
                    ip = ipOption;
                    ipVersion = AnalyseIPVersion(ipOption);
                    char isValidIP = IsValidIP(ipOption);

                    mode = ModeClient;

                    if (!isValidIP)
                    {
                        printf("Invalid IP.");
                        return -1;
                    }

                    ChangeState(StateClientConnecting);

                    break;
                }

                case 'S':
                case 's':
                {
                    mode = ModeServer;

                    switch (ipModeChar)
                    {
                        case '4':
                        {
                            ipVersion = IPVersion4;
                            break;
                        }
                        case '6':
                        {
                            ipVersion = IPVersion6;
                            break;
                        }
                        default:
                        {
                            printf("[Error] Invalid IP Mode. 4 or 6 only");
                            return -1;
                        }
                    }

                    ChangeState(StateServerListening);

                    break;
                }
                default:
                {
                    printf("[Error] Invalid operation mode");
                    return -1;
                }
            }

            break;
        }
        default:
        {
            printf("[Error] Invalid Parameters");
            return -1;
        }
    } 

    while (1)
    {
        switch (_currentApplicationState)
        {
            case StateSelectMode:
            {
                printf(MenuMode); 
                printf("[Input] Mode : ");

                int result = scanf(ScanfInputTag, inputBuffer);
                int mode = atoi(inputBuffer);

                switch (mode)
                {
                    case 0:
                    {
                        mode = ModeClient;
                        ChangeState(StateClientSelectingIP);
                        break;
                    }
                    case 1:
                    {
                        mode = ModeServer;
                        ChangeState(StateServerSelectingIPVersion);
                        break;
                    }
                    default:
                    {
                        mode = ModeInvalid;
                        printf(InvalidModeInput);
                        break;
                    }
                }                

                printf(BannerFooter);     

                break;
            }
            case StateServerSelectingIPVersion:
            {
                char ipInput = -1;

                printf
                (
                    "[?] Which IP Version shall be used?\n"
                    "    Select 4 or 6 : "
                );
                char scanResult = scanf(ScanfInputTag, &ipInput);

                switch (ipInput)
                {
                    case '4':
                    {
                        ipVersion = IPVersion4;
                        break;
                    }
                    case '6':
                    {
                        ipVersion = IPVersion6;
                        break;
                    }
                    default:
                    {
                        ipVersion = IPVersionInvalid;
                        printf("Invalid IP Version! Check your input.\n");
                        break;
                    }
                }

                if (ipVersion != IPVersionInvalid)
                {
                    ChangeState(StateServerStarting);
                }

                break;
            }
            case StateSelectingSpecificPort:
            {
                printf
                (
                    "[?] Specify Port : "
                );

                int result = scanf(ScanfInputTag, inputBuffer);
                int convertedNumber = atoi(inputBuffer);              

                if (0 < convertedNumber && convertedNumber < 65535)
                {
                    port = convertedNumber;
                    ChangeState(StateSelectMode);                    
                }  
                else
                {
                    printf("[Error] Invalid Port. Check your input.\n");
                }

                break;
            }
            case StateSelectingDefaultPort:
            {
                char useDefaultPort = 0;

                printf
                (
                    "[?] Use default Port <%i>?\n"
                    "    <y/n> : ",
                    DefaultPort
                );

                int result = scanf(ScanfInputTag, inputBuffer);

                useDefaultPort = inputBuffer[0];

                switch (useDefaultPort)
                {
                    case 'Y':
                    case 'y':
                    {
                        port = DefaultPort;
                        ChangeState(StateSelectMode);
                        break;
                    }
                    case 'N':
                    case 'n':
                    {
                        ChangeState(StateSelectingSpecificPort);
                        break;
                    }
                    default:
                    {
                        printf("[Error] Invalid Option. Check Input.\n");
                        break;
                    }
                }

                break;
            }
            case StateClientSelectingIP:
            {
                printf(BannerClientSelectIPHeader);

                int scanResult = scanf(ScanfInputTag, &inputBuffer);

                char hasUserEnteredIP = memcmp(TagNotSet, &inputBuffer, 6) != 0;

                if (hasUserEnteredIP)
                {
                    char result = IsValidIP(inputBuffer);

                    if (result)
                    {
                        ChangeState(StateClientConnecting);
                    }
                    else
                    {
                        printf(InvalidIPInput);
                    }
                }
                else
                {
                    printf(NoIPSelected);
                    memcpy(inputBuffer, "127.0.0.1", 10);
                    ChangeState(StateClientConnecting);
                }                

                printf(BannerFooter);

                break;
            }
            case StateClientConnecting:
            {            
                printf(BannerConnectToServer);

                ClientConnect(&_client, &inputBuffer[0], port);

                switch (_client.State)
                {
                    case ConnectionOnline:
                    {
                        _client.Socket.OnConnected = OnRemoteServerConnect;
                        _client.Socket.OnMessage = OnRemoteServerMessageRecieved;
                        _client.Socket.OnDisconnected = OnRemoteServerDisconnect;

                        ChangeState(StateClientConnected);

                        ThreadCreate(&thread, SocketReadAsync, &_client.Socket);  

                        printf(ConnectionSuccesful);

                        break;
                    }
                    case ConnectionOffline:
                    {
                        printf(ServerUnreachable);
                        break;
                    }
                }                
            
                printf(BannerFooter);         

                break;
            }
            case StateClientConnected:
            {
                // printf(BannerSendAndRecieve);

                char scanResult = scanf(ScanfInputTag, inputBuffer);

                SocketErrorCode errorCode = SocketWrite(&_client.Socket, inputBuffer);

                switch (errorCode)
                {
                    case SocketNoError:
                    {
                        printf("[You] %s\n", inputBuffer);
                        break;
                    }

                    default:
                    {
                        printf("[Error] Sending failed. ErrorCode: <%i>.\n", errorCode);
                        break;
                    }
                }

                break;
            }
            case StateServerStarting:
            {
                ServerStart(&_server, ipVersion, port);

                ServerPrint(&_server);

                switch (_server.State)
                {
                    case ConnectionOffline:
                    {
                        printf(ServerPortBlocked);
                        ChangeState(StateServerOffline);
                        break;
                    }

                    case ConnectionOnline:
                    {
                        printf(BannerSendAndRecieve);
                        ChangeState(StateServerListening);
                        break;
                    }
                }

                break;
            }
            case StateServerListening:
            {
                if (ServerIsRunning(&_server))
                {
                    Client* client = ServerWaitForClient(&_server);

                    if (client != 0)
                    {
                        client->Socket.OnConnected = OnRemoteClientConnect;
                        client->Socket.OnMessage = OnRemoteClientMessageRecieved;
                        client->Socket.OnDisconnected = OnRemoteClientDisconnect;

                        client->Socket.OnConnected(client->Socket.ID);
                    }
                }
                else
                {
                    ChangeState(StateServerOffline);
                }

                break;
            }
        }
    }

    //     ClientDisconnect(&_client);     ServerStop(&_server);                 

    return 0;
}


void OnRemoteServerMessageRecieved(int socketID, char* message)
{
    printf("[Server]%s\n", message);
}

void OnRemoteClientMessageRecieved(int socketID, char* message)
{
    char messageBuffer[1024];
    char* messageToSend = 0;
    CommandToken commandToken;
    FileError fileError = FileErrorNotSet;

    CommandTokenInitialize(&commandToken);

    commandToken.ClientSocketID = socketID;

    CommandTokenParse(&commandToken, message);

    switch (commandToken.CommandType)
    {
        case CommandFileDataPut:
        {
            printf("[Client][%i][Command] PUT KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);

            fileError = FileDataPut(commandToken.Key, commandToken.Value);

            break;
        }
        case CommandFileDataGet:
        {
            printf("[Client][%i][Command] GET KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);

            fileError = FileDataGet(commandToken.Key, messageBuffer);

            messageToSend = messageBuffer;

            break;
        }
        case CommandFileDelete:
        {
            printf("[Client][%i][Command] DELETE KEY:%s\n", socketID, commandToken.Key);

            fileError = FileDelete(commandToken.Key);

            break;
        }

        case CommandFileLock:
        {
            printf("[Client][%i][Command] LockFile KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);

            fileError = FileLock(commandToken.Key);

            break;
        }
        case CommandFileUnlock:
        {
            printf("[Client][%i][Command] UnlockFile KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);

            fileError = FileUnlock(commandToken.Key);

            break;
        }

        case CommandFileChangePublish:
        {
            printf("[Client][%i][Command] Publish KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);

            fileError = FileChangePublish(commandToken.Key);

            break;
        }
        case CommandFileChangeSubscribe:
        {
            printf("[Client][%i][Command] Subscribe KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);

            fileError = FileChangeSubscribe(commandToken.Key);

            break;
        }

        case CommandOpenProgram:
        {
            printf("[Client][%i][Command] OpenProgramm KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);

            fileError = ProgramOpen(commandToken.Key);

            break;
        }

        case CommandQuit:
        {
            printf("[Client][%i][Command] QUIT\n", socketID);

            ApplicationQuit();

            break;
        }

        case CommandHTTPRequest:
        {
            fileError = FileNoError;

            SendHTTPResponse(&_server, socketID);

            break;
        }

        case CommandInvalid:
        default:
        {
            printf("[Server][Info] Invalid command from Client:%i. Broadcast:%s\n", socketID, message);

            sprintf(messageBuffer, "[Client:%i] %s", socketID, message);

            ServerBroadcastToClients(&_server, messageBuffer);
            break;
        }
    }

    switch (fileError)
    {
        case FileNoError:
        {
            messageToSend = "[OK] Operation successful.";
            break;
        }
        case FileDoesNotExist:
        {
            messageToSend = "[Error] File doesn't exist.";
            break;
        }
        case FileAlreadyExist:
        {
            messageToSend = "[Error] File already exist.";
            break;
        }
        case ProgramNameNotFound:
        {
            messageToSend = "[Error] There is no program with this name accessible.";
            break;
        }
    }

    if (fileError != FileErrorNotSet)
    {
        ServerSendToClient(&_server, commandToken.ClientSocketID, messageToSend);
    }
}

void OnRemoteServerDisconnect(int socketID, char disconnectionCause)
{
    switch (disconnectionCause)
    {
        case 0:
        {
            printf("[Server][Info] Disconnected.\n");
            break;
        }
        case 1:
        {
            printf("[Server][Warning] Lost connection!\n");
            break;
        }
    }
}

void OnRemoteClientDisconnect(int socketID, char disconnectionCause)
{
    switch (disconnectionCause)
    {
        case 0:
        {
            printf("[Server][Info] Client disconnected.\n");
            break;
        }
        case 1:
        {
            printf("[Server][Warning] Client disconnected unexpectedly.\n");
            break;
        }
    }
}

void OnRemoteServerConnect(int socketID)
{
    printf("[Server][Info] Connected succesful!\n");
}

void OnRemoteClientConnect(int socketID)
{
    printf("[Server][Info] New client connected with ID:%i.\n", socketID);

#if 0
    // RensResponse
    {
        char welcomeMessage[100];

        sprintf
        (
            welcomeMessage,
            "Connected to a "
#ifdef linux
            "Linux"
#endif

#ifdef __APPLE__
            "MAC_OS"
#endif

#ifdef OSWindows
            "Windows"
#endif    
            " System as (ID:%.i)",
            socketID
        );

        SocketErrorCode errorCode = ServerSendToClient(&_server, socketID, welcomeMessage);

        if (errorCode != SocketNoError)
        {
            printf("[Server][Error] Couldn't send welcome response. ErrorCode <%i>.\n", errorCode);
        }
    }
#endif
}