#pragma once
#include "Input.h"

class KeyBoardInput:public Input{
	private:
	char NowInput[256];			/**< ���݉����ꂽ�{�^�� */
	char OldInput[256];			/**< �O�񉟂��ꂽ�{�^�� */
	char EdgeInput[256];		/**< �O�񉟂���Ă��Ȃ��āA���񉟂��ꂽ�{�^�� */

public:
	/**
	* �R���X�g���N�^�@�L�[�{�[�h�̓��͏�Ԃ̏�����
	*/
	KeyBoardInput();				// �R���X�g���N�^
	void update();				// �X�V
	bool isEdgeStartButton();
	int isLeft();
	int isRight();
	int isUp();
	int isEdgeUp();
	int isDown();
	int isEdgeDown();
	int isLeft2(); //�J�����ړ�
	int isRight2();//�J�����ړ�
	int isUp2();//�J�����ړ�
	int isDown2();//�J�����ړ�
	bool isDoubleRight();
	bool isDoubleLeft();
	bool isFire();
	bool isJump();
	bool isEject();
	bool isPushed2();
	bool isEdgeFire();
	bool isLockOn();
	bool isEdgeLockON();
	/**
	* �f�X�g���N�^�@���ɂ����Ăˁ[
	*/
	~KeyBoardInput();	
};