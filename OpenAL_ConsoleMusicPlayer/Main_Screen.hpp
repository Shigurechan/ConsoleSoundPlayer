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
# メイン画面
##############################################*/

class Main_Screen
{
public:

    Main_Screen();    		//コンストラクタ
    ~Main_Screen();    		//デストラクタ
    void Loop();            //ループ
    void Update();		    //計算
    void GenerateOutput();  //描画
    void Input();           //キー入力
    


private:

    /* コンポーネント 関係 */
    KeyInput *mInput;        //キー入力  
    SoundPlayer *mSound;    //音楽再生 
    Debug_Log *mText;       //デバッグ用　テキストファイルに書き込む
    ScreenBuffer *mWindow;  //画面描画

    std::vector<std::string> mPlayList_Name;    //プレイリスト ファイル名
    std::vector<std::string> mPlayList_Path;    //プレイリスト　ディレクトリパス



    int mPos_y = 0;  //カーソルの位置


    //ファイルパス 関係
    std::string mNowDir_Path;                   //今いるディレクトリのパス
    std::string mPlayPath;                      //プレイ中のパス 
    std::string mRootDir_Path;                  //一番最初のパス
    std::string mNowSelect_Path;                //選択中のファイル

    int mNowPath_num;                           //今のパス番号
    std::vector<std::string> mIndexString;      //mNowPath_numの値を使って前後をのパスを取得
    std::map<std::string,int> mCursorDir_pos;   //カーソルの場所(数値)をパスの値を使って調べる

    bool EnterKey = false;


    //再生状態　関係
    int mPlayList_Num;  //曲のリスト数
    bool mNo_Playing;   //何も再生していない場合
    bool mEnter;        //選んだ曲を決定
    bool mEnter_push;   //mEnterを押しているかどうか？　連打防止


    //再生時間ゲージ
    float mMemsec;          //１枚のメモリ
    int mNowMemory;         //現在のメモリ
    int mAllMemory;   //全体のメモリ    
    float mPlayingMemory;   //蓄積秒数






    // エラー処理
    bool mNoDirectory = false; // ルートディレクトリがない場合
    bool mNoFile = false; // 音楽ファイルがない場合

};



#endif
