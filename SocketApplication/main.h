#include "ApplicationState.h"
#include "../SocketSystem/Server.h"
#include "../SocketSystem/Client.h"

unsigned short DefaultPort = 5678u;
const char TagNotSet[] = "NotSet";
const char ConnectionSuccesful[] = "[i] Connection successful!\n";

const char InputSpecifyPort[] = "[?] Specify Port : ";

const char InfoNoIPSelected[] = "[Info] No IP selected! Guessing localhost (127.0.0.1).\n";

const char ErrorInvalidModeInput[] = "[x] Invalid Mode! Please select a valid option.\n";
const char ErrorInvalidIPInput[] = "[x]\x1b[91m Invalid IP! Please check your input.\x1b[0m\n";
const char ErrorServerPortBlocked[] = "[x]\x1b[91m Port seems to be blocked. Server can't be started.\x1b[0m\n";
const char ErrorInvalidIPVersion[] = "Invalid IP Version! Check your input.\n";
const char ErrorInvalidInput[] = "[x] Invalid input.\n";
const char ErrorInvalidPort[] = "[x]\x1b[91m Invalid Port. Check your input.\x1b[0m\n";
const char ErrorSendingFailed[] = "[x]\x1b[91m Sending failed. ErrorCode: <%i:%s>.\x1b[0m\n";

const char IncommingCommandPutMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] PUT KEY:%s Value:%s\n";
const char IncommingCommandGetMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] GET KEY:%s Value:%s\n";
const char IncommingCommandDeleteMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] DELETE KEY:%s\n";
const char IncommingCommandLockMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] LockFile KEY:%s Value:%s\n";
const char IncommingCommandUnlockFileMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] UnlockFile KEY:%s Value:%s\n";
const char IncommingCommandPublishMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] Publish KEY:%s Value:%s\n";
const char IncommingCommandSubscribeMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] Subscribe KEY:%s Value:%s\n";
const char IncommingCommandOpenProgrammMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] OpenProgramm KEY:%s Value:%s\n";
const char IncommingCommandQuitMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] QUIT\n";
const char IncommingCommandHTTPRequestMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] HTTP Request\n";
const char IncommingCommandInvalidMessage[] = "[\x1b[96m#\x1b[0m][Client:%i] Invalid command. Message:\x1b[97m%s\x1b[0m\n";

const char ASCIIArtLogo[] =
"+---------------------------------------------------------+\n"
"|   \x1b[96m      _____ \x1b[0m   \x1b[95m  _____            _        _         \x1b[0m |\n"
"|   \x1b[96m     / ____|\x1b[0m    \x1b[95m/ ____|          | |      | |        \x1b[0m |\n"
"|   \x1b[96m    | | \x1b[0m  _____\x1b[95m| (___   ___   ___| | _____| |_       \x1b[0m |\n"
"|   \x1b[96m    | | \x1b[0m |______\x1b[95m\\___ \\ / _ \\ / __| |/ / _ \\ __|      \x1b[0m |\n"
"|   \x1b[96m    | |____  \x1b[0m   \x1b[95m____) | (_) | (__|   <  __/ |_       \x1b[0m |\n"
"|   \x1b[96m     \\_____| \x1b[0m  \x1b[95m|_____/ \\___/ \\___|_|\\_\\___|\\__|      \x1b[0m |\n";


const char BannerFootter[] =
"+---------------------------------------------------------+\n";

const char BannerGeneral[] =
"+---------------------------------------------------------+\n\n"
"+---------------------------------------------------------+\n"
"| %-55s |\n"
"+---------------------------------------------------------+\n";

const char MenuMode[] =
"| 0 : Client Mode                                         |\n"
"| 1 : Server Mode                                         |\n"
"+---------------------------------------------------------+\n"
"| [Input] Operation mode : ";
const char ServerUnreachable[] =
"| [Info]  It seems that the server is unreachable\n"
"|         or even offline. Use another IP or try later.\n";

const char BannerClientSelectIPHeader[] =
"| [Input] IP   : ";

const char InputUseDefaultPort[] =
"| [?] Use default Port <%i>?\n"
"|     <y/n> : ";

const char InputIPVersion[] =
"| [?] Which IP Version shall be used?\n"
"|     Select 4 or 6 : ";

const char InputConnectionTryAgain[] =
"| \x1b[91m[?] Connection failed.\x1b[0m\n"
"|     Do you want to try again?\n"
"|     <y/n> : ";

const char InputServerStartTryAgain[] =
"| \x1b[91m[?] Server starting failed.\x1b[0m\n"
"|     Do you want to try again?\n"
"|     <y/n> : ";

const char ClientMessageRead[] = "[Server] %s\n";
const char ClientServerDisconnected[] = "[!][Server] Server closed connection.\n";

const char ServerClientDisconnected[] = "[\x1b[91m-\x1b[0m][Client:%i] Disconnected.\n";
const char ServerClientConnection[] = "[\x1b[92m+\x1b[0m][Client:%i] New client connected.\n";

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