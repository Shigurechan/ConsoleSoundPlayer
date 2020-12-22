#include "ColorPrintf.hpp"
#include <string>
#include <iostream>

#include "stdarg.h"
#include <cstdarg>


ColorPrintf::ColorPrintf()
{

}

// �����_�����O�֐��@�w�i�F�@�O�i�F�@������						
void ColorPrintf::RenderText(Color_Code Back, Color_Code Front, const char* format,...) {
	
	//�F�w��q���擾
	std::string front = getColorFront(Front); 
	std::string back = getColorBack(Back);
	
	//�����𐶐�
	std::string text; //���������������i�[
	va_list ap;
	char str[100];
	va_start(ap, format);
	vsprintf_s(str, sizeof(str), format, ap);
	va_end(ap);

	//�Ō�Ɍ��ɖ߂�
	std::string reset_front = "\x1b[39m";
	std::string reset_back = "\x1b[49m";
}


// �����_�����O�֐��@�w�i�F�@�O�i�F�@������						
void ColorPrintf::RenderText_Line(Color_Code Back, Color_Code Front, const char* format, ...) {

	//�F�w��q���擾
	std::string front = getColorFront(Front);
	std::string back = getColorBack(Back);

	//�����𐶐�
	std::string text; //���������������i�[
	va_list ap;
	char str[1000];
	va_start(ap, format);
	vsprintf_s(str, sizeof(str), format, ap);
	va_end(ap);
	text = std::string(str);

	//�Ō�Ɍ��ɖ߂�
	char reset_front[6] = "\x1b[39m";
	char reset_back[6] = "\x1b[49m";

	//printf("%s",back.c_str());
	//printf("%s%s%s%s%s", front.c_str(), back.c_str(), text.c_str(), reset_back, reset_front);

}






//�F�R�[�h���擾 �O�i�F
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

	default://�G���[����
		std::string name = "�����ȃR�[�h�ł��B Color_Code\n";
		return name;//Color_Code::Invalid;
		break;

	};
}


//�F�R�[�h���擾 �w�i�F
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

	default://�G���[����
		std::string name = "�����ȃR�[�h�ł��B Color_Code\n";
		return name;//Color_Code::Invalid;
		break;

	};
}


ColorPrintf::~ColorPrintf()
{

}