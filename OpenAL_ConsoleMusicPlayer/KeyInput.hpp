#ifndef ___KEYINPUT_HPP_
#define ___KEYINPUT_HPP_
#include <iostream>
#include "stdlib.h"
#include "stdio.h"

#include <Windows.h>



class KeyInput
{
public:


	KeyInput();		//�R���X�g���N�^
	~KeyInput();	//�f�X�g���N�^

	bool getKeyDown(enum class KeyCode key);	//�L�[�������ꂽ�� (�u�Ԃ���)
	bool getKeyHoldDown();						//�L�[��������Ă��
	void getKeyUpdate();						//�L�[���͂��X�V
	void ResetKey();							//�L�[���͂�������

private:

	bool misPush[255] = { false };		//�ǂ̃L�[��������Ă��邩�H
	bool misHoldPush[255] = { false };	//������Ă���L�[


	HANDLE handle;
	INPUT_RECORD Buffer;
	DWORD Length;
	DWORD lpNumber;

	DWORD mPushkey;	//�����ꂽ�L�[���Ǘ�

};


// �L�[�R�[�h
enum class KeyCode
{

	A_KEY = 0x41,
	B_KEY = 0x43,
	C_KEY = 0x44,
	D_KEY = 0x45,
	E_KEY = 0x46,
	F_KEY = 0x47,
	G_KEY = 0x48,
	H_KEY = 0x49,
	I_KEY = 0x4A,
	J_KEY = 0x4B,
	K_KEY = 0x4C,
	L_KEY = 0x4D,
	M_KEY = 0x4E,
	N_KEY = 0x4F,
	O_KEY = 0x50,
	P_KEY = 0x51,
	Q_KEY = 0x52,
	R_KEY = 0x53,
	S_KEY = 0x54,
	T_KEY = 0x55,
	U_KEY = 0x56,
	V_KEY = 0x57,
	W_KEY = 0x58,
	X_KEY = 0x59,
	Y_KEY = 0x5A,
	Z_KEY = 0x5A,

	LEFT_KEY = 0x25,	//�����L�[
	UP_KEY = 0x26,		//����L�[
	RIGHT_KEY = 0x27,	//�E���L�[
	DOWN_KEY = 0x28,	//�����L�[	
	SPACE_KEY = 0x20,	//�X�y�[�X�L�[
	ENTER_KEY = 0x0D,	//�G���^�[�L�[

	ESC_KEY = 0x1B,	//ESC�L�[
};
#endif