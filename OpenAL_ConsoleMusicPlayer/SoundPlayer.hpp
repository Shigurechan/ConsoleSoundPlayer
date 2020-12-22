#ifndef ___SOUNDPLAYER_HPP_
#define ___SOUNDPLAYER_HPP_
#include <iostream>
#include <al.h>
#include <alc.h>
#include "Debug_Log.hpp"


#include "dr_wav.hpp"
#define DR_WAV_IMPLEMENTATION

#include "dr_mp3.hpp"
#define DR_MP3_IMPLEMENTATION

#include <iostream>
#include <cstdio>
#include <vector>
#include <Windows.h>

#include <vector>

class SoundPlayer
{
public:

	SoundPlayer();					//コンストラクタ
	~SoundPlayer();					//デストラクタ
	void InputFile(const char* fp);	//ファイル名を入力して待機
	void Play();					//再生中
	void Pause();					//一時停止
	void Stop();					//再生終了


	bool isPlay();					//再生中
	bool isPause();					//一時停止
	bool isStop();					//再生終了

	int isNowState();				//再生中かどうか？



	ALuint mSource = 0;	// OpenAL ソース
	ALuint mBuffer = 0;	// OpenAL　バッファー

	Debug_Log *mText;

	std::string mFilePath;		//ファイルパス	
	ALenum format;				//チャンネル
	drwav_uint64 mFramesCount;	// PCM フレーム数
	drwav_uint64 mBisPerSample;	//ビットパーフレーム
	drwav_uint64 mSampleRate;	//サンプルレート
	int mChannels;				//チャンネル数
	bool mPause;				//一時停止しているかどか？
	float mTime;					//再生時間
	unsigned long long  mAllsec;//全体時間

	int mPlaying;
private:

	drwav* wav = nullptr;	//drwavライブラリ

};
#endif