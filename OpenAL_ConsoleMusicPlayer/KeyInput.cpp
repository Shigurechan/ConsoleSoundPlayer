#include "KeyInput.hpp"
#include "conio.h"

KeyInput::KeyInput()
{
    setlocale(LC_CTYPE, "");    //���[�J����ݒ�
    handle = GetStdHandle(STD_INPUT_HANDLE);    //�n���h����ݒ�
    
    Length = 1;     //buffer��������
    lpNumber = 0;   //���̓��R�[�h�̐����󂯎��
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
            // ������Ă��Ȃ���
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



// �L�[�������ꂽ�u�Ԃ���
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



