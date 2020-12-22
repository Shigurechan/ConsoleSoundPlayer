#include "SoundPlayer.hpp"
#include <iostream>
#include <al.h>
#include <alc.h>
#include "dr_wav.hpp"


//コンストラクタ
SoundPlayer::SoundPlayer()
{
  //  printf("SoundPlayer コンストラクタ\n");
    
    mText = new Debug_Log("SoundPlayer.txt");

    mPause = true;      //一時停止しているかどか？
    wav = new drwav();  //.wavファイル再生ライブラリ

    mTime = 0;          //時間を初期化


    mSource = 0;		// OpenAL ソース
    mBuffer = 0;		// OpenAL　バッファー


    // --- バッファー
    mBuffer = 0;
    alGenBuffers(1, &mBuffer);
    if (alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Couldn't generate buffer.\n");
        exit(1);
    }

    // --- ソース
    mSource = 0;
    alGenSources(1, &mSource);
    if (alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Couldn't generate source.\n");
        exit(1);
    }

}

void SoundPlayer::InputFile(const char* fp)
{

    // --- バッファー
    mBuffer = 0;
    alGenBuffers(1, &mBuffer);
    if (alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Couldn't generate buffer.\n");
        exit(1);
    }

    // --- ソース
    mSource = 0;
    alGenSources(1, &mSource);
    if (alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Couldn't generate source.\n");
        exit(1);
    }


    mFilePath = fp; //ファイル名パス


//    std::string FilePath = "Music.wav"; //ファイル名
    // .wavファイルを読み込む  
    if (!drwav_init_file(wav, mFilePath.c_str(), nullptr)) {
        fprintf(stderr, "Couldn't load file for reading.\n");
        exit(1);
    }


    // PCMデータを読み取り、それをバッファにロードします。
    std::vector<int16_t> sampleData;// OpenAL　サンプル
    sampleData.resize(wav->totalPCMFrameCount * wav->channels);

    //オーディオのチャンクを16ビットPCMサンプルに変更します。
    mFramesCount = drwav_read_pcm_frames_s16(wav, wav->totalPCMFrameCount, sampleData.data());

  //  printf("frames: %llu\n", framesRead);

    //エラー処理
    if (mFramesCount != wav->totalPCMFrameCount)
    {
        fprintf(stderr, "Couldn't read file.\n");
    }

    mAllsec = mFramesCount / wav->sampleRate;

    mBisPerSample = wav->bitsPerSample; //ビットパーフレーム
    mSampleRate = wav->sampleRate;      //サンプルレート

    //ステレオかモノラルかを設定   
    if (wav->channels == 2) 
    {    
        mChannels = AL_FORMAT_STEREO16; //パラメータ
        format = AL_FORMAT_STEREO16;
    }
    else {
        mChannels = AL_FORMAT_MONO16;   //パラメータ
        format = AL_FORMAT_MONO16;  
    }

    alBufferData(mBuffer, format, sampleData.data(), static_cast<ALsizei>(sampleData.size() * sizeof(int16_t)), wav->sampleRate); //音楽PCMデータにバッファを設定

    // エラー処理
    if (alGetError() != AL_NO_ERROR) 
    {
        fprintf(stderr, "Could not buffer data.\n");
        exit(1); 
    }    
}




//再生
void SoundPlayer::Play()
{
  
   // printf("あああああ\n");
    // ---------------------- 再生　----------------------
    
    alGetSourcei(mSource, AL_SOURCE_STATE, &mPlaying);
    
    if (mPlaying != AL_PLAYING) {
       
        alSourcei(mSource, AL_BUFFER, mBuffer);   //sourceを設定
        alSourcePlay(mSource);
    }    
    // ---------------------- 再生　----------------------
    
    mPause = false;
    // 終了処理
   drwav_uninit(wav);
}


//一時停止
void SoundPlayer::Pause()
{
    alSourcePause(mSource);

}

//再生終了
void SoundPlayer::Stop()
{
    alSourceStop(mSource);

}

/*
* 再生中は    1
* 
* 一時停止中は 2
* 
* 停止中は    3 
*/
int SoundPlayer::isNowState()
{
    alGetSourcei(mSource, AL_SOURCE_STATE, &mPlaying);

    if (mPlaying == AL_PLAYING)
    {
        mText->Write("AL_PLAYING\n");
        return 1;
    }
    else if (mPlaying == AL_STOPPED)
    {
        mText->Write("AL_STOPPED\n");

        return 3;
    }
    else if (mPlaying == AL_PAUSED)
    {
        mText->Write("AL_PAUSED\n");

        return 2;
    }

    return -1;
}

bool SoundPlayer::isPlay()
{
    alGetSourcei(mSource, AL_SOURCE_STATE, &mPlaying);

    if (mPlaying == AL_PLAYING)
    {    
        return true;
    }
    else
    {
        return false;
    }

}

bool SoundPlayer::isPause()
{
    alGetSourcei(mSource, AL_SOURCE_STATE, &mPlaying);

    if (mPlaying == AL_STOPPED)
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool SoundPlayer::isStop()
{
    alGetSourcei(mSource, AL_SOURCE_STATE, &mPlaying);

    if (mPlaying == AL_PAUSED)
    {
        return true;
    }
    else
    {
        return false;
    }

}





//デストラクタ
SoundPlayer::~SoundPlayer()
{
    delete wav;
    wav = nullptr;
    alDeleteSources(1, &mSource);
    alDeleteBuffers(1, &mBuffer);
    
}

