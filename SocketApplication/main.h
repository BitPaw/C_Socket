#ifndef MainInclude
#define MainInclude

#include "FileError.h"
#include "../SocketSystem/Client.h"
#include "../SocketSystem/Server.h"
#include "../SocketSystem/Thread.h"
#include "SocketApplicationData.h"

unsigned short DefaultPort = 5678u;
const char TagNotSet[] = "NotSet";
const char ConnectionSuccesful[] = "| &i[&li&i]&r Connection &ksuccessful&r!\n";

const char InputSpecifyPort[] = "| &i[&o>&i]&r Specify Port : ";

const char InfoNoIPSelected[] = "| &i[&oi&i]&r No IP selected! Guessing localhost (127.0.0.1).\n";

const char ErrorInvalidModeInput[] = "| &i[&jx&i]&r Invalid Mode! Please select a valid option.\n";
const char ErrorInvalidIPInput[] = "| &i[&jx&i]&r Invalid IP! Please check your input.\n";
const char ErrorServerPortBlocked[] = "| &i[&jx&i]&r Port seems to be blocked. Server can't be started.\n";
const char ErrorInvalidIPVersion[] = "| &i[&jx&i]&r Invalid IP Version! Check your input.\n";
const char ErrorInvalidInput[] = "| &i[&jx&i]&r Invalid input.\n";
const char ErrorInvalidPort[] = "| &i[&jx&i]&r Invalid Port. Check your input.\n";
const char ErrorSendingFailed[] = "| &i[&jx&i]&r Sending failed. ErrorCode: <%i:%s>.\n";

const char IncommingCommandPutMessage[] = "| &i[&o#&i][&oClient:%i&i] &rPUT KEY:%s Value:%s\n";
const char IncommingCommandGetMessage[] = "| &i[&o#&i][&oClient:%i&i] &rGET KEY:%s Value:%s\n";
const char IncommingCommandDeleteMessage[] = "| &i[&o#&i][&oClient:%i&i] &rDELETE KEY:%s\n";
const char IncommingCommandLockMessage[] = "| &i[&o#&i][&oClient:%i&i] &rLockFile KEY:%s Value:%s\n";
const char IncommingCommandUnlockFileMessage[] = "| &i[&o#&i][&oClient:%i&i] &rUnlockFile KEY:%s Value:%s\n";
const char IncommingCommandPublishMessage[] = "| &i[&o#&i][&oClient:%i&i] &rPublish KEY:%s Value:%s\n";
const char IncommingCommandSubscribeMessage[] = "| &i[&o#&i][&oClient:%i&i] &rSubscribe KEY:%s Value:%s\n";
const char IncommingCommandOpenProgrammMessage[] = "| &i[&o#&i][&oClient:%i&i] &rOpenProgramm KEY:%s Value:%s\n";
const char IncommingCommandQuitMessage[] = "| &i[&o#&i][&oClient:%i&i] &rQUIT\n";
const char IncommingCommandHTTPRequestMessage[] = "| &i[&o#&i][&oClient:%i&i] &rHTTP Request\n";
const char IncommingCommandInvalidMessage[] = "| &i[&o#&i][&oClient:%i&i] &rInvalid command. Message:%s\n";

const char ASCIIArtLogo[] =
"+---------------------------------------------------------+\n"
"|   &o      _____      &n  _____            _        _       &r |\n"
"|   &o     / ____|      &n/ ____|          | |      | |      &r |\n"
"|   &o    | | &p    _____&n| (___   ___   ___| | _____| |_     &r |\n"
"|   &o    | | &p   |______&n\\___ \\ / _ \\ / __| |/ / _ \\ __|    &r |\n"
"|   &o    | |___        &n____) | (_) | (__|   <  __/ |_     &r |\n"
"|   &o     \\_____|     &n|_____/ \\___/ \\___|_|\\_\\___|\\__|    &r |\n";


const char BannerGeneral[] =
"++---------------------------------------------------------+\n\n"
"+---------------------------------------------------------+\n"
"| %-55s |\n"
"+---------------------------------------------------------+\n";

const char MenuMode[] =
"| &l0 &r: &lClient Mode&r                                         |\n"
"| &l1 &r: &lServer Mode&r                                         |\n"
"+---------------------------------------------------------+\n"
"| &i[&o>&i]&r Operation mode : ";

const char ServerUnreachable[] =
"| &i[&oi&i]&r  It seems that the server is &junreachable&r\n"
"|         or even offline. Use another IP or try later.\n";

const char BannerClientSelectIPHeader[] =
"| &i[&o>&i]&r IP   : ";

const char InputUseDefaultPort[] =
"| &i[&o?&r&i]&r Use default Port <&l%i&r>?\n";

const char InputIPVersion[] =
"| &i[&o?&i]&r Which IP Version shall be used?\n"
"| &i[&o>&i]&r Select &l4 &ror &l6 &r: ";

const char InputConnectionTryAgain[] =
"| &i[&o?&i]&r Connection &jfailed.&r\n";

const char InputTryAgain[] =
"|     Do you want to try again?\n";

const char InputYesNo[] =
"| &i[&o>&i] <&2y&i/&1n&i> : ";

const char InputServerStartTryAgain[] =
"| &i[&o?&i]&r Server starting failed.\n";

const char ClientMessageRead[] = "| &i[&lServer&i]&r %s\n";
const char ClientServerDisconnected[] = "| &i[&r!&i][&lServer&i]&r Server closed connection.\n";
const char ClientServerConnection[] = "| &i[&ri&i][&lServer&i]&r Connected succesful!\n";

const char ServerClientDisconnected[] = "| &i[&j-&i][&oClient:%i&i]&r Disconnected.\n";
const char ServerClientConnection[] = "| &i[&k+&i][&oClient:%i&i]&r New client connected.\n";

const char HelpPage[] =
"++---------------------------------------------------------+\n"
"| Help Page - Commands                                    |\n"
"+---------------------------------------------------------+\n"
"| Note: 1) Commands tags have to be in caps.              |\n"
"|       2) The filename is without extension.             |\n"
"+--------------------------------+------------------------+\n"
"| - GET <FileName>               |                  (Read)|\n"
"| - PUT <FileName> <FileContent> |                 (Write)|\n"
"| - DEL <FileName>               |                (Delete)|\n"
"| - BEG <FileName>               |  (Lock file for others)|\n"
"| - SUB <FileName>               |      (Notify on change)|\n"
"| - END <FileName>               |           (Unlock file)|\n"
"| - OP  <FileName> <ProgrammName>|(Call external programm)|\n"
"| - QUIT                         |      (Quit from server)|\n"
"+---------------------------------------------------------+\n";

#define ScanfInputTag " %50[^\n]"

// system("@cls||clear");

SocketApplicationData _socketApplicationData;
static Server _server;
static Client _client;
static Thread _clientThread;

int main(int numberOfArguments, char* arguments[]);
static void OnRemoteServerMessageRecieved(int socketID, char* message);
static void OnRemoteClientMessageRecieved(int socketID, char* message);
static void OnRemoteServerDisconnect(int socketID);
static void OnRemoteClientDisconnect(int socketID);
static void OnRemoteServerConnect(int socketID);
static void OnRemoteClientConnect(int socketID);
static FileError FileLoadHTML(char* filePath, char** content);
static void ServerPrintState(Server* server);

#endif