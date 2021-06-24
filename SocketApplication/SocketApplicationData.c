#include "SocketApplicationData.h"

void SocketApplicationDataInitialize(SocketApplicationData* socketApplicationData)
{
    socketApplicationData->CommunicationMode = ModeInvalid;
    socketApplicationData->IPMode = -1;
    socketApplicationData->IP = 0;
    socketApplicationData->Port = -1;

    socketApplicationData->State = StateNeutralIDLE;

    memset(socketApplicationData->InputBuffer, 0, InputBufferSize);
}