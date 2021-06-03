#include "ListTest.h"

#include "../Tester.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void list_test(char execute)
{
	if (execute == 0)
		return;

	testPrintHeader("List-Tests");
	
	
	List a = EMPTYLIST;
	List b = EMPTYLIST;
	List c = EMPTYLIST;

	// Test: 1 [char*]
	ListInitialize(&a, 3, sizeof(char*));

	char* testChar1 = calloc(2,sizeof(char));
	strcpy_s(testChar1, 2, "a");
	
	char* testChar2 = calloc(4, sizeof(char));
	strcpy_s(testChar2,4, "bbb");
	
	char* testChar3 = calloc(2, sizeof(char));
	strcpy_s(testChar3, 2, "c");
	
	ListItemInsertAt(&a, 0, testChar1);
	ListItemInsertAt(&a, 2, testChar2);

		test_string("a", (char*)ListItemGet(&a, 0),"List Test 1");

	ListItemAdd(&a, testChar3);

		test_string(NULL, (char*)ListItemGet(&a, 3), "List Test 2");
		test_string("bbb", (char*)ListItemGet(&a, 2), "List Test 3");

		test_string("c", (char*)ListItemGet(&a, 1), "List Test 4");

	ListDestruction(&a);

	// Test: 2 [int]
	ListInitialize(&b, 2, sizeof(int*));

	int* testInt1 = calloc(1, sizeof(int));
	*testInt1 = 12321;
	
	int* testInt2 = calloc(1, sizeof(int));
	*testInt2 = 5;
	
	int* testInt3 = calloc(1, sizeof(int));
	*testInt3 = 54;

	ListItemAdd(&b, testInt1);
	ListItemAdd(&b, testInt2);
	ListItemAdd(&b, testInt3);
	
	test_int(12321, *(int*)ListItemGet(&b, 0), "List Test 5");
	test_int(5, *(int*)ListItemGet(&b, 1), "List Test 6");
	test_int(54, *(int*)ListItemGet(&b, 2), "List Test 7");
	test_int(0, b.content[3], "List Test 8");
	test_int(0, ListItemGet(&b, 4), "List Test 9");

	ListDestruction(&b);

	// Test: 3 (add 150 Int)[int]

	ListInitialize(&c, 2, sizeof(int*));

	for (int i = 0; i < 150; ++i)
	{
		int* testIntX = calloc(1, sizeof(int));
		*testIntX = 54;
		ListItemAdd(&c, testIntX);
	}
		
	int* testInt4 = calloc(1, sizeof(int));
	*testInt4 = 99;

	ListItemInsertAt(&c, 150, testInt4);

	int* testInt5 = calloc(1, sizeof(int));
	*testInt5 = 54;
	ListItemAdd(&c, testInt5);

		test_int(99, *(int*)ListItemGet(&c, 150), "List Test 10");
		test_int(54, *(int*)ListItemGet(&c, 151), "List Test 11");

	ListDestruction(&c);
	
	// Test: 4 Remove an Clear[int]
	b = EMPTYLIST;
	
	ListInitialize(&b, 2, sizeof(int));
	
	int* testInt6 = calloc(1, sizeof(int));
	*testInt6 = 44;

	int* testInt7 = calloc(1, sizeof(int));
	*testInt7 = 55;

	int* testInt8 = calloc(1, sizeof(int));
	*testInt8 = 56;

	int* testInt9 = calloc(1, sizeof(int));
	*testInt9 = 57;

	int* testInt10 = calloc(1, sizeof(int));
	*testInt10 = 58;
		
	ListItemAdd(&b, testInt6);
	ListItemAdd(&b, testInt7);
	ListItemAdd(&b, testInt8);
	ListItemAdd(&b, testInt9);
	ListItemAdd(&b, testInt10);

		test_int(57, *(int*)ListItemGet(&b, 3), "List Test 13");
	
	ListItemRemove(&b, 3);
	
		test_int(0, ListItemGet(&b, 3), "List Test 14");

	ListClear(&b);
	
		test_int(0, ListItemGet(&b, 0), "List Test 15");
		test_int(0, ListItemGet(&b, 4), "List Test 16");

	ListDestruction(&b);
	
}
