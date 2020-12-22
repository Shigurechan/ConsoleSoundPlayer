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

	SoundPlayer();					//�R���X�g���N�^
	~SoundPlayer();					//�f�X�g���N�^
	void InputFile(const char* fp);	//�t�@�C��������͂��đҋ@
	void Play();					//�Đ���
	void Pause();					//�ꎞ��~
	void Stop();					//�Đ��I��


	bool isPlay();					//�Đ���
	bool isPause();					//�ꎞ��~
	bool isStop();					//�Đ��I��

	int isNowState();				//�Đ������ǂ����H



	ALuint mSource = 0;	// OpenAL �\�[�X
	ALuint mBuffer = 0;	// OpenAL�@�o�b�t�@�[

	Debug_Log *mText;

	std::string mFilePath;		//�t�@�C���p�X	
	ALenum format;				//�`�����l��
	drwav_uint64 mFramesCount;	// PCM �t���[����
	drwav_uint64 mBisPerSample;	//�r�b�g�p�[�t���[��
	drwav_uint64 mSampleRate;	//�T���v�����[�g
	int mChannels;				//�`�����l����
	bool mPause;				//�ꎞ��~���Ă��邩�ǂ��H
	float mTime;					//�Đ�����
	unsigned long long  mAllsec;//�S�̎���

	int mPlaying;
private:

	drwav* wav = nullptr;	//drwav���C�u����

};
#endif