#include "ApplicationState.h"
#include "../SocketSystem/Server.h"
#include "../SocketSystem/Client.h"

unsigned short DefaultPort = 5678u;
const char TagNotSet[] = "NotSet";
const char ConnectionSuccesful[] = "[OK] Connection successful!\n";
const char InvalidModeInput[] = "[Error] Invalid Mode! Please select a valid option.\n";
const char InvalidIPInput[] = "[Error] Invalid IP! Please check your input.\n";
const char NoIPSelected[] = "[Info] No IP selected! Guessing localhost (127.0.0.1).\n";
const char ServerPortBlocked[] = "[Error] Port seems to be blocked. Server can't be started.\n";
const char ASCIIArtLogo[] =
"-----------------------------------------------------------\n"
"         _____      _____            _        _   \n"
"        / ____|    / ____|          | |      | |  \n"
"       | |   _____| (___   ___   ___| | _____| |_ \n"
"       | |  |______\\___ \\ / _ \\ / __| |/ / _ \\ __|\n"
"       | |____     ____) | (_) | (__|   <  __/ |_ \n"
"        \\_____|   |_____/ \\___/ \\___|_|\\_\\___|\\__|\n"
"-----------------------------------------------------------\n";
const char MenuMode[] =
"+---------------------------------------------------------+\n"
"| Select operation mode                                   |\n"
"+---------------------------------------------------------+\n"
"| 0 : Client Mode                                         |\n"
"| 1 : Server Mode                                         |\n"
"+---------------------------------------------------------+\n";
const char BannerFooter[] =
"+---------------------------------------------------------+\n";
const char BannerConnectToServer[] =
"+---------------------------------------------------------+\n"
"| Connecting To Server...                                 |\n"
"+---------------------------------------------------------+\n";
const char BannerSendAndRecieve[] =
"+---------------------------------------------------------+\n"
"| Send & Recieve                                          |\n"
"+---------------------------------------------------------+\n";
const char ServerUnreachable[] =
"[Info]  It seems that the server is unreachable\n"
"        or even offline. Use another IP or try later.\n";
const char BannerClientSelectIPHeader[] =
"+---------------------------------------------------------+\n"
"| Select Server-IP to connect to.                         |\n"
"+---------------------------------------------------------+\n"
"| [Input] IP   : ";

#define ScanfInputTag " %50[^\n]"

// system("@cls||clear");

static Server _server;
static Client _client;

static ApplicationState _currentApplicationState;

int main(int numberOfArguments, char* arguments[]);
static void OnRemoteServerMessageRecieved(int socketID, char* message);
static void OnRemoteClientMessageRecieved(int socketID, char* message);
static void OnRemoteServerDisconnect(int socketID, char disconnectionCause);
static void OnRemoteClientDisconnect(int socketID, char disconnectionCause);
static void OnRemoteServerConnect(int socketID);
static void OnRemoteClientConnect(int socketID);