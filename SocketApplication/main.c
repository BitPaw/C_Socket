#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../SocketSystem/Server.h"
#include "../SocketSystem/IOSocket.h"
#include "../SocketSystem/Client.h"

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif
#include "CommandToken.h"

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

#define ScanfInputTag " %50[^\n]"

// system("@cls||clear");

unsigned short DefaultPort = 5678u;
const char TagNotSet[] = "NotSet";
const char ConnectionSuccesful[] = "[OK] Connection successful!\n";
const char ConnectionFailed[] = "[Error] Connection Failed!\n";
const char InvalidModeInput[] = "[Error] Invalid Mode! Please select a valid option.\n";
const char InvalidIPInput[] = "[Error] Invalid IP! Please check your input.\n";
const char NoIPSelected[] = "[Info] No IP selected! Guessing localhost (127.0.0.1).\n";
const char ServerPortBlocked[] = "[Error] Port seems to be blocked. Server can't be started.\n";
const char MenuMode[] =
"+---------------------------------------------------------+\n"
"| Select operation mode                                   |\n"
"+---------------------------------------------------------+\n"
"| 0 : Client Mode                                         |\n"
"| 1 : Server Mode                                         |\n"
"+---------------------------------------------------------+\n";
const char BannerFooter[] =
"+---------------------------------------------------------+\n\n\n";
const char BannerConnectToServer[] =
"+---------------------------------------------------------+\n"
"| Connect To Server                                       |\n"
"+---------------------------------------------------------+\n";
const char BannerConnecting[] =
"+---------------------------------------------------------+\n"
"| Connecting...                                           |\n"
"+---------------------------------------------------------+\n";
const char BannerSendAndRecieve[] =
"+---------------------------------------------------------+\n"
"| Send & Recieve                                          |\n"
"+---------------------------------------------------------+\n";
const char ServerUnreachable[] =
"[Info]  It seems that the server is unreachable\n"
"        or even offline. Use another IP or try later.\n";












static Server _server;
static Client _client;


void OnRemoteServerMessageRecieved(int socketID, char* message)
{
    printf("[Server]%s\n", message);
}

