#include "Semaphore.h"

int SemaphoreCreate(Semaphore* semaphore)
{
	int createResult = -1;

#ifdef OSWindows
	LPSECURITY_ATTRIBUTES lpSemaphoreAttributes = 0;
	LONG lInitialCount = 1;
	LONG lMaximumCount = 1;
	LPCWSTR lpName = 0;

	semaphore->HandleID = CreateSemaphore(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);

	createResult = 0;
#endif

#ifdef OSUnix
	int sharedPointer = 0;
	unsigned int value = 1;

	createResult = sem_init(&semaphore->HandleID, sharedPointer, value);
#endif 

	return createResult;
}

int SemaphoreDelete(Semaphore* semaphore)
{
	int closingResult = -1;

#ifdef OSWindows
	closingResult = CloseHandle(semaphore->HandleID);
#endif

#ifdef OSUnix
	closingResult = sem_destroy(&semaphore->HandleID);
#endif 

	return closingResult;
}

int SemaphoreLock(Semaphore* semaphore)
{
	int lockResult = -1;

#ifdef OSWindows
	lockResult = WaitForSingleObject(semaphore->HandleID, INFINITE);
#endif

#ifdef OSUnix
	lockResult = sem_wait(&semaphore->HandleID);
#endif 

	return lockResult;	
}

int SemaphoreRelease(Semaphore* semaphore)
{
	int releaseResult = -1;

#ifdef OSWindows
	releaseResult = ReleaseSemaphore(semaphore->HandleID, 1, 0);
#endif

#ifdef OSUnix
	releaseResult = sem_post(&semaphore->HandleID);
#endif 

	return releaseResult;
}