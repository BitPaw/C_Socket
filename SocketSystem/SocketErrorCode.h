#pragma once

typedef enum SocketErrorCode_
{
	NoError,

	SocketInavlidAdressFamily,
	SocketCreationFailure,
	SocketOptionFailure,
	SocketBindingFailure,
	SocketListeningFailure,

	SocketSendFailure,
	SocketRecieveFailure,
	SocketRecieveConnectionClosed,

	// Client
	SocketConnectionFailure,



	//---[ Windows Only (WindowsSocketAgent) ]-------

	SubSystemNotReady,
	VersionNotSupported,
	BlockedByOtherOperation,
	LimitReached,
	InvalidParameter

	//----------------------------------------


}SocketErrorCode;