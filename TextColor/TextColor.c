#include "TextColor.h"
#include <stdio.h>

char TranslateColor(Color color)
{
	switch (color)
	{
		case ColorGray:
			return 90;

		case ColorRed:
			return 91;

		case ColorGreen:
			return 92;

		case ColorYellow:
			return 93;

		case ColorBlue:
			return 94;

		case ColorMagenta:
			return 95;

		case ColorAqua:
			return 96;

		case ColorWhite:
			return 97;

		default:
		case ColorBlack:
			return 98;
	}
}

void SetTextColorAndBackGroudnColor(Color forground, char useBackGround)
{
	char forgroundColor = TranslateColor(forground);

	if (useBackGround)
	{
		forgroundColor += 10;
	}

	printf("\033[%dm", forgroundColor);
}

void SetColor(Color color)
{
	SetTextColorAndBackGroudnColor(color, 0);
}