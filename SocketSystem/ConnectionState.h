#ifndef ConnectionStateIncluded
#define ConnectionStateIncluded

typedef enum ConnectionState_
{
    ConnectionInvalid,

    ConnectionOffline,
    ConnectionOnline,

}ConnectionState;

const char* ConnectionStateToString(ConnectionState state);
#endif