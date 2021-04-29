#pragma once

typedef enum SocketErrorCode_
{
	NoError,

	SocketCreationFailure,
	SocketOptionFailure,
	SocketBindingFailure,
	SocketListeningFailure,


	//---[ Windows Only (WindowsSocketAgent) ]-------

	SubSystemNotReady,
	VersionNotSupported,
	BlockedByOtherOperation,
	LimitReached,
	InvalidParameter

	//----------------------------------------


}SocketErrorCode;