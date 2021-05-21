#if defined(linux) || defined(__APPLE__)
#include <pthread.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif 

#ifndef ThreadInclude
#define ThreadInclude

typedef struct Thread_
{
#if defined(linux) || defined(__APPLE__)
	pthread_t ID;
#endif

#ifdef _WIN32
	void* Handle;
#endif 

}Thread;

#if defined(linux) || defined(__APPLE__)
void ThreadCreate(Thread* thread, void* (*threadTask)(void* data), void* parameter);
#endif

#ifdef _WIN32
void ThreadCreate(Thread* thread, unsigned long (*threadTask)(void* data), void* parameter);
#endif

void ThreadWaitForFinish(Thread* thread);

#endif