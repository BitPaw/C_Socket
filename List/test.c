#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

#include <stdio.h>
#include <stdlib.h>


int main()
{
	printf("Hello World\n");


	
#ifdef OSWindows
	system("pause");
#else
	printf("Terminated\n");
#endif
}
