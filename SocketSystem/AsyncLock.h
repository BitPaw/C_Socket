#ifndef AsyncLockIncluded
#define AsyncLockIncluded

#include "OSDefine.h"

#ifdef OSUnix
#include <semaphore.h>
#elif defined(OSWindows)
#include <Windows.h>
#include <process.h>
#endif 

typedef struct AsyncLock_
{
#ifdef OSUnix
	sem_t HandleID;
#elif defined(OSWindows)
	HANDLE HandleID;
#endif

}AsyncLock;

int AsyncLockCreate(AsyncLock* asyncLock);
int AsyncLockDelete(AsyncLock* asyncLock);
int AsyncLockLock(AsyncLock* asyncLock);
int AsyncLockRelease(AsyncLock* asyncLock);

#endif