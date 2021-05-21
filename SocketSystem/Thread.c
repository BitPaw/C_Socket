#include "Thread.h"

#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#ifdef OSUnix
void ThreadCreate(Thread* thread, void* (*threadTask)(void* data), void* parameter)
{
    thread->ID = pthread_create(&thread->ID, 0, threadTask, parameter);
}
#endif

#ifdef OSWindows
void ThreadCreate(Thread* thread, unsigned long (*threadTask)(void* data), void* parameter)
{
	const LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;
	const SIZE_T dwStackSize = NULL;
	const LPTHREAD_START_ROUTINE lpStartAddress = (LPTHREAD_START_ROUTINE)threadTask;
	const LPVOID lpParameter = parameter;
	const DWORD dwCreationFlags = NULL;
	const LPDWORD lpThreadId = NULL;

    thread->Handle = CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}
#endif


void ThreadWaitForFinish(Thread* thread)
{
#ifdef OSUnix
    //pthread_join(thread->ID, NULL);
#endif 

}


/*
void forkstuff()
{
    const unsigned int input = 1;
    const unsigned int output = 0;
    int pipeConnector[2];

    pipe(pipeConnector);

    if (fork() == 0)
    {
        dup2(pipe_connect[input], input);
        close(pipe_connect[output]);
        execlp("who", "who", output);
                
    }
    else if(fork() == 0)
    {
        dub2(pipe_connect[output], output);
        close(pipe_connect[input]);
        execlp("sort", "sort", output);
    }
    else
    {
        close(pipe_connecr[0]);
        wait(0);
        wait(0);
    }


    // Shared memory
    int nameKey = IPC_PRIVATE;
    int sizeInBytes = 0;
    int permissionFlag = 777; // CHMOD value like 777. rwx
    int id = shmget(nameKey, sizeInBytes, permissionFlag); // Create shared memory or just use it if it already exists.


    int id = 0;
    void* preferedAdress = 0;
    int useageFlag = 0; // 0 or SHM_RDONLY
    void* adress = shmat(id, preferedAdress, useageFlag); 


       shmctl(id, cmd, buffer);
}*/