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
	List a,b,c;
	
	// Test: 1 [char*]
	ListInitialize(&a, 3, sizeof(char*));

	ListItemInsertAt(&a, 0, "a");
	ListItemInsertAt(&a, 2, "b");
	
	test_string("a", (char*)ListItemGet(&a, 0));
	
	ListPrint_string(&a);
	ListItemAdd(&a, "c");
	ListPrint_string(&a);

	test_string(NULL, (char*)ListItemGet(&a, 3));
	test_string("b", (char*)ListItemGet(&a, 2));
	
	test_string("c", (char*)ListItemGet(&a, 1));
	
	ListDestruction(&a);

	// Test: 2 [int]
	ListInitialize(&b, 2, sizeof(int));
	
	ListItemAdd(&b, 12321);
	ListItemAdd(&b, 5);
	ListItemAdd(&b, 54);
	
	test_int(12321, (int)ListItemGet(&b, 0));
	test_int(5, (int)ListItemGet(&b, 1));
	test_int(54, (int)ListItemGet(&b, 2));
	test_int(0, (int)b.content[3]);
	test_int(0, (int)ListItemGet(&b, 4));
		
	ListDestruction(&b);

	// Test: 3 [int]
	
	ListInitialize(&c, 2, sizeof(int));
	
	for (int i = 0; i < 150; ++i)
		ListItemAdd(&c, 54);
	

	ListItemInsertAt(&c, 150,99);

	ListItemAdd(&c, 54);
	
	test_int(99, (int)ListItemGet(&c, 150));
	test_int(54, (int)ListItemGet(&c, 151));
	
	ListDestruction(&c);
	
#ifdef OSWindows
	system("pause");
#else
	printf("Terminated\n");
#endif
}
