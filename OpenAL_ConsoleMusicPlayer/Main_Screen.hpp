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

    std::vector<std::string> mPlayList_Name;    //�v���C���X�g �t�@�C����
    std::vector<std::string> mPlayList_Path;    //�v���C���X�g�@�f�B���N�g���p�X



    int mPos_y = 0;  //�J�[�\���̈ʒu


    //�t�@�C���p�X �֌W
    std::string mNowDir_Path;                   //������f�B���N�g���̃p�X
    std::string mPlayPath;                      //�v���C���̃p�X 
    std::string mRootDir_Path;                  //��ԍŏ��̃p�X
    std::string mNowSelect_Path;                //�I�𒆂̃t�@�C��

    int mNowPath_num;                           //���̃p�X�ԍ�
    std::vector<std::string> mIndexString;      //mNowPath_num�̒l���g���đO����̃p�X���擾
    std::map<std::string,int> mCursorDir_pos;   //�J�[�\���̏ꏊ(���l)���p�X�̒l���g���Ē��ׂ�

    bool EnterKey = false;


    //�Đ���ԁ@�֌W
    int mPlayList_Num;  //�Ȃ̃��X�g��
    bool mNo_Playing;   //�����Đ����Ă��Ȃ��ꍇ
    bool mEnter;        //�I�񂾋Ȃ�����
    bool mEnter_push;   //mEnter�������Ă��邩�ǂ����H�@�A�Ŗh�~


    //�Đ����ԃQ�[�W
    float mMemsec;          //�P���̃�����
    int mNowMemory;         //���݂̃�����
    int mAllMemory;   //�S�̂̃�����    
    float mPlayingMemory;   //�~�ϕb��






    // �G���[����
    bool mNoDirectory = false; // ���[�g�f�B���N�g�����Ȃ��ꍇ
    bool mNoFile = false; // ���y�t�@�C�����Ȃ��ꍇ

};



#endif
