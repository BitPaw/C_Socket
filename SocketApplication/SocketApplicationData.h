
#ifndef SocketApplicationDataInclude
#define SocketApplicationDataInclude

#include "CommunicationRole.h"
#include "ApplicationState.h"
#include "../SocketSystem/IPVersion.h"
#include "../SocketSystem/AsyncLock.h"

typedef struct SocketApplicationData_
{
    CommunicationRole CommunicationMode;
    ApplicationState State;
    IPVersion IPMode;

    char* IP;
    unsigned short Port;
    char InputBuffer[1024];

    AsyncLock UserInteractLock;

}SocketApplicationData;

void SocketApplicationDataInitialize(SocketApplicationData* SocketApplicationData);

#endif