#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../SocketSystem/Server.h"
#include "../SocketSystem/IOSocket.h"
#include "../SocketSystem/Client.h"

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

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


void ClearBuffer()
{
    char c;

    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    char mode = -1;

    //---[Get operating mode]--------------------------------------------------
    printf("%s", MenuMode);

    while (1)
    {
        printf("[Input] Mode : ");
        mode = getc(stdin);
        ClearBuffer();

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
            Client client;
            ClientInitialize(&client);

            printf(BannerConnectToServer);
            printf("[Info]  Port : %i\n", port);

            while (1) // Repeat until connected succesfully.
            {    
                while (1) // Repeat until the entered IP was valid.
                {
                    memset(inputDataBuffer, 0, bufferLength);
                    memcpy(inputDataBuffer, TagNotSet, 6);

                    printf("[Input] IP   : ");
                    fflush(stdout);
                    fflush(stdin);
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

                ClientConnect(&client, &inputDataBuffer[0], port);

                if (client.State == ConnectionOnline)
                {
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

            ThreadCreate(&thread, ThreadClientHandleRead, &client);

            printf(BannerSendAndRecieve);

            while (client.Socket.ID != -1)
            {
                ClearBuffer();
                //fgets(&inputDataBuffer[0], 40, stdin);
                scanf(ScanfInputTag, &inputDataBuffer[0]);

                SocketErrorCode errorCode = SocketWrite(&client.Socket, &inputDataBuffer[0]);

                switch (errorCode)
                {
                    case NoError:
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

            ClientDisconnect(&client);

            break;
        }
        case '1':
        {
            Server server;
            IPVersion ipVersion;
            ServerInitialize(&server);

            while (1)
            {
                char ipInput = -1; 

                printf("Which IP Version shall be used?\nSelect 4 or 6 : ");
                scanf(ScanfInputTag, &ipInput);

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

            ServerStart(&server, ipVersion, DefaultPort);

            ServerPrint(&server);

            if (server.State != ConnectionOnline)
            {
                printf(ServerPortBlocked);
            }

            while (server.State == ConnectionOnline)
            {
                ServerWaitForClient(&server);
            }

            ServerStop(&server);
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