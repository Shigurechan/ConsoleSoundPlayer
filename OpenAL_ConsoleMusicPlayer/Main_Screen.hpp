#ifndef ___MAIN_SCREEN_HPP_
#define ___MAIN_SCREEN_HPP_

#include <compare>
#include <iostream>
#include <filesystem>
#include <random>
#include <map>
#include <vector>
#include <Windows.h>
#include "stdio.h"
#include <random>

#include "SoundPlayer.hpp"
#include "KeyInput.hpp"
#include "KeyCode.hpp"
#include "Debug_Log.hpp"
#include "ScreenBuffer.hpp"


/*############################################
# ���C�����
##############################################*/

class Main_Screen
{
public:

    Main_Screen();    		//�R���X�g���N�^
    ~Main_Screen();    		//�f�X�g���N�^
    void Loop();            //���[�v
    void Update();		    //�v�Z
    void GenerateOutput();  //�`��
    void Input();           //�L�[����
    
private:

    /* �R���|�[�l���g �֌W */
    KeyInput *mInput;        //�L�[����  
    SoundPlayer *mSound;    //���y�Đ� 
    Debug_Log *mText;       //�f�o�b�O�p�@�e�L�X�g�t�@�C���ɏ�������
    ScreenBuffer *mWindow;  //��ʕ`��


    /* �t�@�C���p�X�@�֌W */
    std::vector<std::string> mPlayList_Name;    //�v���C���X�g �t�@�C����
    int mPos_y = 0;                             //�J�[�\���̈ʒu
    std::string mPlayPath;                      //�v���C���Ă�p�X 
    std::string mNowPlay_Path;                  //���ݍĐ����̃p�X
    std::string mPlayName;                      //�Đ����̃t�@�C����






    bool EnterKey = false;


    // �Đ���ԁ@�֌W
    

    // ����
    std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
    std::mt19937 mt;     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
    std::uniform_int_distribution<> Rand;




    // �G���[����
    bool mNoDirectory = false; // ���[�g�f�B���N�g�����Ȃ��ꍇ
    bool mNoFile = false; // ���y�t�@�C�����Ȃ��ꍇ

};



#endif
