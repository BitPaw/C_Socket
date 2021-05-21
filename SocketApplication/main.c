#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../SocketSystem/Server.h"
#include "../SocketSystem/IOSocket.h"
#include "../SocketSystem/Client.h"


#define ScanfInputTag "%30[^\n]"

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
            char inputDataBuffer[40];
            unsigned short port = DefaultPort;

            Thread thread;
            Client client;
            ClientInitialize(&client);

            printf(BannerConnectToServer);
            printf("[Info]  Port : %i\n", port);

            while (1)
            {
                memset(inputDataBuffer, 0, 40);
                memcpy(inputDataBuffer, TagNotSet, 6);

                printf("[Input] IP   : ");
                //ClearBuffer();
                scanf(ScanfInputTag, &inputDataBuffer);

                char hasUserEnteredIP = memcmp(TagNotSet, &inputDataBuffer, 6) != 0;

                if (hasUserEnteredIP)
                {
                    //TODO: buggy with "192.168.178.42" please fix
                    char result = IsValidIPv4(inputDataBuffer);

                    if (result == 0)
                    {
                        // IP OK     
                        break;
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

            ClientConnect(&client,&inputDataBuffer[0], port);

            if (client.State == ConnectionOnline)
            {
                printf(ConnectionSuccesful);
            }
            else
            {
                printf(ConnectionFailed);
                printf(BannerFooter);
                break;
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
            ServerInitialize(&server);
            ServerStart(&server, DefaultPort);

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




#ifdef _WIN32
    system("pause");
#else
    printf("Terminated\n");
#endif


    return 0;
}