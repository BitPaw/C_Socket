#include "ConnectionState.h"

const char* ConnectionStateToString(ConnectionState state)
{
    switch (state)
    {
        default:
        case Invalid:
            return "Invalid";

        case Online:
            return "Online";

        case Offline:
            return "Offline";
    }
}