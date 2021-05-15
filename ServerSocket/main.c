#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>

#ifdef linux
// This is stupid... but visual studio code makes me do it.. help!
#include "Server.c" 
#include "IOSocket.c"
#include "ConnectionState.c"
#include "Client.c"
#elif _WIN32
// Normal Include
#include "Server.h"
#include "IOSocket.h"
#include "Client.h"
#endif

// system("@cls||clear");

void ClearBuffer()
{
    char c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void PrintLine()
{
    printf("------------------------\n");
}

int main()
{
    char mode = -1;
    const short defaultPort = 5678u;

    //---[Get operating mode]--------------------------------------------------
    printf
    (
        "+-----------------------+\n"
        "| Select operation mode |\n"
        "+-----------------------+\n"
        "| 0 : Client Mode       |\n"
        "| 1 : Server Mode       |\n"
        "+-----------------------+\n"
    );

    while (1)
    {
        printf("[Input] Mode : ");
        mode = getc(stdin);
        ClearBuffer();

        if (mode == '0' || mode == '1')
        {
            break;
        }

        printf("[Error] Invalid Mode! Please select a valid option.\n");
    }
    //-------------------------------------------------------------------------

    printf("+-----------------------+\n\n");

    switch (mode)
    {
        case '0':
        {
            char quitFlag = 0;
            char command = '-';
            char inputDataBuffer[40] = "127.0.0.1";
            unsigned short port = defaultPort;

            Thread thread;
            Client client;
            ClientInitialize(&client);

            printf("+----------------------------+\n");
            printf("| Connect To Server          |\n");
            printf("+----------------------------+\n");

            while (1)
            {
                printf("[Input] IP  : ");
                scanf("%s", &inputDataBuffer);

                if (IsValidIP(inputDataBuffer))
                {
                    break;
                }
                else
                {
                    printf("[Error] Invalid IP! Please check your input.\n");
                }
            }

            printf("[Info] Port : %i\n", port);
            printf("+----------------------------+\n\n");

            printf
            (
                "+-----------------------------+\n"
                "| Connecting...               |\n"
                "+-----------------------------+\n"
            );

            ClientConnect(&client, &inputDataBuffer[0], port);

            if (client.State == Online)
            {
                printf
                (
                    "[OK] Connection successful!\n"
                    "+-----------------------------+\n\n"
                );
            }
            else
            {
                printf
                (
                    "[Error] Connection Failed!\n"
                    "+-----------------------------+\n\n"
                );
   
                break;
            }

            ThreadCreate(&thread, ThreadClientHandleRead, &client);

            printf
            (
                "+----------------+\n"
                "| Send & Recieve |\n"
                "+----------------+\n"
            );

            while (client.Socket.ID != -1)
            {
                ClearBuffer();
                //fgets(&inputDataBuffer[0], 40, stdin);
                scanf("%s", &inputDataBuffer[0]);

                if (memcmp("q", &inputDataBuffer[0], 1) == 0)
                {
                    printf("[System] Quitting...\n");
                    break;
                }

                SocketErrorCode errorCode = SocketWrite(&client.Socket, &inputDataBuffer[0]);

                switch (errorCode)
                {
                    case NoError:
                    {
                        printf("[You] %s\n", inputDataBuffer);
                        break;
                    }

                    default:
                        break;
                }
            }

            ClientDisconnect(&client);

            break;
        }
        case '1':
        {
            Server server;
            ServerInitialize(&server);
            ServerStart(&server, defaultPort);

            ServerPrint(&server);

            if (server.State != Online)
            {
                printf("[Error] Port seems to be blocked. Server can't be started.\n");
            }

            while (server.State == Online)
            {
                ServerWaitForClient(&server);
                ServerPrint(&server);


            	
            }


        		
            ServerStop(&server);
            break;
        }
    }

    system("pause");

    return 0;
}