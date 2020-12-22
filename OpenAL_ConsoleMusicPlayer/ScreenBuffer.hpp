#ifndef ___SCREEN_BUFFER_HPP_
#define ___SCREEN_BUFFER_HPP_
#include "stdio.h"
#include "stdlib.h"
#include <Windows.h>
#include <iostream>

#include "Debug_Log.hpp"

// �E�C���h�E�T�C�Y
#define  MAX_WIDTH ((int)100)
#define  MAX_HEIGHT ((int)40)

/*################################################
* ������`�悷��N���X
################################################*/

class ScreenBuffer
{
public:

    ScreenBuffer();  //�R���X�g���N�^
	~ScreenBuffer();                               //�f�X�g���N�^

	void GenerateOutput(); //�`�悷��

    void Draw(int H, int W, const char* format, ...);   //�o�b�t�@�[�ɏ�������
    void DrawLoop(int H, int W,int speed, const char* format, ...);   //�o�b�t�@�[�ɏ������݁@�����Ȃ����������̓��[�v����


    HANDLE getHandle();
    
private:

    //vector<int> mCount;


	CHAR_INFO mScreenBuffer[MAX_HEIGHT][MAX_WIDTH];  //��ʃo�b�t�@
	HANDLE mHandle; //�n���h��

    COORD mDraw_start;  //�`��J�n�ʒu
    COORD mDraw_size;   //��ʂ̃T�C�Y
    _SMALL_RECT mRect;  //��ʂ̕`��͈�    

    /* �i�[�ł��镶�������J�E���g */
    int mNowBuffer_width[MAX_HEIGHT];   //��
    int mNowBuffer_height = 0;          //�c

    Debug_Log *mText;   //�f�o�b�O�p�e�L�X�g�o��
    FILE* fp;           //�t�@�C���|�C���^
};
#endif;