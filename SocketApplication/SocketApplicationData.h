
#ifndef SocketApplicationDataInclude
#define SocketApplicationDataInclude

#include "CommunicationRole.h"
#include "ApplicationState.h"
#include "../SocketSystem/IPVersion.h"
#include "../SocketSystem/AsyncLock.h"

#define InputBufferSize 2048

typedef struct SocketApplicationData_
{
    CommunicationRole CommunicationMode;
    ApplicationState State;
    IPVersion IPMode;

    char* IP;
    unsigned short Port;
    char InputBuffer[InputBufferSize];

    AsyncLock UserInteractLock;

}SocketApplicationData;

void SocketApplicationDataInitialize(SocketApplicationData* SocketApplicationData);

#endif