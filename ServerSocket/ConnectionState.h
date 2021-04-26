#ifndef ConnectionStateIncluded
#define ConnectionStateIncluded

typedef enum ConnectionState_
{
    Invalid,
    SocketFailure,

    // Client Only
    Disconnected,
    Connected,
    ConnectionFailure,
    ConnectionLost,

    // Server Only
    Listening,
    Stopped

}ConnectionState;

#endif