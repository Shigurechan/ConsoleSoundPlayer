#ifndef ___COLORPRINTF_HPP_
#define ___COLORPRINTF_HPP_

#include <iostream>
#include <string>


// �F���
enum class Color_Code
{
	Black,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	Gray,
	White,
	Invalid,
};


class ColorPrintf
{
public:
	ColorPrintf();	//�R���X�g���N�^		
	~ColorPrintf();	//�f�X�g���N�^

	void RenderText(Color_Code Back, Color_Code Front, const char* format, ...);	//�����`��
	void RenderText_Line(Color_Code Back, Color_Code Front, const char* format, ...);
//	void RenderText(Color_Code Back, Color_Code Front, const char* format, ...);	//�����`��

	std::string getColorFront(Color_Code& color);	//�O�i�F�̐F�w��q���擾
	std::string getColorBack(Color_Code& color);	//�w�i�F�̐F�w��q���擾


private:

	// �w�i�F
	std::string black_back = "\x1b[40m";
	std::string red_back = "\x1b[41m";
	std::string green_back = "\x1b[42m";
	std::string yellow_back = "\x1b[43m";
	std::string blue_back = "\x1b[44m";
	std::string magenta_back = "\x1b[45m";
	std::string cyan_back = "\x1b[46m";
	std::string gray_back = "\x1b[47m";
	
	//�@�O�i�F
	std::string black_front = "\x1b[30m";
	std::string red_front = "\x1b[31m";
	std::string green_front = "\x1b[32m";
	std::string yellow_front = "\x1b[33m";
	std::string blue_front = "\x1b[34m";
	std::string magenta_front = "\x1b[35m";
	std::string cyan_front = "\x1b[36m";
	std::string white_front = "\x1b[37m";
	
};

#endif;
