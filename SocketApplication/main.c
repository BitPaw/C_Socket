#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "CommandToken.h"
#include "CommandError.h"
#include "UserSytem.h"

#include "../ColorPrinter/ColorPrinter.h"
#include "../SocketSystem/OSDefine.h"
#include "../SocketFileManager/FileManager.h"
#include "../List/List.h"
#include "../ColorPrinter/ColorPrinter.h"

void StateChange(ApplicationState newState)
{
    ApplicationState oldState = _socketApplicationData.State;
    char hasChanged = newState != oldState;

    if (!hasChanged)
    {
        return;
    }

    _socketApplicationData.State = newState;

    colorPrintf(BannerGeneral, ApplicationStateToString(newState));

#if 0 // Debug
    printf
    (
        "[System] State changed from <%s> to <%s>.\n",
        ApplicationStateToString(oldState),
        ApplicationStateToString(newState)
    );
#endif 
}

int main(int numberOfArguments, char* arguments[])
{
    SocketApplicationDataInitialize(&_socketApplicationData);  

    AsyncLockCreate(&_socketApplicationData.UserInteractLock);

    ClientInitialize(&_client);
    ServerInitialize(&_server);

    printColors = 1;

    //system("color 0B");

    colorPrintf(ASCIIArtLogo);     

    /* 
        Parse
        
    */

    switch (numberOfArguments)
    {
        case 1:
        {
            StateChange(StateSelectingDefaultPort);
            break;
        }
        case 4:
        {
            char* portText = arguments[3];

            _socketApplicationData.Port = atoi(portText);

            if (_socketApplicationData.Port == 0)
            {
                colorPrintf("[Error] Invalid port");
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
                colorPrintf("[Error] Invalid Parameters");
                return -1;
            }

            commandLetter = operatingMode[1];

            switch (commandLetter)
            {
                // Client
                case 'C':
                case 'c':
                {
                    char isValidIP = IsValidIP(ipOption);

                    _socketApplicationData.CommunicationMode = ModeClient;
                    _socketApplicationData.IP = ipOption;
                    _socketApplicationData.IPMode = AnalyseIPVersion(ipOption); 

                    if (!isValidIP)
                    {
                        colorPrintf("Invalid IP.");
                        return -1;
                    }

                    StateChange(StateClientConnecting);

                    break;
                }

                // Server
                case 'S':
                case 's':
                {
                    _socketApplicationData.CommunicationMode = ModeServer;

                    switch (ipModeChar)
                    {
                        case '4': // IPv4
                        {
                            _socketApplicationData.IPMode = IPVersion4;
                            break;
                        }
                        case '6': // IPv6
                        {
                            _socketApplicationData.IPMode = IPVersion6;
                            break;
                        }
                        default:
                        {
                            colorPrintf("[Error] Invalid IP Mode. 4 or 6 only");
                            return -1;
                        }
                    }

                    StateChange(StateServerListening);

                    break;
                }
                default:
                {
                    colorPrintf("[Error] Invalid operation mode");
                    return -1;
                }
            }

            break;
        }
        default:
        {
            colorPrintf("[Error] Invalid Parameters");
            return -1;
        }
    } 

    while (1)
    {
        switch (_socketApplicationData.State)
        {
            case StateSelectMode:
            {
                colorPrintf(MenuMode); 

                int result = scanf(ScanfInputTag, _socketApplicationData.InputBuffer);
                char inputCharacter = _socketApplicationData.InputBuffer[0];

                switch (inputCharacter)
                {
                    case '0':
                    {
                        _socketApplicationData.CommunicationMode = ModeClient;
                        StateChange(StateClientSelectingIP);
                        break;
                    }
                    case '1':
                    {
                        _socketApplicationData.CommunicationMode = ModeServer;
                        StateChange(StateServerSelectingIPVersion);
                        break;
                    }
                    default:
                    {
                        _socketApplicationData.CommunicationMode = ModeInvalid;
                        colorPrintf(ErrorInvalidModeInput);
                        break;
                    }
                }                

                break;
            }
            case StateServerSelectingIPVersion:
            {                 
                char ipInput = -1;
                char scanResult = 0;

                colorPrintf(InputIPVersion);

                scanResult = scanf(ScanfInputTag, &ipInput);

                switch (ipInput)
                {
                    case '4':
                    {
                        _socketApplicationData.IPMode = IPVersion4;
                        break;
                    }
                    case '6':
                    {
                        _socketApplicationData.IPMode = IPVersion6;
                        break;
                    }
                    default:
                    {
                        _socketApplicationData.IPMode = IPVersionInvalid;
                        colorPrintf(ErrorInvalidIPVersion);
                        break;
                    }
                }

                if (_socketApplicationData.IPMode != IPVersionInvalid)
                {
                    StateChange(StateServerStarting);
                }
                

                break;
            }
            case StateSelectingSpecificPort:
            {
                colorPrintf(InputSpecifyPort);

                int result = scanf(ScanfInputTag, _socketApplicationData.InputBuffer);
                int convertedNumber = atoi(_socketApplicationData.InputBuffer);

                if (0 < convertedNumber && convertedNumber < 65535)
                {
                    _socketApplicationData.Port = convertedNumber;
                    StateChange(StateSelectMode);                    
                }  
                else
                {
                    colorPrintf(ErrorInvalidPort);
                }

                break;
            }
            case StateSelectingDefaultPort:
            {
                char useDefaultPort = 0;
                int result;

                colorPrintf(InputUseDefaultPort, DefaultPort);
                colorPrintf(InputYesNo);

                result = scanf(ScanfInputTag, _socketApplicationData.InputBuffer);
                useDefaultPort = _socketApplicationData.InputBuffer[0];

                switch (useDefaultPort)
                {
                    case 'Y':
                    case 'y':
                    {
                        _socketApplicationData.Port = DefaultPort;
                        StateChange(StateSelectMode);
                        break;
                    }
                    case 'N':
                    case 'n':
                    {
                        StateChange(StateSelectingSpecificPort);
                        break;
                    }
                    default:
                    {
                        colorPrintf(ErrorInvalidInput);
                        break;
                    }
                }

                break;
            }
            case StateClientSelectingIP:
            {
                colorPrintf(BannerClientSelectIPHeader);

                int scanResult = scanf(ScanfInputTag, _socketApplicationData.InputBuffer);

                char hasUserEnteredIP = memcmp(TagNotSet, _socketApplicationData.InputBuffer, 6) != 0;

                if (hasUserEnteredIP)
                {
                    char result = IsValidIP(_socketApplicationData.InputBuffer);

                    if (result)
                    {
                        StateChange(StateClientConnecting);
                    }
                    else
                    {
                        colorPrintf(ErrorInvalidIPInput);
                    }
                }
                else
                {
                    colorPrintf(InfoNoIPSelected);
                    memcpy(_socketApplicationData.InputBuffer, "127.0.0.1", 10);
                    StateChange(StateClientConnecting);
                }                

                break;
            }
            case StateClientConnecting:
            {            
                char connectionSuccesful = ClientConnect(&_client, _socketApplicationData.InputBuffer, _socketApplicationData.Port);

                if (connectionSuccesful)
                {
                    _client.Socket.OnConnected = OnRemoteServerConnect;
                    _client.Socket.OnMessage = OnRemoteServerMessageRecieved;
                    _client.Socket.OnDisconnected = OnRemoteServerDisconnect;

                    colorPrintf(ConnectionSuccesful);

                    StateChange(StateClientConnected);

                    ThreadCreate(&_clientThread, SocketReadAsync, &_client.Socket);
                }
                else
                {
                    colorPrintf(ServerUnreachable);
                    StateChange(StateClientConnectionFailed);                             
                }

                break;
            }
        	
            case StateClientConnectionFailed:
            {
                colorPrintf(InputConnectionTryAgain);

                char inputText[50];
                int scanResult = scanf(ScanfInputTag, &inputText);
                char character = inputText[0];
                
                switch (character)
                {
                    case 'N':
                    case 'n':
                    {
                        StateChange(StateClientSelectingIP);
                        break;
                    }

                    case 'Y':
                    case 'y':
                    {
                        StateChange(StateClientConnecting);
                        break;
                    }
                }

                break;
            }
            case StateClientDisconnecting:
            {
                ClientDisconnect(&_client);

                StateChange(StateClientSelectingIP);

                break;
            }

            case StateClientConnected:
            {
                char scanResult = scanf(ScanfInputTag, _socketApplicationData.InputBuffer);

                if(memcmp(_socketApplicationData.InputBuffer, "HELP", 4 * sizeof(char)) == 0 ||
                   memcmp(_socketApplicationData.InputBuffer, "help", 4 * sizeof(char)) == 0 ||
                   memcmp(_socketApplicationData.InputBuffer, "Help", 4 * sizeof(char)) == 0)
                {
                    colorPrintf(HelpPage);
                    break;
                }

            		
                SocketError errorCode = SocketWrite(&_client.Socket, _socketApplicationData.InputBuffer);

                if (errorCode != SocketNoError)
                {
                    colorPrintf(ErrorSendingFailed, errorCode, SocketErrorToString(errorCode));

                    StateChange(StateClientDisconnecting);
                }

                break;
            }
            case StateServerStartFailed:
            {
                colorPrintf(InputServerStartTryAgain);

                char scanResult = scanf(ScanfInputTag, _socketApplicationData.InputBuffer);
                char answer = _socketApplicationData.InputBuffer[0];

                switch (answer)
                {
                    case 'Y':
                    case 'y':
                    {
                        StateChange(StateServerStarting);
                        break;
                    }
                    case 'N':
                    case 'n':
                    {
                        colorPrintf(StateSelectMode);
                        break;
                    }
                    default:
                    {
                        colorPrintf(ErrorInvalidInput);
                        break;
                    }
                }

                break;
            }

            case StateServerStarting:
            {
                char serverStartSuccesful = ServerStart(&_server, _socketApplicationData.IPMode, _socketApplicationData.Port);

                ServerPrintState(&_server);

                if (serverStartSuccesful)
                {
                    StateChange(StateServerListening);
                }
                else
                {
                    colorPrintf(ErrorServerPortBlocked);
                    StateChange(StateServerStartFailed);
                }

                break;
            }
            case StateServerListening:
            {
                char serverIsRunning = SocketIsCurrentlyUsed(&_server.Socket);

                if (serverIsRunning)
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
                    StateChange(StateSelectMode);
                }

                break;
            }
        }
    }            

    return 0;
}

