#ifndef SemaphoreIncluded
#define SemaphoreIncluded

#include "OSDefine.h"

#ifdef OSUnix
// ???
#elif defined(OSWindows)
#include <Windows.h>
#include <process.h>
#endif 

typedef struct Semaphore_
{
#ifdef OSUnix
	sem_t HandleID;
#elif defined(OSWindows)
	HANDLE HandleID;
#endif

}Semaphore;

int SemaphoreCreate(Semaphore* semaphore);
int SemaphoreDelete(Semaphore* semaphore);
int SemaphoreLock(Semaphore* semaphore);
int SemaphoreRelease(Semaphore* semaphore);

#endif