#include "DxLib.h"
#include "JoypadInput.h"

#define DOUBLE_TIMER 20
// 左であると判定する境目
#define LEFT_JUDGE 800

// コンストラクタ
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
	// 前回のボタンの情報を格納
	oldButtonInput = nowButtonInput;
	// 今回のボタンの情報を格納
	nowButtonInput = GetJoypadInputState(DX_INPUT_PAD1);
	// エッジ情報を格納
	edgeButtonInput = nowButtonInput & ~oldButtonInput;
	oldInput = input;
	// 入力状態を取得
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

// ダブルタップ
bool JoypadInput::isDoubleRight(){
	if(isRight() >= LEFT_JUDGE){
		// 一回目
		if(doubleRightTimer == 0){
			doubleRightTimer++;
		}
		// 二回目
		else if(doubleRightTimer < DOUBLE_TIMER && doubleRightBack){
			doubleRightTimer = 0;
			doubleRightBack = false;
			return true;
		}
	}
	// スティックを元に戻したか判定
	if(doubleRightTimer != 0){
		if(isRight() == 0){
			doubleRightBack = true;
		}
	}
	// カウントアップ
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
		// 一回目
		if(doubleLeftTimer == 0){
			doubleLeftTimer++;
		}
		// 二回目
		else if(doubleLeftTimer < DOUBLE_TIMER && doubleLeftBack){
			doubleLeftTimer = 0;
			doubleLeftBack = false;
			return true;
		}
	}
	// スティックを元に戻したか判定
	if(doubleLeftTimer != 0){
		if(isLeft() == 0){
			doubleLeftBack = true;
		}
	}
	// カウントアップ
	if(doubleLeftTimer != 0){
		doubleLeftTimer++;
		if(doubleLeftTimer > DOUBLE_TIMER){
			doubleLeftTimer = 0;
			doubleLeftBack = false;
		}
	}
	return false;
}

// ダブルタップ(現在はXキー)
bool JoypadInput::isFire(){
	return nowButtonInput & PAD_INPUT_6;
}


// スタートボタン取得(今回のみ押されていたか)
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