void OnRemoteServerMessageRecieved(int socketID, char* message)
{
    colorPrintf(ClientMessageRead, message);
}

void OnRemoteClientMessageRecieved(int socketID, char* message)
{
    OSError fileError = OSError_NotImplemented;
    CommandError commandError = CommandNotSet;
    CommandToken commandToken; 
    char messageBuffer[2048];
    char* messageToSend = 0;

    char filePathText[255];
    memset(filePathText, 0, 255);

    CommandTokenInitialize(&commandToken);   
    CommandTokenParse(&commandToken, message);
    commandToken.ClientSocketID = socketID;    


    if (commandToken.Key != 0)
    {
        char* fileExtensionText = ".txt";
        int keyLength = 0;

        keyLength = strlen(commandToken.Key);

        memcpy(filePathText, "Data/", 5);
        memcpy(filePathText + 5, commandToken.Key, keyLength);

        keyLength += 5;

        memcpy(filePathText + keyLength, fileExtensionText, 4);
    } 

    switch (commandToken.CommandType)
    {
        case CommandFileDataPut:
        {
            colorPrintf(IncommingCommandPutMessage, socketID, commandToken.Key, commandToken.Value);                       

            AsyncLockLock(&_socketApplicationData.UserInteractLock);
            commandError = UserWriteInFile(socketID, filePathText, commandToken.Value);
            AsyncLockRelease(&_socketApplicationData.UserInteractLock);

            // Send change to all subscribers
            if(commandError == CommandSuccessful)
            {
                int amoutntOfSubscribers = -1;
                int* subscriberSocketIDs = 0;

                UserGetAllSubscribers(socketID, filePathText, &subscriberSocketIDs, &amoutntOfSubscribers);

                for (unsigned int i = 0; i < amoutntOfSubscribers; i++)
                {
                    int subscriberSocketID = subscriberSocketIDs[0];

                    sprintf
                    (
                        messageBuffer,
                        "[Client:%i] Changed file at %s.\nChange:%s\n",
                        socketID,
                        filePathText,
                        commandToken.Value
                    );

                    ServerSendToClient(&_server, subscriberSocketID, messageBuffer);
                }
            }       

            break;
        }
        case CommandFileDataGet:
        {
            char* data = 0;

            colorPrintf(IncommingCommandGetMessage, socketID, commandToken.Key, commandToken.Value);

            AsyncLockLock(&_socketApplicationData.UserInteractLock);
            commandError = UserReadFromFile(socketID, filePathText, &data);
            AsyncLockRelease(&_socketApplicationData.UserInteractLock);

            if (data != 0)
            {
                ServerSendToClient(&_server, commandToken.ClientSocketID, data);

                free(data);
            }             

            break;
        }
        case CommandFileDelete:
        {
            colorPrintf(IncommingCommandDeleteMessage, socketID, commandToken.Key);

            AsyncLockLock(&_socketApplicationData.UserInteractLock);
            commandError = UserDeleteFile(socketID, filePathText);
            AsyncLockRelease(&_socketApplicationData.UserInteractLock);

            break;
        }
        case CommandFileLock:
        {
            colorPrintf(IncommingCommandLockMessage, socketID, commandToken.Key, commandToken.Value);

            AsyncLockLock(&_socketApplicationData.UserInteractLock);
            commandError = UserLockFile(socketID, filePathText);
            AsyncLockRelease(&_socketApplicationData.UserInteractLock);

            break;
        }
        case CommandFileUnlock:
        {
            colorPrintf(IncommingCommandUnlockFileMessage, socketID, commandToken.Key, commandToken.Value);

            AsyncLockLock(&_socketApplicationData.UserInteractLock);
            commandError = UserUnlockFile(socketID, filePathText);
            AsyncLockRelease(&_socketApplicationData.UserInteractLock);

            break;
        }
        case CommandFileChangeSubscribe:
        {
            colorPrintf(IncommingCommandSubscribeMessage, socketID, commandToken.Key, commandToken.Value);

            AsyncLockLock(&_socketApplicationData.UserInteractLock);
            commandError = UserSubscribeToFile(socketID, filePathText);
            AsyncLockRelease(&_socketApplicationData.UserInteractLock);

            break;
        }
        case CommandOpenProgram:
        {
            colorPrintf(IncommingCommandOpenProgrammMessage, socketID, commandToken.Key, commandToken.Value);
            
            AsyncLockLock(&_socketApplicationData.UserInteractLock);
            commandError = UserOpenProgram(socketID, filePathText, commandToken.Value);
            AsyncLockRelease(&_socketApplicationData.UserInteractLock);

            break;
        }
        case CommandQuit:
        {
            colorPrintf(IncommingCommandQuitMessage, socketID);

            UserUnlockAllFiles(socketID);

            ServerSendToClient(&_server, commandToken.ClientSocketID, "Goodbye!");
            ServerKickClient(&_server, commandToken.ClientSocketID);

            commandError = CommandSuccessfulSilent;

            break;
        }
        case CommandHTTPRequest:
        {
            colorPrintf(IncommingCommandHTTPRequestMessage, socketID);

            char* htmlFile = 0;
            char* htmlFileName = "index.html";

            fileError = FileLoadHTML(htmlFileName, &htmlFile); // <.. has to be ** not *

            if (fileError == FileNoError)
            {
                ServerSendToClient(&_server, commandToken.ClientSocketID, htmlFile);
                free(htmlFile);
            }
            else
            {
                //ServerSendToClient(&_server, commandToken.ClientSocketID, "Error NO");
                printf("[Error] HTML file not found <%s>.\n", htmlFileName);
            }      

            ServerKickClient(&_server, commandToken.ClientSocketID);

            commandError = CommandSuccessfulSilent;

            break;
        }
        case CommandInvalid:
        default:
        {
            colorPrintf(IncommingCommandInvalidMessage, socketID, message);

            commandError = CommandUnsupportedCommand;

            break;
        }
    }

    switch (commandError)
    {
        case CommandSuccessfulSilent:
        case CommandSuccessful:
            messageToSend = "OK: Command sucessful.";
            break;

        case CommandFileDoesNotExist:
            messageToSend = "Error: File not found";
            break;

        case CommandAccessLocked:
            messageToSend = "Error: Access denyed: File is locked";
            break;

        case CommandFileAlreadyExists:
            messageToSend = "Error: File already exists";
            break;

        case CommandUnsupportedCommand:
            messageToSend = "Invalid Command. Check your input. [Maybe try: HELP]";
            break;

        case CommandNotSet:
            messageToSend = "Warning: Invalid state! This should not be possible.";
            break;

        default:
            messageToSend = "Woups: Something went unexpectetly wrong.";
            break;
    }

    if (commandError != CommandSuccessfulSilent)
    {
        ServerSendToClient(&_server, commandToken.ClientSocketID, messageToSend);
    }

    CommandTokenClear(&commandToken);  
}

