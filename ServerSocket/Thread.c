#include "Thread.h"
#include <windows.h>

void ThreadCreate(Thread* thread, unsigned long (*threadTask)(void* data), void* parameter)
{
#ifdef linux
    thread->ID = pthread_create(&thread_id, NULL, myThreadFun, NULL);
#endif

#ifdef _WIN32
	const LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;
	const SIZE_T dwStackSize = NULL;
	const LPTHREAD_START_ROUTINE lpStartAddress = (LPTHREAD_START_ROUTINE)threadTask;
	const LPVOID lpParameter = parameter;
	const DWORD dwCreationFlags = NULL;
	const LPDWORD lpThreadId = NULL;

    thread->Handle = CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
#endif
}

void ThreadWaitForFinish(Thread* thread)
{
#ifdef linux
    pthread_join(thread->ID, NULL);
#endif 

#ifdef _WIN32
	
#endif 


   
}