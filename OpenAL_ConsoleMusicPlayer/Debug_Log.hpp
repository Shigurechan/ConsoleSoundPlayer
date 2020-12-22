#ifndef ___DEBUG_HPP_
#define ___DEBUG_HPP_

#include <iostream>
#include <string>

class Debug_Log
{
public:

	Debug_Log(const char* FileName);	//コンストラクタ
	~Debug_Log();						//デストラクタ

	void Write(const char* format, ...);	//文字描画

private:

	std::string file;
	bool b = false;
	FILE* fp = NULL;

};

#endif;
