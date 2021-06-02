#include "ApplicationState.h"
#include "../SocketSystem/Server.h"
#include "../SocketSystem/Client.h"

unsigned short DefaultPort = 5678u;
const char TagNotSet[] = "NotSet";
const char ConnectionSuccesful[] = "[i] Connection successful!\n";

const char InputSpecifyPort[] = "[?] Specify Port : ";

const char InfoNoIPSelected[] = "[Info] No IP selected! Guessing localhost (127.0.0.1).\n";

const char ErrorInvalidModeInput[] = "[x] Invalid Mode! Please select a valid option.\n";
const char ErrorInvalidIPInput[] = "[x] Invalid IP! Please check your input.\n";
const char ErrorServerPortBlocked[] = "[x] Port seems to be blocked. Server can't be started.\n";
const char ErrorInvalidInput[] = "[x] Invalid input.\n";
const char ErrorInvalidPort[] = "[x] Invalid Port. Check your input.\n";
const char ErrorSendingFailed[] = "[x] Sending failed. ErrorCode: <%i:%s>.\n";

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
"+---------------------------------------------------------+\n"
"| [Input] Operation mode : ";
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

const char BannerClientDisconnecting[] =
"+---------------------------------------------------------+\n"
"| Disconnecting...                                        |\n"
"+---------------------------------------------------------+\n";
const char BannerClientSelectIPHeader[] =
"+---------------------------------------------------------+\n"
"| Select Server-IP to connect to.                         |\n"
"+---------------------------------------------------------+\n"
"| [Input] IP   : ";

const char InputUseDefaultPort[] =
"[?] Use default Port <%i>?\n"
"    <y/n> : ";

const char InputIPVersion[] =
"[?] Which IP Version shall be used?\n"
"    Select 4 or 6 : ";

const char InputConnectionTryAgain[] =
"[?] Connection failed.\n"
"    Do you want to try again?\n"
"    <y/n> : ";

const char InputServerStartTryAgain[] =
"[?] Server starting failed.\n"
"    Do you want to try again?\n"
"    <y/n> : ";


#define ScanfInputTag " %50[^\n]"

// system("@cls||clear");

static Server _server;
static Client _client;

static ApplicationState _currentApplicationState;

int main(int numberOfArguments, char* arguments[]);
static void OnRemoteServerMessageRecieved(int socketID, char* message);
static void OnRemoteClientMessageRecieved(int socketID, char* message);
static void OnRemoteServerDisconnect(int socketID);
static void OnRemoteClientDisconnect(int socketID);
static void OnRemoteServerConnect(int socketID);
static void OnRemoteClientConnect(int socketID);