#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "FileError.h"
#include "CommandToken.h"
#include "CommunicationRole.h"
#include "ApplicationState.h"
#include "../ColorPrinter/ColorPrinter.h"
#include "../SocketSystem/OSDefine.h"
#include "../SocketFileManager/FileManager.h"
#include "../List/List.h"

void StateChange(ApplicationState newState)
{
    ApplicationState oldState = _currentApplicationState;
    char hasChanged = newState != oldState;

    if (!hasChanged)
    {
        return;
    }

    _currentApplicationState = newState;

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
    CommunicationRole mode = ModeInvalid;
    IPVersion ipVersion = -1;
    Thread thread;
    char* ip = 0;    
    unsigned short port = -1;
    char inputBuffer[1024];

    printColors = 0;

    _currentApplicationState = StateNeutralIDLE;

    ClientInitialize(&_client);
    ServerInitialize(&_server);

    colorPrintf(ASCIIArtLogo);

    //system("color 0B");

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

            port = atoi(portText);

            if (port == 0)
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
                case 'C':
                case 'c':
                {
                    ip = ipOption;
                    ipVersion = AnalyseIPVersion(ipOption);
                    char isValidIP = IsValidIP(ipOption);

                    mode = ModeClient;

                    if (!isValidIP)
                    {
                        colorPrintf("Invalid IP.");
                        return -1;
                    }

                    StateChange(StateClientConnecting);

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
        switch (_currentApplicationState)
        {
            case StateSelectMode:
            {
                colorPrintf(MenuMode); 

                int result = scanf(ScanfInputTag, inputBuffer);
                char inputCharacter = inputBuffer[0];

                switch (inputCharacter)
                {
                    case '0':
                    {
                        mode = ModeClient;
                        StateChange(StateClientSelectingIP);
                        break;
                    }
                    case '1':
                    {
                        mode = ModeServer;
                        StateChange(StateServerSelectingIPVersion);
                        break;
                    }
                    default:
                    {
                        mode = ModeInvalid;
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
                        colorPrintf(ErrorInvalidIPVersion);
                        break;
                    }
                }

                if (ipVersion != IPVersionInvalid)
                {
                    StateChange(StateServerStarting);
                }
                

                break;
            }
            case StateSelectingSpecificPort:
            {
                colorPrintf(InputSpecifyPort);

                int result = scanf(ScanfInputTag, inputBuffer);
                int convertedNumber = atoi(inputBuffer);              

                if (0 < convertedNumber && convertedNumber < 65535)
                {
                    port = convertedNumber;
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

                result = scanf(ScanfInputTag, inputBuffer);
                useDefaultPort = inputBuffer[0];

                switch (useDefaultPort)
                {
                    case 'Y':
                    case 'y':
                    {
                        port = DefaultPort;
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

                int scanResult = scanf(ScanfInputTag, &inputBuffer);

                char hasUserEnteredIP = memcmp(TagNotSet, &inputBuffer, 6) != 0;

                if (hasUserEnteredIP)
                {
                    char result = IsValidIP(inputBuffer);

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
                    memcpy(inputBuffer, "127.0.0.1", 10);
                    StateChange(StateClientConnecting);
                }                

                break;
            }
            case StateClientConnecting:
            {            
                char connectionSuccesful = ClientConnect(&_client, &inputBuffer[0], port);

                if (connectionSuccesful)
                {
                    _client.Socket.OnConnected = OnRemoteServerConnect;
                    _client.Socket.OnMessage = OnRemoteServerMessageRecieved;
                    _client.Socket.OnDisconnected = OnRemoteServerDisconnect;

                    colorPrintf(ConnectionSuccesful);

                    StateChange(StateClientConnected);

                    ThreadCreate(&thread, SocketReadAsync, &_client.Socket);           
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
                char scanResult = scanf(ScanfInputTag, inputBuffer);

                SocketError errorCode = SocketWrite(&_client.Socket, inputBuffer);

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

                char scanResult = scanf(ScanfInputTag, inputBuffer);
                char answer = inputBuffer[0];

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
                char serverStartSuccesful = ServerStart(&_server, ipVersion, port);

                ServerPrint(&_server);

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
    CommandToken commandToken; 
    char messageBuffer[2048];
    char* messageToSend = 0;

    char filePath[2048];
    int keyLength = 0;

    CommandTokenInitialize(&commandToken);   
    CommandTokenParse(&commandToken, message);
    commandToken.ClientSocketID = socketID;    

    memset(filePath, 0, 2048);

    if (commandToken.Key != 0)
    {
        keyLength = strlen(commandToken.Key);

        memcpy(filePath, "Data/", 5);
        memcpy(filePath + 5, commandToken.Key, keyLength);

        keyLength += 5;

        memcpy(filePath + keyLength, ".txt", 4);

        keyLength += 4;      
    } 

    switch (commandToken.CommandType)
    {
        case CommandFileDataPut:
        {
            colorPrintf(IncommingCommandPutMessage, socketID, commandToken.Key, commandToken.Value);                       

            fileError = OSFileForceWrite(filePath, commandToken.Value, WriteMode_Overwrite);

            break;
        }
        case CommandFileDataGet:
        {
            char* data = 0;

            colorPrintf(IncommingCommandGetMessage, socketID, commandToken.Key, commandToken.Value);          

            fileError = OSFileRead(filePath, &data);

            if (fileError == OSError_NoError)
            {
                ServerSendToClient(&_server, commandToken.ClientSocketID, data);

                free(data);
            }

            break;
        }
        case CommandFileDelete:
        {
            colorPrintf(IncommingCommandDeleteMessage, socketID, commandToken.Key);

            fileError = OSFileDelete(filePath);

            break;
        }
        case CommandFileLock:
        {
            colorPrintf(IncommingCommandLockMessage, socketID, commandToken.Key, commandToken.Value);                    

            memcpy(filePath + keyLength - 3 , "lck", 3 * sizeof(char));

            fileError = OSFileCreate(filePath);

            break;
        }
        case CommandFileUnlock:
        {
            colorPrintf(IncommingCommandUnlockFileMessage, socketID, commandToken.Key, commandToken.Value);

            memcpy(filePath + keyLength - 3, "lck", 3 * sizeof(char));

            fileError = OSFileDelete(filePath);

            break;
        }
        case CommandFileChangePublish:
        {
            colorPrintf(IncommingCommandPublishMessage, socketID, commandToken.Key, commandToken.Value);

            // ToDo: sent all changes to all subsribers

            break;
        }
        case CommandFileChangeSubscribe:
        {
            colorPrintf(IncommingCommandSubscribeMessage, socketID, commandToken.Key, commandToken.Value);

            // ToDo: register to a file

            break;
        }
        case CommandOpenProgram:
        {
            colorPrintf(IncommingCommandOpenProgrammMessage, socketID, commandToken.Key, commandToken.Value);

            // ToDo: Open a programm somehow, sent that result to the user.           

            break;
        }
        case CommandQuit:
        {
            colorPrintf(IncommingCommandQuitMessage, socketID);

            // ToDo: unlock files that the user has locket

            ServerSendToClient(&_server, commandToken.ClientSocketID, "Goodbye!");
            ServerKickClient(&_server, commandToken.ClientSocketID);

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

            break;
        }
        case CommandInvalid:
        default:
        {
            colorPrintf(IncommingCommandInvalidMessage, socketID, message);

            fileError = OSError_NotImplemented;

            break;
        }
    }

    switch (fileError)
    {
        case OSError_NoError:
            messageToSend = "OK: Command sucessful.";
            break;

        case OSError_DirectoryOrFileNotFound:
            messageToSend = "Error: File not found";
            break;

        case OSError_FileIsCurrentlyInUse:
            messageToSend = "Error: File is locked";
            break;

        case OSError_FileAlreadyExists:
            messageToSend = "Error: File already exists";
            break;

        case OSError_NotImplemented:
            messageToSend = "Invalid Command.Check your input.";
            break;

        default:
            messageToSend = "Woups: Something went unexpectetly wrong.";
            break;
    }

    ServerSendToClient(&_server, commandToken.ClientSocketID, messageToSend);

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
}

void OnRemoteServerConnect(int socketID)
{
    colorPrintf(ClientServerConnection);
}

void OnRemoteClientConnect(int socketID)
{
    colorPrintf(ServerClientConnection, socketID);

    // maybe send if port is not 80?

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

    *content = calloc(fileLength + htmlResponseTag + 1, sizeof(char));

    if (!*content)
    {
        return 0; // calloc failed
    }

    memcpy(*content, htmlResponseTag, htmlResponselength);
    fread(*content + htmlResponselength, 1, fileLength, file);

    fclose(file);

    return FileNoError;
}