#include "Test.h"
#include "CommandToken.h"

unsigned int testCount;

void test_int(int expectedInput, int input)
{
    printf("\n------ Test [%i] [INT] --------\n", testCount++);

    if (expectedInput != input)
        printf("[X] Test failed:\n   -Expected input '%i', actual '%i'\n", input, expectedInput);
    else
        printf("    Test completed\n");

    printf("------------------------------\n");
}

void test_string(char* expectedInput, char* input)
{
    printf("\n------ Test [%i] [String] -----\n", testCount++);

    if (memcmp(input, expectedInput, sizeof(char) * (strlen(input) < strlen(expectedInput)) ? strlen(input) : strlen(expectedInput)))
        printf("[X] Test failed:\n   -Expected input '%s', actual '%s'\n", input, expectedInput);
    else
        printf("    Test completed\n");

    printf("------------------------------\n");
}

void test_CommandToken_Compare() 
{
    CommandToken commandToken1, commandToken2;

    CommandTokenInitialize(&commandToken1);
    CommandTokenInitialize(&commandToken2);

    char* message1 = calloc(14,sizeof(char));
    char* message2 = calloc(13, sizeof(char));;

    memcpy(message1, "GET;test;Peter", 14);
    memcpy(message2, "GET;test;Paul", 13);

    CommandTokenParse(&commandToken1, message1);
    CommandTokenParse(&commandToken2, message2);

    test_int(CommandTokenCompare(&commandToken1, &commandToken2), -2);
}
