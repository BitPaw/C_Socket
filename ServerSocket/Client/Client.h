struct Client
{
    unsigned int ID;
    char* IP;
    unsigned int Port;
};

extern void SendCommand(Client* client);
extern void Connect(Client* client, char* ip, int port);
extern void Disconnect(Client* client);