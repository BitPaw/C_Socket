#include "Config.h"
#include "Server.h"
#include "Client.h"
#include <stdio.h>

int main()
{
#ifdef ClientMode
    printf("[Socket: Client Mode]");

    // Do Client Stuff
#endif

#ifdef ServerMode
    printf("[Socket: Server Mode]");

    // Do Server Stuff
#endif       


    //-----[ T E S T ]-------------------------
    Server server;
    ServerInitialize(&server);
    ServerStart(&server, DelaultPort);


    Client client;
    ClientInitialize(&client);
    ClientConnect(&client, "127.0.0.1", DelaultPort);


    ClientDisconnect(&client);
    ServerStop(&server);
    //-----------------------------------------

    return 0;
}