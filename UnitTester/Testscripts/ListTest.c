#include "ListTest.h"

#include "../Tester.h"
#include <stddef.h>
#include <stdio.h>


void list_test(char execute)
{
	if (execute == 0)
		return;

	testPrintHeader("List-Tests");
	
	
	List a, b, c;

	// Test: 1 [char*]
	ListInitialize(&a, 3, sizeof(char*));

	ListItemInsertAt(&a, 0, "a");
	ListItemInsertAt(&a, 2, "b");

		test_string("a", (char*)ListItemGet(&a, 0),"List Test 1");

	ListItemAdd(&a, "c");

		test_string(NULL, (char*)ListItemGet(&a, 3), "List Test 2");
		test_string("b", (char*)ListItemGet(&a, 2), "List Test 3");

		test_string("c", (char*)ListItemGet(&a, 1), "List Test 4");

	ListDestruction(&a);

	// Test: 2 [int]
	ListInitialize(&b, 2, sizeof(int));

	ListItemAdd(&b, 12321);
	ListItemAdd(&b, 5);
	ListItemAdd(&b, 54);

		test_int(12321, (int)ListItemGet(&b, 0), "List Test 5");
		test_int(5, (int)ListItemGet(&b, 1), "List Test 6");
		test_int(54, (int)ListItemGet(&b, 2), "List Test 7");
		test_int(0, (int)b.content[3], "List Test 8");
		test_int(0, (int)ListItemGet(&b, 4), "List Test 9");

	ListDestruction(&b);

	// Test: 3 (add 150 Int)[int]

	ListInitialize(&c, 2, sizeof(int));

	for (int i = 0; i < 150; ++i)
		ListItemAdd(&c, 54);


	ListItemInsertAt(&c, 150, 99);

	ListItemAdd(&c, 54);

		test_int(99, (int)ListItemGet(&c, 150), "List Test 10");
		test_int(54, (int)ListItemGet(&c, 151), "List Test 11");

	ListDestruction(&c);
	
	// Test: 4 Remove an Clear[int]

	ListInitialize(&b, 2, sizeof(int));

	//ListClear(&b);
	
	ListItemAdd(&b, 44);
	ListItemAdd(&b, 55);
	ListItemAdd(&b, 56);
	ListItemAdd(&b, 57);
	ListItemAdd(&b, 58);

		test_int(57, (int)ListItemGet(&b, 3), "List Test 13");
	
	ListItemRemove(&b, 3);
	
		test_int(0, (int)ListItemGet(&b, 3), "List Test 14");

	ListClear(&b);
	
		test_int(0, (int)ListItemGet(&b, 0), "List Test 15");
		test_int(0, (int)ListItemGet(&b, 4), "List Test 16");

	ListDestruction(&b);
	
}
