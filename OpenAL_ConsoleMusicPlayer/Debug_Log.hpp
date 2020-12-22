#ifndef ___DEBUG_HPP_
#define ___DEBUG_HPP_

#include <iostream>
#include <string>

class Debug_Log
{
public:

	Debug_Log(const char* FileName);	//�R���X�g���N�^
	~Debug_Log();						//�f�X�g���N�^

	void Write(const char* format, ...);	//�����`��

private:

	std::string file;
	bool b = false;
	FILE* fp = NULL;

};

#endif;
