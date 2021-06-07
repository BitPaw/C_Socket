#include <sys/semaphore.h>
#include "AsyncLock.h"

int AsyncLockCreate(AsyncLock* asyncLock)
{
	int createResult = -1;

#ifdef OSUnix
	int sharedPointer = 0;
	unsigned int value = 1;

	createResult = sem_init(&asyncLock->HandleID, sharedPointer, value);
#elif defined(OSWindows)
	LPSECURITY_ATTRIBUTES lpSemaphoreAttributes = 0;
	LONG lInitialCount = 1;
	LONG lMaximumCount = 1;
	LPCWSTR lpName = 0;

	createResult = 0;
	asyncLock->HandleID = CreateSemaphore(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
#endif 

	return createResult;
}

int AsyncLockDelete(AsyncLock* asyncLock)
{
	int closingResult = -1;

#ifdef OSUnix
	closingResult = sem_destroy(&asyncLock->HandleID);
#elif defined(OSWindows)
	closingResult = CloseHandle(asyncLock->HandleID);
#endif 

	return closingResult;
}

int AsyncLockLock(AsyncLock* asyncLock)
{
	int lockResult = -1;

#ifdef OSUnix
	lockResult = sem_wait(&asyncLock->HandleID);
#elif defined(OSWindows)
	lockResult = WaitForSingleObject(asyncLock->HandleID, INFINITE);
#endif 

	return lockResult;	
}

int AsyncLockRelease(AsyncLock* asyncLock)
{
	int releaseResult = -1;

#ifdef OSUnix
	releaseResult = sem_post(&asyncLock->HandleID);
#elif defined(OSWindows)
	releaseResult = ReleseSemaphore(asyncLock->HandleID, 1, 0);
#endif 

	return releaseResult;
}