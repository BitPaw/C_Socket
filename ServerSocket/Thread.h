#ifdef linux
#include <pthread.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif 

#ifndef ThreadInclude
#define ThreadInclude

typedef struct Thread_
{
#ifdef linux
	pthread_t ID;
#endif

#ifdef _WIN32
	void* Handle;
#endif 

}Thread;

void ThreadCreate(Thread* thread, unsigned long (*threadTask)(void* data), void* parameter);
void ThreadWaitForFinish(Thread* thread);

#endif