void OnRemoteServerDisconnect(int socketID)
{
    colorPrintf(ClientServerDisconnected);

    StateChange(StateClientDisconnecting);
}

void OnRemoteClientDisconnect(int socketID)
{
    colorPrintf(ServerClientDisconnected, socketID);

    UserUnlockAllFiles(socketID);
}

void OnRemoteServerConnect(int socketID)
{
    colorPrintf(ClientServerConnection);
}

void OnRemoteClientConnect(int socketID)
{
    char sendWelcomeMessage = _socketApplicationData.Port != 80;

    colorPrintf(ServerClientConnection, socketID);

    if (sendWelcomeMessage)
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

        SocketError socketError = ServerSendToClient(&_server, socketID, welcomeMessage);

        if (socketError != SocketNoError)
        {
            printf("[Server][Error] Couldn't send welcome response. ErrorCode <%i : %s>.\n", socketError, SocketErrorToString(socketError));
        }
    }
}

FileError FileLoadHTML(char* filePath, char** content)
{
    FILE* file = fopen(filePath, "r");
    int fileLength = -1;
    const char* htmlResponseTag = "HTTP/1.0 200 OK\r\n\r\n";
    const int htmlResponselength = 19;

    if (file == NULL)
    {
        return FileDoesNotExist; // File does not exist
    }

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);

    (*content) = calloc(fileLength + htmlResponselength + 1, sizeof(char));

    if (!(*content))
    {
        return 0; // calloc failed
    }

    memcpy((*content), htmlResponseTag, htmlResponselength);
    fread(*content + htmlResponselength, 1, fileLength, file);

    fclose(file);

    return FileNoError;
}

void ServerPrintState(Server* server)
{

    colorPrintf
    (
        "+--------------------+\n"
        "| Socket (Server)    |\n"
        "+--------------------+\n"
        "| ID      : &o%8i &r|\n"
        "| Mode    : &o%8s &r|\n"
        "| Port    : &o%8i &r|\n",
        server->Socket.ID,
        server->Socket.IPMode == IPVersion4 ? "IPv4" : "IPv6",
        server->Socket.Port);

    if (SocketIsCurrentlyUsed(&server->Socket))
        colorPrintf("| State   :   &kONLINE &r|\n");
    else
        colorPrintf("| State   :   &jOFFLINE &r|\n");

    colorPrintf
    (
        "| Clients : &o%8i &r|\n"
        "+--------------------+\n",
        server->NumberOfConnectedClients
    );
}