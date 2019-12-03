#include "DxLib.h"
#include "JoypadInput.h"

#define DOUBLE_TIMER 20
// ���ł���Ɣ��肷�鋫��
#define LEFT_JUDGE 800

// �R���X�g���N�^
JoypadInput::JoypadInput(){
	oldButtonInput = 0;
	nowButtonInput = 0;

	doubleLeftBack = false;
	doubleLeftTimer = 0;

	doubleRightBack = false;
	doubleRightTimer = 0;
}


JoypadInput::~JoypadInput(){
}

void JoypadInput::update(){
	// �O��̃{�^���̏����i�[
	oldButtonInput = nowButtonInput;
	// ����̃{�^���̏����i�[
	nowButtonInput = GetJoypadInputState(DX_INPUT_PAD1);
	// �G�b�W�����i�[
	edgeButtonInput = nowButtonInput & ~oldButtonInput;
	oldInput = input;
	// ���͏�Ԃ��擾
	GetJoypadDirectInputState( DX_INPUT_PAD1, &input ) ;

}


int JoypadInput::isLeft(){
	return input.X > 0 ? input.X : 0; 
}

int JoypadInput::isRight(){
	return input.X < 0 ? -input.X : 0; 
}
int JoypadInput::isUp(){
	return input.Y < 0 ? -input.Y : 0;
}
int JoypadInput::isEdgeUp(){
	return !(oldInput.Y < 0) && input.Y < 0 ? -input.Y : 0;
}
int JoypadInput::isDown(){
	return input.Y > 0 ? input.Y : 0;
}
int JoypadInput::isEdgeDown(){
	return !(oldInput.Y > 0) && input.Y > 0 ? input.Y : 0;
}

int JoypadInput::isLeft2(){
	return input.Z < 0 ? -input.Z : 0; 
}
int JoypadInput::isRight2(){
	return input.Z > 0 ? input.Z : 0; 
}
int JoypadInput::isUp2(){
	return input.Rz > 0 ? input.Rz : 0;
}
int JoypadInput::isDown2(){
	return input.Rz < 0 ? -input.Rz : 0;
}

bool JoypadInput::isPushed2(){
	return nowButtonInput & PAD_INPUT_12;
}

// �_�u���^�b�v
bool JoypadInput::isDoubleRight(){
	if(isRight() >= LEFT_JUDGE){
		// ����
		if(doubleRightTimer == 0){
			doubleRightTimer++;
		}
		// ����
		else if(doubleRightTimer < DOUBLE_TIMER && doubleRightBack){
			doubleRightTimer = 0;
			doubleRightBack = false;
			return true;
		}
	}
	// �X�e�B�b�N�����ɖ߂���������
	if(doubleRightTimer != 0){
		if(isRight() == 0){
			doubleRightBack = true;
		}
	}
	// �J�E���g�A�b�v
	if(doubleRightTimer != 0){
		doubleRightTimer++;
		if(doubleRightTimer > DOUBLE_TIMER){
			doubleRightTimer = 0;
			doubleRightBack = false;
		}
	}
	return false;
}

bool JoypadInput::isDoubleLeft(){
	if(isLeft() >= LEFT_JUDGE){
		// ����
		if(doubleLeftTimer == 0){
			doubleLeftTimer++;
		}
		// ����
		else if(doubleLeftTimer < DOUBLE_TIMER && doubleLeftBack){
			doubleLeftTimer = 0;
			doubleLeftBack = false;
			return true;
		}
	}
	// �X�e�B�b�N�����ɖ߂���������
	if(doubleLeftTimer != 0){
		if(isLeft() == 0){
			doubleLeftBack = true;
		}
	}
	// �J�E���g�A�b�v
	if(doubleLeftTimer != 0){
		doubleLeftTimer++;
		if(doubleLeftTimer > DOUBLE_TIMER){
			doubleLeftTimer = 0;
			doubleLeftBack = false;
		}
	}
	return false;
}

// �_�u���^�b�v(���݂�X�L�[)
bool JoypadInput::isFire(){
	return nowButtonInput & PAD_INPUT_6;
}


// �X�^�[�g�{�^���擾(����̂݉�����Ă�����)
bool JoypadInput::isEdgeStartButton(){
	return edgeButtonInput & PAD_INPUT_10;
}


bool JoypadInput::isJump(){
	return nowButtonInput & PAD_INPUT_2;
}

bool JoypadInput::isEject(){
	return nowButtonInput & PAD_INPUT_1;
}

bool JoypadInput::isEdgeFire(){
	return edgeButtonInput & PAD_INPUT_3;
}

bool JoypadInput::isLockOn(){
	return nowButtonInput & PAD_INPUT_5;
}


bool JoypadInput::isEdgeLockON(){
	return edgeButtonInput & PAD_INPUT_5;
}
