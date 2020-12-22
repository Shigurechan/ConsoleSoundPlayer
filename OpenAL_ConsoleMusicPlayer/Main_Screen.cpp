#include <iostream>
#include <algorithm>
#include <vector>
#include <compare>
#include <filesystem>
#include <map>
#include <WINDOWS.h>
#include "stdio.h"
#include <random>


#include "Main_Screen.hpp"
#include "SoundPlayer.hpp"
#include "KeyInput.hpp"
#include "ScreenBuffer.hpp"

//コンストラクタ
Main_Screen::Main_Screen()
{
    // 乱数を初期化

    mt.seed(rnd());
    std::uniform_int_distribution<> Rand(0, 100);


    /* コンポーネント　関係 */
    mText = new Debug_Log("Main_Screen.txt");   //デバッグ用　テキスト出力
    mWindow = new ScreenBuffer();               //画面描画
    mInput = new KeyInput();                    //キー入力
    mSound = new SoundPlayer();                 //サウンド再生

    
    std::string path = "Music"; //ルートパス
        try {
            for (const auto& fp : std::filesystem::directory_iterator::directory_iterator(path))
            {
                //        mText->Write("ええええ\n");
                mPlayList_Name.push_back(fp.path().string());
                
            }

            // ファイルの数が0の場合
            if (mPlayList_Name.size() == 0)
            {
                mNoFile = true;
            }
        }
        catch (std::exception e)
        {
            //　ディレクトリがない場合は作成して終了

            mText->Write("%s", e.what());
            std::filesystem::create_directory(path);
            mNoDirectory = true;
        }



}



// キー入力
void Main_Screen::Input()
{
    mInput->getKeyUpdate();

    // カーソルの上下移動
    if (mInput->getKeyDown(KeyCode::DOWN_KEY) && true)
    {
        mPos_y++;
        if (mPos_y > (int)mPlayList_Name.size() - 1)
        {
            mPos_y = (int)mPlayList_Name.size() - 1;
        }

    }else if (mInput->getKeyDown(KeyCode::UP_KEY) && true)
    {
        mPos_y--;

        if (mPos_y < 0)
        {
            mPos_y = 0;
        }
    }


    // 左キー 戻るキー
    else if (mInput->getKeyDown(KeyCode::LEFT_KEY) && true)
    {

       
        const std::filesystem::path fp = std::filesystem::path(mPlayPath);
        std::filesystem::path ff = fp.parent_path();
        mPlayPath = ff.string();

        mText->Write("%s\n",mPlayPath.c_str());

        if (strcmp(mPlayPath.c_str(),"\0") != 0) {
          //  if (mPlayPath.c_str() != "\0") {
            mPos_y = 0;
            mPlayList_Name.clear();


            for (const auto& fp : std::filesystem::directory_iterator::directory_iterator(mPlayPath))
            {
                mPlayList_Name.push_back(fp.path().string());
            }
        }
    }


    //決定ボタン
    else if ( (mInput->getKeyDown(KeyCode::ENTER_KEY) == true) && (EnterKey == false)  )
    {
        EnterKey = true;
    }

    // 再生と一時停止
    else if (mInput->getKeyDown(KeyCode::SPACE_KEY) && true)
    {
        if (mSound->isNowState() == 1)
        {
            mSound->Pause();
        }else if (mSound->isNowState() == 2)
        {
            mSound->Play();
        }
    }



    // ########################################################## 終了
    if (mInput->getKeyDown(KeyCode::ESC_KEY) && true)
    { 
        exit(0);
    }
    // ##########################################################
    mInput->ResetKey();
}



//更新
void Main_Screen::Update()
{
    
    mText->Write("%d\n",Rand(mt));


    Input();    //入力更新    

    if (EnterKey == true)
    {
        // ルートディレクトリが無いかファイルが無い場合
        if (mNoDirectory == true || mNoFile == true)
        {
            exit(1);
        }
        
        const char* st = std::strrchr(mPlayList_Name.at(mPos_y).c_str(), '.');
        if (st == NULL)
        {
            mPlayPath = mPlayList_Name.at(mPos_y);  //パスを設定
            mPlayList_Name.clear();
            for (const auto& fp : std::filesystem::directory_iterator::directory_iterator(mPlayPath))
            {
                mPlayList_Name.push_back(fp.path().string());
            }

            mPos_y = 0; //カーソルを一番上に戻す
        }
        else
        {
            mSound->Stop();

            mNowPlay_Path = mPlayList_Name.at(mPos_y);  //パスを設定
            mPlayName = std::filesystem::path(mNowPlay_Path).filename().string();


            mSound->InputFile(mNowPlay_Path.c_str());
            mSound->Play();
        }
        

        
        
        EnterKey = false;
    }







}


// -------------------------- ループ ----------------------------------
void Main_Screen::Loop()
{
    while (true) 
    {
        Update();   //計算



        GenerateOutput();   //描画
        Sleep((DWORD)16.66);


       

    }
}
// --------------------------     ------------------------------------

#define PLAY_LIST_POS_Y 10//プレイリストを表示するy座標

//描画更新
void Main_Screen::GenerateOutput()
{
    // ディレクトリが無い場合の表示
    if (mNoDirectory == true)
    {
        mWindow->Draw(0,0,"Musicファイルの中に音楽ファイルを入れてください。");
    }
    else if (mNoFile == true)
    {
        mWindow->Draw(0, 0, "ファイルまたはディレクトリが一つもありません。");
    }
    else {
        // メイン画面




        if (Rand(mt) % 2 == 0) {
            mText->Write("あああ\n");
            mWindow->Draw(0, 0, "Sound Player ♪:  %s", mPlayName.c_str());
        }
        else {
            mText->Write("いいい\n");

            mWindow->Draw(0, 0, "Sound Player  :  %s", mPlayName.c_str());
        }



        // プレイリスト
        mWindow->Draw(PLAY_LIST_POS_Y - 2, 0, " --- PLAY LIST  --- ");
        for (int i = 0; i < mPlayList_Name.size(); i++)
        {
            std::string str = std::filesystem::path(mPlayList_Name.at(i)).filename().string();

            if (mPos_y == i)
            {
                mWindow->Draw(i + PLAY_LIST_POS_Y, 0, "->  ");
                mWindow->Draw(i + PLAY_LIST_POS_Y, 0, str.c_str());
            }
            else
            {
                mWindow->Draw(i + PLAY_LIST_POS_Y, 0, str.c_str());
            }
        }
    }









    mWindow->GenerateOutput();
}







//デストラクタ
Main_Screen::~Main_Screen()
{    
    delete mText;
    mText = nullptr;

    delete mWindow;
    mWindow = nullptr;


}


