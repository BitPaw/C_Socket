#pragma once

typedef enum ApplicationState_
{
	StateNeutralIDLE,

	StateSelectingDefaultPort,
	StateSelectingSpecificPort,

	StateSelectMode,

	StateClientSelectingIP,
	StateClientConnecting,
	StateClientConnected,

	StateServerSelectingIPVersion,
	StateServerStarting,
	StateServerListening,
	StateServerOffline


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

		case 	StateSelectingDefaultPort:
			return "selecting default port";

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

		case 	StateServerOffline:
			return "server offline";
	}
}