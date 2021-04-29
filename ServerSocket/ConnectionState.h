#ifndef ConnectionStateIncluded
#define ConnectionStateIncluded

typedef enum ConnectionState_
{
    Invalid,
    SocketCreationFailure,


    // Client Only
    Disconnected,
    Connected,
    ConnectionFailure,
    ConnectionLost,

    // Server Only
    ListeningFailure,
    BindingFailure,
    SocketOptionFailure,

    Listening,
    Stopped

}ConnectionState;

const char* ConnectionStateToString(ConnectionState state)
{
 switch (state)
    {
  case Invalid:
  return "Invalidf";

    case SocketCreationFailure:
     return "Socket Creation Failure";

    case ListeningFailure:
    return "Listening Failure";

    case BindingFailure:
    return "Binding Failure";

    case Listening:
    return "Listening";

    case Stopped:
     return"Stopped";

     case SocketOptionFailure:
     return "Socketoption Failure";

    default:
    return "Error";
  
    }
}

#endif
