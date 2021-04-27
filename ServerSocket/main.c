#include "Config.h"
#include "Server.c"
#include "Client.c"
#include <stdio.h>

int main()
{
#ifdef ClientMode
    printf("[Socket: Client Mode]");

    // Do Client Stuff
#endif

#ifdef ServerMode
    printf("[Socket: Server Mode]\n");

    Server server;
    ServerInitialize(&server);
    ServerStart(&server, 8125);

    ServerPrint(&server);

    while(1)
    {
        ServerWaitForClient(&server);        
    }

    ServerStop(&server);

#endif       


    //-----[ T E S T ]-------------------------
    #if 0
    Server server;
    ServerInitialize(&server);
    ServerStart(&server, DelaultPort);


    Client client;
    ClientInitialize(&client);
    ClientConnect(&client, "127.0.0.1", DelaultPort);

    ClientDisconnect(&client);
    ServerStop(&server);
    #endif
    //-----------------------------------------

    return 0;
}