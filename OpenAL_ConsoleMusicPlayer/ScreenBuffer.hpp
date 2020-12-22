#ifndef ___SCREEN_BUFFER_HPP_
#define ___SCREEN_BUFFER_HPP_
#include "stdio.h"
#include "stdlib.h"
#include <Windows.h>
#include <iostream>

#include "Debug_Log.hpp"

// ウインドウサイズ
#define  MAX_WIDTH ((int)100)
#define  MAX_HEIGHT ((int)40)

/*################################################
* 文字を描画するクラス
################################################*/

class ScreenBuffer
{
public:

    ScreenBuffer();  //コンストラクタ
	~ScreenBuffer();                               //デストラクタ

	void GenerateOutput(); //描画する

    void Draw(int H, int W, const char* format, ...);   //バッファーに書き込み
    void DrawLoop(int H, int W,int speed, const char* format, ...);   //バッファーに書き込み　足しなくった文字はループする


    HANDLE getHandle();
    
private:

    //vector<int> mCount;


	CHAR_INFO mScreenBuffer[MAX_HEIGHT][MAX_WIDTH];  //画面バッファ
	HANDLE mHandle; //ハンドル

    COORD mDraw_start;  //描画開始位置
    COORD mDraw_size;   //画面のサイズ
    _SMALL_RECT mRect;  //画面の描画範囲    

    /* 格納できる文字数をカウント */
    int mNowBuffer_width[MAX_HEIGHT];   //横
    int mNowBuffer_height = 0;          //縦

    Debug_Log *mText;   //デバッグ用テキスト出力
    FILE* fp;           //ファイルポインタ
};
#endif;