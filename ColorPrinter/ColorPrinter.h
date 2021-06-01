#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define OSWindows
#endif

#if defined(linux) || defined(__APPLE__)
#define OSUnix
#endif


#ifndef ColorPrinterInclude
#define ColorPrinterInclude

	char printColors;

	/// <summary>
	/// prints like printf
	/// </summary>
	/// <param name="_Format">You can add into _Format &x x={0-9,a-h}</param>
	/// <returns></returns>
	int colorPrintf(char* _Format, ...);

	void printColorTable();

#endif