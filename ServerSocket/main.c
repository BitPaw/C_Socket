#include "Config.h"
#include <stdio.h>

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

int main()
{
#ifdef ClientMode
    char quitFlag = 0;
    char command = '-';
    char ipInputBuffer[40];
    unsigned short port;
    
    Client client;
    ClientInitialize(&client);

    do
    {
        printf("Select option\n");
        printf("");
        printf("");

        scanf("%c", &command);

       switch (command)
       {
            case 'c':
            {
                printf("+------------------+\n");
                printf("[ Connect To Server ]\n")
                printf("| IP : ");
                scanf("%s", &ipInputBuffer);
                printf("| Port : %i", DelaultPort);
                //scanf("%i", &port);
                printf("+------------------+\n");

                ClientConnect(&client, ipInputBuffer, DelaultPort);

                break;
            }

       case 'q':
       {
            ClientDisconnect(&client);
               break;
       }         
       
       default:
       {
           printf("Invalid Command\n");
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
    }

    ServerStop(&server);
#endif       
    return 0;
}
