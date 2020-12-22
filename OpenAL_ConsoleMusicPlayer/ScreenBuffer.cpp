#include "ScreenBuffer.hpp"

// �R���X�g���N�^
ScreenBuffer::ScreenBuffer()
{
    mText = new Debug_Log("ScreenBuffer.txt");


    //�`��J�n���W
    mDraw_start.X = 0;
    mDraw_start.Y = 0;

    //�`��͈�
    mDraw_size.X = MAX_WIDTH;
    mDraw_size.Y = MAX_HEIGHT;

    //�E�C���h�E�T�C�Y
    mRect.Left = (SHORT)0;
    mRect.Top = (SHORT)0;
    mRect.Right = (SHORT)MAX_WIDTH;
    mRect.Bottom = (SHORT)MAX_HEIGHT;

    // �o�b�t�@�[���쐬
    mHandle = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    SetConsoleActiveScreenBuffer(mHandle);  //�L���ɂ���

    if (mHandle == INVALID_HANDLE_VALUE)
    { 
       
    }

    // ��ʃo�b�t�@�T�C�X�ύX
    if (SetConsoleScreenBufferSize(mHandle, mDraw_size) == 0) 
    { 
       
    }

    // ��ʃT�C�Y�ύX
    if (SetConsoleWindowInfo(mHandle, TRUE, &mRect) != 0) 
    { 
       
    }    

}

// ###################################################################################################################################
// �o�b�t�@�[�ɕ������������ށ@���������[�v����
void ScreenBuffer::DrawLoop(int H, int W, int speed, const char* format, ...)
{

    // �G���[����
    if (strlen(format) > MAX_WIDTH * 9 - 1) {
        mText->Write("���������o�b�t�@�[�T�C�Y�𒴂��܂����B�`��ł��܂���B %d\n", strlen(format));

        exit(0);

    }
    if (H > MAX_HEIGHT)
    {
        mText->Write("�c�̕\���T�C�Y�𒴂��܂����`��ł��܂���B \n");
        exit(0);

    }
    else if (W > MAX_WIDTH)
    {
        mText->Write("���̕\���T�C�Y�𒴂��܂����`��ł��܂���B \n");
        exit(0);

    }


    va_list ap;
    char str[MAX_WIDTH * 9];
    va_start(ap, format);
    vsprintf_s(str, sizeof(str), format, ap);
    va_end(ap);

    wchar_t wc[MAX_WIDTH * 9];  //�ϊ�����wchar_t�������i�[
    size_t size = sizeof(wc);
    size_t count = sizeof(wc) / sizeof(wchar_t);
    mbstowcs_s(&size, wc, count, str, count - 1);   //�}���`���������C�h�����ɕϊ�
    wc[MAX_WIDTH - 1] = L'\0';



    if (mNowBuffer_height >= MAX_HEIGHT)
    {
        fprintf(fp, "�o�b�t�@�[���\���̈�́@�c�𒴂��܂����B\n");
        exit(1);
    }


    // -----------------------------------------------------------------------------------------------
    int  i = 0;
    for (; mNowBuffer_width[H] <= MAX_WIDTH; mNowBuffer_width[H]++) {

        if (wc[i] != L'\0') {

            if (mNowBuffer_width[H] <= MAX_WIDTH) {

                // ���{�ꂶ��Ȃ���
                if (wc[i] >= 0x00 && wc[i] <= 0xFF)
                {
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN;
                }

                else
                {
                    // ���{��̎�
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN | COMMON_LVB_LEADING_BYTE;

                    mNowBuffer_width[H]++;

                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN | COMMON_LVB_TRAILING_BYTE;
                }
            }
            else
            {
                fprintf(fp, "Draw() ��s�̕������𒴂��Ă��܂��B\n");
                exit(1);

            }
            i++;
        }
        else {
            break;
        }
    }



    // -----------------------------------------------------------------------------------------------
}
// ###################################################################################################################################








// ###################################################################################################################################
// �o�b�t�@�[�ɕ�������������
void ScreenBuffer::Draw(int H ,int W,const char* format, ...)
{

    // �G���[����
    if (strlen(format) > MAX_WIDTH * 9 - 1 ) {
        mText->Write("���������o�b�t�@�[�T�C�Y�𒴂��܂����B�`��ł��܂���B %d\n", strlen(format));

       exit(0);
        
    }
    if (H > MAX_HEIGHT)
    {
        mText->Write("�c�̕\���T�C�Y�𒴂��܂����`��ł��܂���B \n");
        exit(0);

    }
    else if (W > MAX_WIDTH)
    {
        mText->Write("���̕\���T�C�Y�𒴂��܂����`��ł��܂���B \n");
        exit(0);

    }
 

    va_list ap;
    char str[MAX_WIDTH * 9];
    va_start(ap, format);
    vsprintf_s(str, sizeof(str), format, ap);
    va_end(ap);

    wchar_t wc[MAX_WIDTH * 9];  //�ϊ�����wchar_t�������i�[
    size_t size = sizeof(wc);
    size_t count = sizeof(wc) / sizeof(wchar_t);
    mbstowcs_s(&size, wc, count, str, count - 1);   //�}���`���������C�h�����ɕϊ�
    wc[MAX_WIDTH - 1] = L'\0';



    if (mNowBuffer_height >= MAX_HEIGHT)
    {
        fprintf(fp, "�o�b�t�@�[���\���̈�́@�c�𒴂��܂����B\n");
        exit(1);
    }


    // -----------------------------------------------------------------------------------------------
    int  i = 0;
    for (; mNowBuffer_width[H] <= MAX_WIDTH; mNowBuffer_width[H]++) {

        if (wc[i] != L'\0') {

            if (mNowBuffer_width[H] <= MAX_WIDTH) {

                // ���{�ꂶ��Ȃ���
                if (wc[i] >= 0x00 && wc[i] <= 0xFF) 
                {
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN; 
                }

                else
                {
                    // ���{��̎�
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN | COMMON_LVB_LEADING_BYTE;

                    mNowBuffer_width[H]++;

                    mScreenBuffer[H][mNowBuffer_width[H] + W].Char.UnicodeChar = wc[i];
                    mScreenBuffer[H][mNowBuffer_width[H] + W].Attributes = FOREGROUND_GREEN | COMMON_LVB_TRAILING_BYTE;   
                }
            }
            else
            {
                fprintf(fp, "Draw() ��s�̕������𒴂��Ă��܂��B\n");
                exit(1);

            }
            i++;
        }
        else {
            break;
        }
    }

    

    // -----------------------------------------------------------------------------------------------
}
// ###################################################################################################################################
















// �`��
void ScreenBuffer::GenerateOutput()
{
    WriteConsoleOutput(mHandle,mScreenBuffer[0], mDraw_size, mDraw_start, &mRect); //���݂̃J�[�\���ʒu����n�܂镶������R���\�[����ʃo�b�t�@�[�ɏ�������   

    /*  �o�b�t�@�̎Q�Ƃ����Z�b�g  */
    mNowBuffer_height = 0;
    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        mNowBuffer_width[i] = 0;
    }
    
    // �X�N���[���o�b�t�@�[��������
    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        for (int j = 0; j < MAX_WIDTH; j++)
        {
            mScreenBuffer[i][j].Char.UnicodeChar = 0;
        }
    }
}

// �n���h����Ԃ�
HANDLE ScreenBuffer::getHandle()
{
    return mHandle;
}


//�@�f�X�g���N�^
ScreenBuffer::~ScreenBuffer()
{
    // �X�N���[���o�b�t�@�����
    CloseHandle(mHandle);
    mHandle = NULL;

    fclose(fp);

}
