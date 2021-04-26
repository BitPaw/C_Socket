//-----------------------------------------------------------------------------
#ifdef linux
#include <sys/types.h> // <-- Can't find them?!
#include <sys/socket.h>
#endif

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>
#include <winsock.h>
//#include <WinSock2.h>
#endif
//-----------------------------------------------------------------------------
#define DelaultPort 5678U 
//-----------------------------------------------------------------------------
#if 0 // <--- Change this 
#define ClientMode
#else
#define ServerMode
#endif
//-----------------------------------------------------------------------------