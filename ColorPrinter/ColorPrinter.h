#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#ifndef ColorPrinterInclude
#define ColorPrinterInclude

	/*
	 * Global Variable: printColors:
	 * if enabled colorPrintf prints colors
	 */
	char printColors;

	 /*
	  * Function:  colorPrintf
	  * --------------------
	  * prints with colors like printf [printColors must be 1]:
	  * --------------------
	  *    colorPrintf("&1HALLO &2%s &3%i\n","Test",5);
	  *    
	  *	output: "RED[HALLO] GREEN[Test] YELLOW[5]\n"
	  *
	  *	colors:
	  *		BLACK[0], RED[1], GREEN[2], YELLOW[3], BLUE[4], MAGENTA[5], CYAN[6], WHITE[7]
	  *		
	  *	backgroundColor:
	  *		BLACK[a], RED[b], GREEN[c], YELLOW[d], BLUE[e], MAGENTA[f], CYAN[g], WHITE[h]
	  *		
	  *  returns: the normal printf() return value 
	  */
	int colorPrintf(char* _Format, ...);

	void printColorTable();

#endif