#include "ColorPrintf.hpp"
#include <string>
#include <iostream>

#include "stdarg.h"
#include <cstdarg>


ColorPrintf::ColorPrintf()
{

}

// レンダリング関数　背景色　前景色　文字列						
void ColorPrintf::RenderText(Color_Code Back, Color_Code Front, const char* format,...) {
	
	//色指定子を取得
	std::string front = getColorFront(Front); 
	std::string back = getColorBack(Back);
	
	//文字を生成
	std::string text; //生成した文字を格納
	va_list ap;
	char str[100];
	va_start(ap, format);
	vsprintf_s(str, sizeof(str), format, ap);
	va_end(ap);

	//最後に元に戻す
	std::string reset_front = "\x1b[39m";
	std::string reset_back = "\x1b[49m";
}


// レンダリング関数　背景色　前景色　文字列						
void ColorPrintf::RenderText_Line(Color_Code Back, Color_Code Front, const char* format, ...) {

	//色指定子を取得
	std::string front = getColorFront(Front);
	std::string back = getColorBack(Back);

	//文字を生成
	std::string text; //生成した文字を格納
	va_list ap;
	char str[1000];
	va_start(ap, format);
	vsprintf_s(str, sizeof(str), format, ap);
	va_end(ap);
	text = std::string(str);

	//最後に元に戻す
	char reset_front[6] = "\x1b[39m";
	char reset_back[6] = "\x1b[49m";

	//printf("%s",back.c_str());
	//printf("%s%s%s%s%s", front.c_str(), back.c_str(), text.c_str(), reset_back, reset_front);

}






//色コードを取得 前景色
std::string ColorPrintf::getColorFront(Color_Code& color)
{
	switch (color)
	{	
	case Color_Code::Red:
		return red_front;
		break;

	case Color_Code::Green:
		return green_front;
		break;

	case Color_Code::Yellow:
		return yellow_front;
		break;

	case Color_Code::Blue:
		return blue_front;
		break;

	case Color_Code::Magenta:
		return magenta_front;
		break;

	case Color_Code::Cyan:
		return cyan_front;
		break;

	case Color_Code::Black:
		return black_front;
		break;

	case Color_Code::White:
		return white_front;
		break;

	default://エラー処理
		std::string name = "無効なコードです。 Color_Code\n";
		return name;//Color_Code::Invalid;
		break;

	};
}


//色コードを取得 背景色
std::string ColorPrintf::getColorBack(Color_Code& color)
{
	switch (color)
	{
	case Color_Code::Black:
		return black_back;
		break;

	case Color_Code::Red:
		return red_back;
		break;

	case Color_Code::Green:
		return green_back;
		break;

	case Color_Code::Yellow:
		return yellow_back;
		break;

	case Color_Code::Blue:
		return blue_back;
		break;

	case Color_Code::Magenta:
		return magenta_back;
		break;

	case Color_Code::Cyan:
		return cyan_back;
		break;

	case Color_Code::Gray:
		return gray_back;
		break;

	default://エラー処理
		std::string name = "無効なコードです。 Color_Code\n";
		return name;//Color_Code::Invalid;
		break;

	};
}


ColorPrintf::~ColorPrintf()
{

}