#include "ApplicationState.h"

const char* ApplicationStateToString(ApplicationState applicationState)
{
	switch (applicationState)
	{
		default:
		case StateNeutralIDLE:
			return "neutral IDLE";

		case StateServerStarting:
			return "Server Starting...";

		case StateClientDisconnecting:
			return "Disconnecting...";

		case 	StateSelectingDefaultPort:
			return "Selecting Default Port";

		case StateClientConnectionFailed:
			return "Connection failed";

		case 	StateSelectingSpecificPort:
			return "Selecting specific port";

		case 	StateSelectMode:
			return "Select operation mode";

		case 	StateClientSelectingIP:
			return "Client selecting IP";

		case 	StateClientConnecting:
			return "Client Connecting...";

		case 	StateClientConnected:
			return "Client Connected";

		case 	StateServerSelectingIPVersion:
			return "Server selecting IP version";

		case 	StateServerListening:
			return "Server listening";

		case 	StateServerStartFailed:
			return "Server start failed";
	}
}