#include "ColorPrinter.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"

#define BACK_COLOR_BLACK   "\x1b[40m"
#define BACK_COLOR_RED     "\x1b[41m"
#define BACK_COLOR_GREEN   "\x1b[42m"
#define BACK_COLOR_YELLOW  "\x1b[43m"
#define BACK_COLOR_BLUE    "\x1b[44m"
#define BACK_COLOR_MAGENTA "\x1b[45m"
#define BACK_COLOR_CYAN    "\x1b[46m"
#define BACK_COLOR_WHITE   "\x1b[47m"

#define ANSI_COLOR_RESET   "\x1b[0m"

const int colorLength = 5;
const int colorResetLength = 4;

int colorPrintf(char * _Format, ...) {

	int returnValue;
	int i = 0;
	int lastAnd = -1;
	
	const int formatLength = strlen(_Format);
	
	if(printColors)
	{
		int countSymbols = 0;
		while (_Format[i] != '\0')
		{
			if (_Format[i] == '&')
				countSymbols++;
			i++;
		}
		
		const unsigned int newFormatLength = (formatLength - countSymbols * 2) + (colorLength * countSymbols) + colorResetLength +1;

		char* format = calloc(newFormatLength, sizeof(char));


		i = 0;
		
		while(_Format[i] != '\0')
		{
			if(_Format[i] == '&')
			{
				//copies old Values
				if (i != 0)
					if (lastAnd == -1)
						memcpy(format, _Format , i * sizeof(char));
					else
						memcpy(format + strlen(format), _Format + lastAnd + 2, (i-lastAnd -2) * sizeof(char));

				lastAnd = i;
				
				//copies ColorTag
				switch (_Format[i + 1])
				{
					//Reset
				case 'r':
					memcpy(format + strlen(format), ANSI_COLOR_RESET, colorLength * sizeof(char));
					break;
					//ForegroundColor
				case '0':
					memcpy(format + strlen(format), ANSI_COLOR_BLACK, colorLength * sizeof(char));
					break;
				case '1':
					memcpy(format + strlen(format), ANSI_COLOR_RED, colorLength * sizeof(char));
					break;
				case '2':
					memcpy(format + strlen(format), ANSI_COLOR_GREEN, colorLength * sizeof(char));
					break;
				case '3':
					memcpy(format + strlen(format), ANSI_COLOR_YELLOW, colorLength * sizeof(char));
					break;
				case '4':
					memcpy(format + strlen(format), ANSI_COLOR_BLUE, colorLength * sizeof(char));
					break;
				case '5':
					memcpy(format + strlen(format), ANSI_COLOR_MAGENTA, colorLength * sizeof(char));
					break;
				case '6':
					memcpy(format + strlen(format), ANSI_COLOR_CYAN, colorLength * sizeof(char));
					break;
				case '7':
					memcpy(format + strlen(format), ANSI_COLOR_WHITE, colorLength * sizeof(char));
					break;
					//BackColor
				case 'a':
					memcpy(format + strlen(format), BACK_COLOR_BLACK, colorLength * sizeof(char));
					break;
				case 'b':
					memcpy(format + strlen(format), BACK_COLOR_RED, colorLength * sizeof(char));
					break;
				case 'c':
					memcpy(format + strlen(format), BACK_COLOR_GREEN, colorLength * sizeof(char));
					break;
				case 'd':
					memcpy(format + strlen(format), BACK_COLOR_YELLOW, colorLength * sizeof(char));
					break;
				case 'e':
					memcpy(format + strlen(format), BACK_COLOR_BLUE, colorLength * sizeof(char));
					break;
				case 'f':
					memcpy(format + strlen(format), BACK_COLOR_MAGENTA, colorLength * sizeof(char));
					break;
				case 'g':
					memcpy(format + strlen(format), BACK_COLOR_CYAN, colorLength * sizeof(char));
					break;
				case 'h':
					memcpy(format + strlen(format), BACK_COLOR_WHITE, colorLength * sizeof(char));
					break;
				}
				
				
				i++;
			}
			
			i++;
		}
		memcpy(format + strlen(format), _Format + lastAnd + 2, (i - lastAnd - 2) * sizeof(char));
		memcpy(format + strlen(format), ANSI_COLOR_RESET, colorResetLength * sizeof(char));
		
		va_list argptr;
		va_start(argptr, _Format);
		returnValue = vprintf(format, argptr);
		va_end(argptr);

		free(format);
	}
	else
	{
		char* format = calloc(strlen(_Format), sizeof(char));

		i = 0;
		while(_Format[i] != '\0')
		{
			if(_Format[i] == '&')
			{
				if (i != 0)
					if (lastAnd == -1)
						memcpy(format, _Format, i * sizeof(char));
					else
						memcpy(format + strlen(format), _Format + lastAnd + 2, (i - lastAnd - 2) * sizeof(char));

				lastAnd = i;
				i++;
			}
			i++;
		}
		memcpy(format + strlen(format), _Format + lastAnd + 2, (i - lastAnd - 2) * sizeof(char));
				
		va_list argptr;
		va_start(argptr, _Format);
		returnValue = vfprintf(stderr, format, argptr);
		va_end(argptr);

		free(format);
	}

	return returnValue;
}

void printColorTable()
{
	if(printColors == 0)
	{
		printf("enable global variable \'printColors=1\'\n ");
		return;
	}

	
	printf("------------------------\n");
	printf("-    ColorTable        -\n");
	printf("------------------------\n");
	colorPrintf(" [0] BLACK    :\t&0&hTest\n");
	colorPrintf(" [1] RED      :\t&1Test\n");
	colorPrintf(" [2] GREEN    :\t&2Test\n");
	colorPrintf(" [3] YELLOW   :\t&3Test\n");
	colorPrintf(" [4] BLUE     :\t&4Test\n");
	colorPrintf(" [5] MAGENTA  :\t&5Test\n");
	colorPrintf(" [6] CYAN     :\t&6Test\n");
	colorPrintf(" [7] WHITE    :\t&7Test\n");
	printf("------------------------\n");
	colorPrintf(" [a] B_BLACK  :\t&aTest\n");
	colorPrintf(" [b] B_RED    :\t&bTest\n");
	colorPrintf(" [c] B_GREEN  :\t&cTest\n");
	colorPrintf(" [d] B_YELLOW :\t&dTest\n");
	colorPrintf(" [e] B_BLUE   :\t&eTest\n");
	colorPrintf(" [f] B_MAGENTA:\t&fTest\n");
	colorPrintf(" [g] B_CYAN   :\t&gTest\n");
	colorPrintf(" [h] B_WHITE  :\t&0&hTest\n");
	printf("------------------------\n");
}
