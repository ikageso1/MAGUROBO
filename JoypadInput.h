#pragma once
#include "Input.h"

class JoypadInput:public Input{
private:
	int oldButtonInput;			/**< �O��̃{�^���̓��͏�� */
	int nowButtonInput;			/**< �{�^���̓��͏�� */
	int edgeButtonInput;		/**< ������͂���āA�O����͂���Ă��Ȃ��{�^�� */
	DINPUT_JOYSTATE input ;		/**< �X�e�B�b�N�̓��͏�� */
	DINPUT_JOYSTATE oldInput ;	/**< �O�̃X�e�B�b�N�̓��͏�� */
	int doubleRightTimer;		/**< �N�C�b�N��ݗp�^�C�}�i�E) */
	bool doubleRightBack;		/**< ���߂������ǂ���(�E */
	int doubleLeftTimer;		/**< �N�C�b�N��ݗp�^�C�}�i�� */
	bool doubleLeftBack;		/**< ���߂������ǂ���(��) */
	
public:
	JoypadInput();				// �R���X�g���N�^
	void update();				// �X�V
	bool isEdgeStartButton();
	int isLeft();
	int isRight();
	int isUp();
	int isDown();
	int isEdgeUp();
	int isEdgeDown();
	int isLeft2();
	int isRight2();
	int isUp2();
	int isDown2();
	bool isPushed2();
	bool isDoubleRight();
	bool isDoubleLeft();
	bool isFire();
	bool isJump();
	bool isEject();
	bool isEdgeFire();
	bool isLockOn();
	bool isEdgeLockON();
	~JoypadInput();				// �f�X�g���N�^
};