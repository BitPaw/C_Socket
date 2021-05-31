#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif

#include "Testscripts/PathTest.h"
#include "Testscripts/ListTest.h"

#include "Tester.h"

#include <stdlib.h>


int main()
{		
	// Example Tests:
	/*
	// -- Test Int
	
	test_int_Failure(4,2,"Int Test");	
	test_int(2, 2, "Int Test 2");

	// -- Test String
	test_string("Hallo", "Hallo", "String Test");
	test_string(NULL, NULL, "String NULL Test 1");
	test_string_Failure(NULL, "Hallo", "String NULL Test 2");
	test_string_Failure("Hallo", NULL, "String NULL Test 3");

	// -- Test Generics
	test_t("Hallo", "Hallo", sizeof(char)*6, "string", "Generic Test 1");
	test_t_Failure("Hallo", "Hal", sizeof(char)*6, "string", "Generic Test 2");

	
	int t1 = 4; int t2 = 4;
	test_t(&t1, &t2, sizeof(int), "Int", "Generic Test 3");

	t1 = INT_MAX; t2 = 444;
	test_t_Failure(&t1, &t2, sizeof(int), "Int", "Generic Test 4");
	*/

	path_test(1);

	list_test(1);
	
	testPrintSummery();

	
#ifdef OSWindows
system("pause");
#else
printf("Terminated\n");
#endif
}
