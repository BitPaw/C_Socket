#include "Thread.h"
#include <windows.h>

void ThreadCreate(Thread* thread, unsigned long (*threadTask)(void* data), void* parameter)
{
#ifdef linux
    thread->ID = pthread_create(&thread_id, NULL, myThreadFun, NULL);
#endif

#ifdef _WIN32
    LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;
    SIZE_T dwStackSize = NULL;
    LPTHREAD_START_ROUTINE lpStartAddress = (LPTHREAD_START_ROUTINE)threadTask;
    LPVOID lpParameter = parameter;
    DWORD dwCreationFlags = NULL;
    LPDWORD lpThreadId = NULL;

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