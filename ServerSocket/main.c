#include "Config.h"
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

void ClearBuffer()
{
    char c;

    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
#ifdef ClientMode
    char quitFlag = 0;
    char command = '-';
    char inputDataBuffer[40] = "127.0.0.1";
    unsigned short port;
    
    Client client;
    ClientInitialize(&client);

    do
    {
        printf
        (
            "+---------------+\n"
            "| Select option |\n"
            "| C - Connect   |\n"
            "| Q - Quit      |\n"
            "| R - Read Data |\n"
            "| S - Send Data |\n"
            "+---------------+\n\n"
        );
     
        ClearBuffer();
        printf("  > ");
        scanf(" %c", &command);

       switch (command)
       {
           case 'C' :
            case 'c':
            {
                printf("+-------------------+\n");
                printf("| Connect To Server |\n");
                printf("| IP   : %s\n", &inputDataBuffer[0]);           
                //scanf("%s", &inputDataBuffer);
                printf("| Port : %i", DelaultPort);
                printf("\n");
                //scanf("%i", &port);
                printf("+-------------------+\n");

                ClientConnect(&client, &inputDataBuffer[0], DelaultPort);

                if (client.State == Online)
                {
                    printf("[OK] Connection sucessful!\n");
                }
                else
                {
                    printf("[Error] Connection Failed!\n");
                    // Read ErrorCode
                }

                break;
            }

            case 'r':
            case 'R':
            {
                SocketErrorCode errorCode = SocketRead(&client.Socket);

                if (errorCode == NoError)
                {
                    printf("[Client] %s\n", &client.Socket.Message[0]);
                }
                else
                {
                    printf("[Error] Failed to read message\n");
                }

                break;
            }

            case 's':
            case 'S':
            {
                printf("| Message : ");      
                ClearBuffer();
                fgets(&inputDataBuffer[0], 40, stdin);                

                SocketErrorCode errorCode = SocketWrite(&client.Socket, &inputDataBuffer[0]);

                break;
            }


       case 'q':
       {
            ClientDisconnect(&client);
            quitFlag = 1;
               break;
       }         
       
       default:
       {
           printf("[Error] Invalid Command\n");
            break;
       }
      
       }
    } 
    while (!quitFlag); 

ClientDisconnect(&client);

#endif

#ifdef ServerMode
    Server server;
    ServerInitialize(&server);
    ServerStart(&server, DelaultPort);

  
    ServerPrint(&server);

    while(server.State == Online)
    {              
        ServerWaitForClient(&server);      
        //system("@cls||clear");
        ServerPrint(&server);
    }

    ServerStop(&server);
#endif       
    return 0;
}
