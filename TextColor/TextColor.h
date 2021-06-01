#ifndef ColorIncluded
#define ColorIncluded

typedef enum Color_
{
	ColorGray, // 1
	ColorRed, // 2
	ColorGreen, // 3
	ColorYellow, // 4
	ColorBlue,
	ColorMagenta, // 
	ColorAqua, // 7
	ColorWhite, // 8
	ColorBlack //  
}Color;

char TranslateColor(Color color);
void SetTextColorAndBackGroudnColor(Color forground, char useBackGround);
void SetColor(Color color);

#endif 