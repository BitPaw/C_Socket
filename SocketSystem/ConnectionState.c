#include "ConnectionState.h"

const char* ConnectionStateToString(ConnectionState state)
{
    switch (state)
    {
        default:
        case ConnectionInvalid:
            return "Invalid";

        case ConnectionOnline:
            return "Online";

        case ConnectionOffline:
            return "Offline";
    }
}