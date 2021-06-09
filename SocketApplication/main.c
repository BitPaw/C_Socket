#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "FileError.h"
#include "CommandToken.h"
#include "CommunicationRole.h"
#include "ApplicationState.h"
#include "../SocketSystem/OSDefine.h"



char DoesFileExist(char* path)
{
    FILE* file = fopen(path, "r");
    char doesDileExist = file != NULL;

    fclose(file);

    return doesDileExist;
}

FileError FileDelete(char* filePath)
{
    int removeResult = remove(filePath);

    switch (removeResult)
    {
        default:
        case 0:
            return FileNoError;
    }
}

FileError FileWriteToEnd(char* filePath, char* message)
{
    FILE* file = 0;
    int contentLength = 0;

    if (!filePath)
        return FileEmptyFileName;

    if (!message)
        return FileEmptyMessage;

    file = fopen(filePath, "w");

    if (!file)
        return FileDoesNotExist;

    contentLength = strnlen(message, 2048);

    fseek(file, 0, SEEK_END); // Move to file end

    fwrite(message, sizeof(char), contentLength, file);

    fclose(file);

    return FileNoError;
}

FileError FileLoad(char* filePath, char* content)
{
    int fileLength = -1;
    FILE* file = 0;

    if (!filePath)
        return FileEmptyFileName;

    if (!content)
        return FileEmptyMessage;

    file = fopen(filePath, "r");

    if (!file)
        return FileDoesNotExist;


    fseek(file, 0, SEEK_END); // Jump to end of file
    fileLength = ftell(file); // Get length of file
    fseek(file, 0, SEEK_SET); // jump to beginning

    content = calloc(fileLength + 1, sizeof(char));

    if (!content)
    {
        fclose(file);
        return FileNotEnoghMemory;
    }

    int readSize = fread(content, sizeof(char), fileLength, file);

    int closeResult = fclose(file);

    return FileNoError;
}

FileError FileLoadHTML(char* filePath, char* content)
{
    FILE* file = fopen(filePath, "r");
    int fileLength = -1;
    const char* htmlResponseTag = "HTTP/1.0 200 OK\r\n\r\n";
    const int htmlResponselength = 19;

    if (file == NULL)
    {
        return 0; // File does not exist
    }

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);

    content = calloc(fileLength + htmlResponseTag + 1, sizeof(char));

    if (!content)
    {
        return 0; // calloc failed
    }

    memcpy(content, htmlResponseTag, htmlResponselength);
    fread(content + htmlResponselength, 1, fileLength, file);

    fclose(file);

    return FileNoError;
}
















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

    printColors = 1;

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
                        printf(ErrorInvalidIPVersion);
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
    FileError fileError = FileErrorNotSet;
    CommandToken commandToken; 
    char messageBuffer[2048];
    char* messageToSend = 0;

    CommandTokenInitialize(&commandToken);   
    CommandTokenParse(&commandToken, message);

    commandToken.ClientSocketID = socketID;    

    switch (commandToken.CommandType)
    {
        case CommandFileDataPut:
        {
            colorPrintf(IncommingCommandPutMessage, socketID, commandToken.Key, commandToken.Value);                       

            fileError = FileWriteToEnd(commandToken.Key, commandToken.Value);

            break;
        }
        case CommandFileDataGet:
        {
            colorPrintf(IncommingCommandGetMessage, socketID, commandToken.Key, commandToken.Value);

            fileError = FileLoad(commandToken.Key, messageToSend);             

            break;
        }
        case CommandFileDelete:
        {
            colorPrintf(IncommingCommandDeleteMessage, socketID, commandToken.Key);

            fileError = FileDelete(commandToken.Key);

            break;
        }
        case CommandFileLock:
        {
            colorPrintf(IncommingCommandLockMessage, socketID, commandToken.Key, commandToken.Value);

           // fileError = FileLock(commandToken.Key);

            break;
        }
        case CommandFileUnlock:
        {
            colorPrintf(IncommingCommandUnlockFileMessage, socketID, commandToken.Key, commandToken.Value);

            //fileError = FileUnlock(commandToken.Key);

            break;
        }
        case CommandFileChangePublish:
        {
            colorPrintf(IncommingCommandPublishMessage, socketID, commandToken.Key, commandToken.Value);

           // fileError = FileChangePublish(commandToken.Key);

            break;
        }
        case CommandFileChangeSubscribe:
        {
            colorPrintf(IncommingCommandSubscribeMessage, socketID, commandToken.Key, commandToken.Value);

            //fileError = FileChangeSubscribe(commandToken.Key);

            break;
        }
        case CommandOpenProgram:
        {
            colorPrintf(IncommingCommandOpenProgrammMessage, socketID, commandToken.Key, commandToken.Value);

           // fileError = ProgramOpen(commandToken.Key);

            break;
        }
        case CommandQuit:
        {
            colorPrintf(IncommingCommandQuitMessage, socketID);

            //ApplicationQuit();

            break;
        }
        case CommandHTTPRequest:
        {
            colorPrintf(IncommingCommandHTTPRequestMessage, socketID);

            char* htmlFile = 0;

            fileError = FileLoadHTML(commandToken.Key, htmlFile); // <.. has to be ** not *

            if (fileError == FileNoError)
            {
                ServerSendToClient(&_server, commandToken.ClientSocketID, htmlFile);
                free(htmlFile);
            }
            else
            {
                ServerSendToClient(&_server, commandToken.ClientSocketID, "Error NO");
            }                   

            break;
        }
        case CommandInvalid:
        default:
        {
            colorPrintf(IncommingCommandInvalidMessage, socketID, message);

            ServerSendToClient(&_server, commandToken.ClientSocketID, "Invalid Command.Check your input.");

            break;
        }
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
}

void OnRemoteServerConnect(int socketID)
{
    colorPrintf(ClientServerConnection);
}

void OnRemoteClientConnect(int socketID)
{
    colorPrintf(ServerClientConnection, socketID);

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