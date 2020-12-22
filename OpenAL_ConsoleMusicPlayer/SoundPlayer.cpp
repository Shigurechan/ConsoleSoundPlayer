#include "SoundPlayer.hpp"
#include <iostream>
#include <al.h>
#include <alc.h>
#include "dr_wav.hpp"


//�R���X�g���N�^
SoundPlayer::SoundPlayer()
{
  //  printf("SoundPlayer �R���X�g���N�^\n");
    
    mText = new Debug_Log("SoundPlayer.txt");

    mPause = true;      //�ꎞ��~���Ă��邩�ǂ��H
    wav = new drwav();  //.wav�t�@�C���Đ����C�u����

    mTime = 0;          //���Ԃ�������


    mSource = 0;		// OpenAL �\�[�X
    mBuffer = 0;		// OpenAL�@�o�b�t�@�[


    // --- �o�b�t�@�[
    mBuffer = 0;
    alGenBuffers(1, &mBuffer);
    if (alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Couldn't generate buffer.\n");
        exit(1);
    }

    // --- �\�[�X
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

    // --- �o�b�t�@�[
    mBuffer = 0;
    alGenBuffers(1, &mBuffer);
    if (alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Couldn't generate buffer.\n");
        exit(1);
    }

    // --- �\�[�X
    mSource = 0;
    alGenSources(1, &mSource);
    if (alGetError() != AL_NO_ERROR)
    {
        fprintf(stderr, "Couldn't generate source.\n");
        exit(1);
    }


    mFilePath = fp; //�t�@�C�����p�X


//    std::string FilePath = "Music.wav"; //�t�@�C����
    // .wav�t�@�C����ǂݍ���  
    if (!drwav_init_file(wav, mFilePath.c_str(), nullptr)) {
        fprintf(stderr, "Couldn't load file for reading.\n");
        exit(1);
    }


    // PCM�f�[�^��ǂݎ��A������o�b�t�@�Ƀ��[�h���܂��B
    std::vector<int16_t> sampleData;// OpenAL�@�T���v��
    sampleData.resize(wav->totalPCMFrameCount * wav->channels);

    //�I�[�f�B�I�̃`�����N��16�r�b�gPCM�T���v���ɕύX���܂��B
    mFramesCount = drwav_read_pcm_frames_s16(wav, wav->totalPCMFrameCount, sampleData.data());

  //  printf("frames: %llu\n", framesRead);

    //�G���[����
    if (mFramesCount != wav->totalPCMFrameCount)
    {
        fprintf(stderr, "Couldn't read file.\n");
    }

    mAllsec = mFramesCount / wav->sampleRate;

    mBisPerSample = wav->bitsPerSample; //�r�b�g�p�[�t���[��
    mSampleRate = wav->sampleRate;      //�T���v�����[�g

    //�X�e���I�����m��������ݒ�   
    if (wav->channels == 2) 
    {    
        mChannels = AL_FORMAT_STEREO16; //�p�����[�^
        format = AL_FORMAT_STEREO16;
    }
    else {
        mChannels = AL_FORMAT_MONO16;   //�p�����[�^
        format = AL_FORMAT_MONO16;  
    }

    alBufferData(mBuffer, format, sampleData.data(), static_cast<ALsizei>(sampleData.size() * sizeof(int16_t)), wav->sampleRate); //���yPCM�f�[�^�Ƀo�b�t�@��ݒ�

    // �G���[����
    if (alGetError() != AL_NO_ERROR) 
    {
        fprintf(stderr, "Could not buffer data.\n");
        exit(1); 
    }    
}




//�Đ�
void SoundPlayer::Play()
{
  
   // printf("����������\n");
    // ---------------------- �Đ��@----------------------
    
    alGetSourcei(mSource, AL_SOURCE_STATE, &mPlaying);
    
    if (mPlaying != AL_PLAYING) {
       
        alSourcei(mSource, AL_BUFFER, mBuffer);   //source��ݒ�
        alSourcePlay(mSource);
    }    
    // ---------------------- �Đ��@----------------------
    
    mPause = false;
    // �I������
   drwav_uninit(wav);
}


//�ꎞ��~
void SoundPlayer::Pause()
{
    alSourcePause(mSource);

}

//�Đ��I��
void SoundPlayer::Stop()
{
    alSourceStop(mSource);

}

/*
* �Đ�����    1
* 
* �ꎞ��~���� 2
* 
* ��~����    3 
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





//�f�X�g���N�^
SoundPlayer::~SoundPlayer()
{
    delete wav;
    wav = nullptr;
    alDeleteSources(1, &mSource);
    alDeleteBuffers(1, &mBuffer);
    
}

