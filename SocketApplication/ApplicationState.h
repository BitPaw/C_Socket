#pragma once

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

const char* ApplicationStateToString(ApplicationState applicationState)
{
	switch (applicationState)
	{
		default:
		case StateNeutralIDLE:
			return "neutral IDLE";

		case StateServerStarting:
			return "server starting";

		case StateClientDisconnecting:
			return "disconnecting";

		case 	StateSelectingDefaultPort:
			return "selecting default port";

		case StateClientConnectionFailed:
			return "connection failed";

		case 	StateSelectingSpecificPort:
			return "selecting specific port";

		case 	StateSelectMode:
			return "select mode";

		case 	StateClientSelectingIP:
			return "client selecting ip";

		case 	StateClientConnecting:
			return "Client connecting";

		case 	StateClientConnected:
			return "client connected";

		case 	StateServerSelectingIPVersion:
			return "server selecting IP version";

		case 	StateServerListening:
			return "server listening";

		case 	StateServerStartFailed:
			return "server start failed";
	}
}