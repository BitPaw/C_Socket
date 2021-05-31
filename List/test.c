#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

static unsigned int testCount;

static void test_int(int expectedInput, int input)
{
	printf("\n------ Test [%i] [INT] --------\n", testCount++);

	if (expectedInput != input)
		printf("[X] Test failed:\n   -Expected input '%i', actual '%i'\n", expectedInput, input);
	else
		printf("    Test completed\n");

	printf("------------------------------\n");
}

static void test_string(char* expectedInput, char* input)
{
	printf("\n------ Test [%i] [String] -----\n", testCount++);

	if (!(expectedInput == NULL && input == NULL))
	{
		if (expectedInput == NULL || input == NULL)
		{
			printf("[X] Test failed:\n   -Expected input '%s', actual '%s'\n", expectedInput,input);
			return;
		}
			

		const unsigned int fullPathLength = (strlen(expectedInput) > strlen(input)) ? strlen(expectedInput) : strlen(input);
		if (memcmp(expectedInput, input, sizeof(char) * fullPathLength) != 0)
			printf("[X] Test failed:\n   -Expected input '%s', actual '%s'\n", expectedInput, input);
		else
			printf("    Test completed\n");
	}
	else
		printf("    Test completed\n");
	
	printf("------------------------------\n");	
}



int main()
{
	List a,b;

	ListInitialize(&a, 3, sizeof(char*));

	ListInsertAt(&a, 0, "a");
	ListInsertAt(&a, 2, "b");
	
	test_string("a", (char*)ListGet(&a, 0));
	

	ListAdd(&a, "c");


	test_string(NULL, (char*)ListGet(&a, 3));
	test_string("b", (char*)ListGet(&a, 2));
	
	test_string("c", (char*)ListGet(&a, 0));
	
	ListDestruction(&a);


	ListInitialize(&b, 2, sizeof(int));

	ListAdd(&b, 12321);
	ListAdd(&b, 5);
	ListAdd(&b, 54);
	
	test_int(12321, (int)ListGet(&b, 0));
	test_int(5, (int)ListGet(&b, 1));
	test_int(54, (int)ListGet(&b, 2));
	test_int(0, (int)b.content[3]);
	test_int(0, (int)ListGet(&b, 4));
		
	ListDestruction(&b);

	
#ifdef OSWindows
	system("pause");
#else
	printf("Terminated\n");
#endif
}
