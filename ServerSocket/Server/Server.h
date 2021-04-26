typedef struct Server_
{
    /* data */
}Server;

extern void ServerInit(Server* server);
extern void ServerOpen(Server* server, int port);
extern void ServerClose(Server* server);
