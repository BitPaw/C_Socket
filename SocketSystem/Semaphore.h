#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif
#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

#ifdef OSWindows
#include <Windows.h>
#include <process.h>

typedef struct Semaphore_
{
	HANDLE HandleID;
}Semaphore;

#endif

#ifdef OSUnix
typedef struct Semaphor_
{
	sem_t HandleID;
}Semaphor;
#endif 

int SemaphoreCreate(Semaphore* semaphore);
int SemaphoreDelete(Semaphore* semaphore);
int SemaphoreLock(Semaphore* semaphore);
int SemaphoreRelease(Semaphore* semaphore);