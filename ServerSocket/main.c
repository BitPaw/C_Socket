#include "Config.h"
#include "Server.c"
#include "Client.c"
#include <stdio.h>

int main()
{
#ifdef ClientMode
    char quitFlag = 0;
    char command = '-';
    char ipInputBuffer[40];
    unsigned short port;

    printf("[Socket: Client Mode]");
    
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
    printf("[Socket: Server Mode]\n");

    Server server;
    ServerInitialize(&server);
    ServerStart(&server, DelaultPort);

    ServerPrint(&server);

    while(1)
    {
        ServerWaitForClient(&server);        
    }

    ServerStop(&server);
#endif       
    return 0;
}
