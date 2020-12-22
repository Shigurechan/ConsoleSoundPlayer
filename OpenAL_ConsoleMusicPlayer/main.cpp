#include <iostream>
#include <cstdio>
#include <vector>
#include <Windows.h>
#define WINAPI __stdcall

#include <al.h>
#include <alc.h>
#include "conio.h"

#include "Main_Screen.hpp"

// 計算
void Update()
{

}

// 描画
void GenerateOutput()
{

}

int main() {

    setlocale(LC_ALL, " "); //スケールを指定

    
    ALCdevice* const device = alcOpenDevice(nullptr);               //デバイス
    ALCcontext* const context = alcCreateContext(device, nullptr);  //コンテキスト    
    // デバイスの生成エラー
    if (device == nullptr)
    {
        fprintf(stderr, "Couldn't open OpenAL device.");
        exit(1);
    }

    // コンテキスト生成エラー
    if (context == nullptr)
    {
        fprintf(stderr, "Couldn't create OpenAL context.\n");
        exit(1);
    }

    // コンテキストを利用
    if (alcMakeContextCurrent(context) != ALC_TRUE)
    {
        fprintf(stderr, "Couldn't make OpenAL context current.\n");
        exit(1);
    }






    //メインループ
    // -----------------------------------------------------------
    class Main_Screen* mc = new Main_Screen();

    mc->Loop();
    // -----------------------------------------------------------







    delete mc;
    mc = nullptr;
   
    alcDestroyContext(context);
    alcCloseDevice(device);
    
    return 0;
}