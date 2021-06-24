#ifndef ApplicationStateInclude
#define ApplicationStateInclude

typedef enum ApplicationState_
{
	StateNeutralIDLE,

	StateSelectingDefaultPort,
	StateSelectingSpecificPort,

	StateSelectMode,

	StateClientConnectionFailed,
	StateClientSelectingIP,
	StateClientConnecting,
	StateClientConnected,
	StateClientDisconnecting,

	StateServerSelectingIPVersion,
	StateServerStarting,
	StateServerListening,
	StateServerStartFailed

}ApplicationState;

const char* ApplicationStateToString(ApplicationState applicationState);

#endif