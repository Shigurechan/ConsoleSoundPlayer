#include "Debug_Log.hpp"
#include <string>
#include <iostream>

#include "stdarg.h"
#include <cstdarg>


//コンストラクタ
Debug_Log::Debug_Log(const char* FileName)
{
	file = FileName;
	fopen_s(&fp, FileName, "w");
	fclose(fp);
}



//書き込み
void Debug_Log::Write(const char* format,...)
{
	fopen_s(&fp, file.c_str(), "a");



	va_list ap;
	char str[10000];
	va_start(ap, format);
	vsprintf_s(str, sizeof(str), format, ap);
	va_end(ap);

	fprintf(fp, str);


	fclose(fp);

}


//デストラクタ
Debug_Log::~Debug_Log()
{
	fclose(fp);
}