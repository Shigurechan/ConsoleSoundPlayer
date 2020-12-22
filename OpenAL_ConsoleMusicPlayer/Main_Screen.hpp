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


    /* ファイルパス　関係 */
    std::vector<std::string> mPlayList_Name;    //プレイリスト ファイル名
    int mPos_y = 0;                             //カーソルの位置
    std::string mPlayPath;                      //プレイしてるパス 
    std::string mNowPlay_Path;                  //現在再生中のパス
    std::string mPlayName;                      //再生中のファイル名






    bool EnterKey = false;


    // 再生状態　関係
    

    // 乱数
    std::random_device rnd;     // 非決定的な乱数生成器を生成
    std::mt19937 mt;     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    std::uniform_int_distribution<> Rand;




    // エラー処理
    bool mNoDirectory = false; // ルートディレクトリがない場合
    bool mNoFile = false; // 音楽ファイルがない場合

};



#endif