void OnRemoteClientMessageRecieved(int socketID, char* message)
{
    CommandToken commandToken;
    CommandTokenInitialize(&commandToken);

    commandToken.ClientSocketID = socketID;

    CommandTokenParse(&commandToken, message);

    switch (commandToken.CommandType)
    {    
        case CommandPut:
        {
            printf("[Client][%i][Command] PUT KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);
            break;
        }            
        case CommandGet:
        {
            printf("[Client][%i][Command] GET KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);
            break;
        }
        case CommandDelete:
        {
            printf("[Client][%i][Command] DELETE KEY:%s\n", socketID, commandToken.Key);
            break;
        }

        case CommandLockFile:
        {
            printf("[Client][%i][Command] LockFile KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);
            break;
        }
        case CommandUnlockFile:
        {
            printf("[Client][%i][Command] UnlockFile KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);
            break;
        }

        case CommandPublish:
        {
            printf("[Client][%i][Command] Publish KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);
            break;
        }
        case CommandSubscribe:
        {
            printf("[Client][%i][Command] Subscribe KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);
            break;
        }

        case CommandOpenProgram:
        {
            printf("[Client][%i][Command] OpenProgramm KEY:%s Value:%s\n", socketID, commandToken.Key, commandToken.Value);
            break;
        }

        case CommandQuit:
        {
            printf("[Client][%i][Command] QUIT\n", socketID);
            break;
        }

        case CommandInvalid:
        default:
        {
            printf("[Server][Info] Invalid command from Client:%i. Handle as broadcast message.\n", socketID);
            char messageBuffer[100];

            sprintf(messageBuffer, "[Client:%i] %s", socketID, message);

            ServerBroadcastToClients(&_server, messageBuffer);
            break;
        }
    }   
}

void OnRemoteServerDisconnect(int socketID, char disconnectionCause)
{
    switch (disconnectionCause)
    {
        case 0 :
        {
            printf("[Server][Info] disconnected.\n");
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
            printf("[Server][Info] disconnected.\n");
            break;
        }
        case 1:
        {
            printf("[Server][Warning] Client lost connection!\n");
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
            " as (%i)",
            socketID
        );

        SocketErrorCode errorCode = ServerSendToClient(&_server, socketID, welcomeMessage);

        if (errorCode != SocketNoError)
        {
            printf("[Server][Error] Couldn't send welcome response. ErrorCode <%i>.\n", errorCode);
        }
    }   
}

int main()
{
    char mode = -1;

    //---[Get operating mode]--------------------------------------------------
    printf(MenuMode);

    while (1)
    {
        printf("[Input] Mode : ");
        mode = getc(stdin);

        if (mode == '0' || mode == '1')
        {
            break;
        }

        printf(InvalidModeInput);
    }
    //-------------------------------------------------------------------------

    printf(BannerFooter);

    switch (mode)
    {
        case '0':
        {
            char quitFlag = 0;
            char command = '-';
            const int bufferLength = 50;
            char inputDataBuffer[50];
            unsigned short port = DefaultPort;

            Thread thread;
            ClientInitialize(&_client);

            printf(BannerConnectToServer);
            printf("[Info]  Port : %i\n", port);

            while (1) // Repeat until connected succesfully.
            {    
                while (1) // Repeat until the entered IP was valid.
                {
                    memset(inputDataBuffer, 0, bufferLength);
                    memcpy(inputDataBuffer, TagNotSet, 6);

                    printf("[Input] IP   : ");

                    int scanResult = scanf(ScanfInputTag, &inputDataBuffer);

                    char hasUserEnteredIP = memcmp(TagNotSet, &inputDataBuffer, 6) != 0;

                    if (hasUserEnteredIP)
                    {
                        char result = IsValidIP(inputDataBuffer);

                        if (result == 0)
                        {                        
                            break; // IP OK, quit loop.     
                        }
                        else
                        {
                            printf(InvalidIPInput);
                        }
                    }
                    else
                    {
                        printf(NoIPSelected);
                        memcpy(inputDataBuffer, "127.0.0.1", 10);
                        break;
                    }                
                }     

                printf(BannerFooter);
                printf(BannerConnecting);

                ClientConnect(&_client, &inputDataBuffer[0], port);

                if (_client.State == ConnectionOnline)
                {
                    _client.Socket.OnConnected = OnRemoteServerConnect;
                    _client.Socket.OnMessage = OnRemoteServerMessageRecieved;
                    _client.Socket.OnDisconnected = OnRemoteServerDisconnect;

                    printf(ConnectionSuccesful);
                    break;
                }
                else
                {
                    printf(ConnectionFailed);
                    printf(BannerFooter);
                }

                printf(BannerConnectToServer);
                printf(ServerUnreachable);
            }

            printf(BannerFooter);

            ThreadCreate(&thread, SocketReadAsync, &_client.Socket);

            printf(BannerSendAndRecieve);

            while (_client.Socket.ID != -1)
            {
                char scanResult = scanf(ScanfInputTag, &inputDataBuffer[0]);

                SocketErrorCode errorCode = SocketWrite(&_client.Socket, &inputDataBuffer[0]);

                switch (errorCode)
                {
                    case SocketNoError:
                    {
                        printf("[You] %s\n", inputDataBuffer);
                        break;
                    }

                    default:
                    {
                        printf("[Error] Sending failed. ErrorCode: <%i>.\n", errorCode);
                        break;
                    }
                }
            }

            ClientDisconnect(&_client);

            break;
        }
        case '1':
        {
            IPVersion ipVersion;
            ServerInitialize(&_server);

            while (1)
            {
                char ipInput = -1; 

                printf("Which IP Version shall be used?\nSelect 4 or 6 : ");
                char scanResult = scanf(ScanfInputTag, &ipInput);

                if (ipInput == '4')
                {
                    ipVersion = IPVersion4;
                    break;
                }

                if (ipInput == '6')
                {
                    ipVersion = IPVersion6;
                    break;
                }

                printf("Invalid IP Version! Check your input.\n");
            }

            ServerStart(&_server, ipVersion, DefaultPort);

            ServerPrint(&_server);

            switch (_server.State)
            {
                case ConnectionOffline:
                {
                    printf(ServerPortBlocked);
                    break;
                }

                case ConnectionOnline:
                {
                    printf(BannerSendAndRecieve);
                    break;
                }

                default:
                case ConnectionInvalid:
                {
                    break;
                }                    
            }          

            while (_server.State == ConnectionOnline)
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

            ServerStop(&_server);

            break;
        }
    }




#ifdef OSWindows
    system("pause");
#else
    printf("Terminated\n");
#endif


    return 0;
}