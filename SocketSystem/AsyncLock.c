#include <semaphore.h>
#include "AsyncLock.h"

int SemaphoreCreate(AsyncLock* asyncLock)
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
	semaphore->HandleID = CreateSemaphore(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
#endif 

	return createResult;
}

int SemaphoreDelete(AsyncLock* asyncLock)
{
	int closingResult = -1;

#ifdef OSUnix
	closingResult = sem_destroy(&asyncLock->HandleID);
#elif defined(OSWindows)
	closingResult = CloseHandle(semaphore->HandleID);
#endif 

	return closingResult;
}

int SemaphoreLock(AsyncLock* asyncLock)
{
	int lockResult = -1;

#ifdef OSUnix
	lockResult = sem_wait(&asyncLock->HandleID);
#elif defined(OSWindows)
	lockResult = WaitForSingleObject(semaphore->HandleID, INFINITE);
#endif 

	return lockResult;	
}

int SemaphoreRelease(AsyncLock* asyncLock)
{
	int releaseResult = -1;

#ifdef OSUnix
	releaseResult = sem_post(&asyncLock->HandleID);
#elif defined(OSWindows)
	releaseResult = ReleaseSemaphore(semaphore->HandleID, 1, 0);
#endif 

	return releaseResult;
}