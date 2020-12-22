#include "KeyInput.hpp"
#include "conio.h"

KeyInput::KeyInput()
{
    setlocale(LC_CTYPE, "");    //ローカルを設定
    handle = GetStdHandle(STD_INPUT_HANDLE);    //ハンドルを設定
    
    Length = 1;     //bufferを初期化
    lpNumber = 0;   //入力レコードの数を受け取る
}


void KeyInput::getKeyUpdate()
{
    if (ReadConsoleInput(handle, &Buffer, 1, &lpNumber) != 0)
    {
        if (Buffer.Event.KeyEvent.bKeyDown == true) 
        {
            mPushkey = Buffer.Event.KeyEvent.wVirtualKeyCode;
            misPush[(int)mPushkey] = true;     
        }
        else
        {
            // 押されていない時
            for (int i = 0; i < 255; i++)
            {
                misPush[(int)i] = false;                
            }
        }

    }
    else
    {

    }
}



// キーが押された瞬間だけ
bool KeyInput::getKeyDown(KeyCode key) {


    if ( misPush[(int)key] == true && misHoldPush[(int)key] == false)
    {   
        misHoldPush[(int)key] = true;
        return true;
    }    
    else if(misPush[(int)key] == false && misHoldPush[(int)key] == true)
    {
        misHoldPush[(int)key] = false;
        //return false;
    }



   
    return false;


}

void KeyInput::ResetKey()
{
    for (int i = 0; i < 255; i++)
    {
        misPush[(int)i] = false;

    }

}

bool KeyInput::getKeyHoldDown()
{
    return false;
}


KeyInput::~KeyInput()
{

}



