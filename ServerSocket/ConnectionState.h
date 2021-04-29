#ifndef ConnectionStateIncluded
#define ConnectionStateIncluded

typedef enum ConnectionState_
{
    Invalid,

    Offline,
    Online,

}ConnectionState;

const char* ConnectionStateToString(ConnectionState state);
#endif