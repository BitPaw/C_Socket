#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

#ifdef OSUNIX
	#include <pthread.h>
#elif defined(OSWindows)
	#include <Windows.h>
#endif 

#ifndef ThreadInclude
#define ThreadInclude


#ifdef OSUnix
typedef struct Thread_
{
	pthread_t ID;
}Thread;

void ThreadCreate(Thread* thread, void* (*threadTask)(void* data), void* parameter);

#endif

#ifdef OSWindows

typedef struct Thread_
{
	void* Handle;
}Thread;

void ThreadCreate(Thread* thread, unsigned long (*threadTask)(void* data), void* parameter);

#endif

void ThreadWaitForFinish(Thread* thread);
#endif
