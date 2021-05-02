#pragma once

typedef enum SocketErrorCode_
{
	NoError,

	SocketCreationFailure,
	SocketOptionFailure,
	SocketBindingFailure,
	SocketListeningFailure,

	SocketSendFailure,
	SocketRecieveFailure,

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