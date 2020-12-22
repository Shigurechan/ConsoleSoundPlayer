#include "ScreenBuffer.hpp"

// コンストラクタ
ScreenBuffer::ScreenBuffer()
{
    mText = new Debug_Log("ScreenBuffer.txt");


    //描画開始座標
    mDraw_start.X = 0;
    mDraw_start.Y = 0;

    //描画範囲
    mDraw_size.X = MAX_WIDTH;
    mDraw_size.Y = MAX_HEIGHT;

    //ウインドウサイズ
    mRect.Left = (SHORT)0;
    mRect.Top = (SHORT)0;
    mRect.Right = (SHORT)MAX_WIDTH;
    mRect.Bottom = (SHORT)MAX_HEIGHT;

    // バッファーを作成
    mHandle = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    SetConsoleActiveScreenBuffer(mHandle);  //有効にする

    if (mHandle == INVALID_HANDLE_VALUE)
    { 
       
    }

    // 画面バッファサイス変更
    if (SetConsoleScreenBufferSize(mHandle, mDraw_size) == 0) 
    { 
       
    }

    // 画面サイズ変更
    if (SetConsoleWindowInfo(mHandle, TRUE, &mRect) != 0) 
    { 
       
    }    

}

// ###################################################################################################################################
// バッファーに文字を書き込む　文字をループする
void ScreenBuffer::DrawLoop(int H, int W, int speed, const char* format, ...)
{

    // エラー処理
    if (strlen(format) > MAX_WIDTH * 9 - 1) {
        mText->Write("文字数がバッファーサイズを超えました。描画できません。 %d\n", strlen(format));

        exit(0);

    }
    if (H > MAX_HEIGHT)
    {
        mText->Write("縦の表示サイズを超えました描画できません。 \n");
        exit(0);

    }
    else if (W > MAX_WIDTH)
    {
        mText->Write("横の表示サイズを超えました描画できません。 \n");
        exit(0);

    }


    va_list ap;
    char str[MAX_WIDTH * 9];
    va_start(ap, format);
    vsprintf_s(str, sizeof(str), format, ap);
    va_end(ap);

    wchar_t wc[MAX_WIDTH * 9];  //変換したwchar_t文字を格納
    size_t size = sizeof(wc);
    size_t count = sizeof(wc) / sizeof(wchar_t);
    mbstowcs_s(&size, wc, count, str, count - 1);   //マルチ文字をワイド文字に変換
    wc[MAX_WIDTH - 1] = L'\0';



    if (mNowBuffer_height >= MAX_HEIGHT)
    {
        fprintf(fp, "バッファーが表示領域の　縦を超えました。\n");
        exit(1);
    }


    // -----------------------------------------------------------------------------------------------
    int  i = 0;
    for (; mNowBuffer_width[H] <= MAX_WIDTH; mNowBuffer_width[H]++) {

        if (wc[i] != L'\0') {

            if (mNowBuffer_width[H] <= MAX_WIDTH) {

                // 日本語じゃない時
                if (wc[i] >= 0x00 && wc[i] <= 0xFF)
                {
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN;
                }

                else
                {
                    // 日本語の時
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN | COMMON_LVB_LEADING_BYTE;

                    mNowBuffer_width[H]++;

                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN | COMMON_LVB_TRAILING_BYTE;
                }
            }
            else
            {
                fprintf(fp, "Draw() 一行の文字数を超えています。\n");
                exit(1);

            }
            i++;
        }
        else {
            break;
        }
    }



    // -----------------------------------------------------------------------------------------------
}
// ###################################################################################################################################








// ###################################################################################################################################
// バッファーに文字を書き込む
void ScreenBuffer::Draw(int H ,int W,const char* format, ...)
{

    // エラー処理
    if (strlen(format) > MAX_WIDTH * 9 - 1 ) {
        mText->Write("文字数がバッファーサイズを超えました。描画できません。 %d\n", strlen(format));

       exit(0);
        
    }
    if (H > MAX_HEIGHT)
    {
        mText->Write("縦の表示サイズを超えました描画できません。 \n");
        exit(0);

    }
    else if (W > MAX_WIDTH)
    {
        mText->Write("横の表示サイズを超えました描画できません。 \n");
        exit(0);

    }
 

    va_list ap;
    char str[MAX_WIDTH * 9];
    va_start(ap, format);
    vsprintf_s(str, sizeof(str), format, ap);
    va_end(ap);

    wchar_t wc[MAX_WIDTH * 9];  //変換したwchar_t文字を格納
    size_t size = sizeof(wc);
    size_t count = sizeof(wc) / sizeof(wchar_t);
    mbstowcs_s(&size, wc, count, str, count - 1);   //マルチ文字をワイド文字に変換
    wc[MAX_WIDTH - 1] = L'\0';



    if (mNowBuffer_height >= MAX_HEIGHT)
    {
        fprintf(fp, "バッファーが表示領域の　縦を超えました。\n");
        exit(1);
    }


    // -----------------------------------------------------------------------------------------------
    int  i = 0;
    for (; mNowBuffer_width[H] <= MAX_WIDTH; mNowBuffer_width[H]++) {

        if (wc[i] != L'\0') {

            if (mNowBuffer_width[H] <= MAX_WIDTH) {

                // 日本語じゃない時
                if (wc[i] >= 0x00 && wc[i] <= 0xFF) 
                {
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN; 
                }

                else
                {
                    // 日本語の時
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN | COMMON_LVB_LEADING_BYTE;

                    mNowBuffer_width[H]++;

                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN | COMMON_LVB_TRAILING_BYTE;   
                }
            }
            else
            {
                fprintf(fp, "Draw() 一行の文字数を超えています。\n");
                exit(1);

            }
            i++;
        }
        else {
            break;
        }
    }

    

    // -----------------------------------------------------------------------------------------------
}
// ###################################################################################################################################
















// 描画
void ScreenBuffer::GenerateOutput()
{
    WriteConsoleOutput(mHandle,mScreenBuffer[0], mDraw_size, mDraw_start, &mRect); //現在のカーソル位置から始まる文字列をコンソール画面バッファーに書き込み   

    /*  バッファの参照をリセット  */
    mNowBuffer_height = 0;
    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        mNowBuffer_width[i] = 0;
    }
    
    // スクリーンバッファーを初期化
    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        for (int j = 0; j < MAX_WIDTH; j++)
        {
            mScreenBuffer[i][j].Char.UnicodeChar = 0;
        }
    }
}

// ハンドルを返す
HANDLE ScreenBuffer::getHandle()
{
    return mHandle;
}


//　デストラクタ
ScreenBuffer::~ScreenBuffer()
{
    // スクリーンバッファを解放
    CloseHandle(mHandle);
    mHandle = NULL;

    fclose(fp);

}
