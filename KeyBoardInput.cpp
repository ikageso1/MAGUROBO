#include "DxLib.h"
#include "KeyBoardInput.h"

KeyBoardInput::KeyBoardInput(){
	for(int i=0; i < 256; ++i){
	NowInput[i] = 0;	
	OldInput[i] = 0;
	EdgeInput[i] = 0;
	}
}
KeyBoardInput::~KeyBoardInput(){
}

void KeyBoardInput::update(){
	//OldInput = NowInput;
	for(int i = 0; i < 256; i++){
		OldInput[i]=NowInput[i];
	}
	GetHitKeyStateAll(NowInput);
	//NowInput = GetJoypadInputState( DX_INPUT_KEY_PAD1 );
	for(int i = 0; i < 256; i++){
		EdgeInput[i] = NowInput[i] & ~OldInput[i];
	}
	//EdgeInput = NowInput & ~OldInput;
	//DrawFormatString(200,200,GetColor(255,100,100),"%d",joypad.Z);
}

int KeyBoardInput::isLeft(){
	return NowInput[KEY_INPUT_D] == 1 ? 1000 : 0;
}



int KeyBoardInput::isRight(){
	return NowInput[KEY_INPUT_A] == 1 ? 1000 : 0;
	//return KEY_INPUT_RIGHT ? 1 : 0;
}

int KeyBoardInput::isUp(){
	return NowInput[KEY_INPUT_W] == 1 ? 1000 : 0;
	//return KEY_INPUT_UP ? 1 : 0;
}
int KeyBoardInput::isEdgeUp(){
	return EdgeInput[KEY_INPUT_W];
}
int KeyBoardInput::isDown(){
	return NowInput[KEY_INPUT_S] == 1 ? 1000 : 0;
	//return KEY_INPUT_DOWN ? 1 : 0;
}
int KeyBoardInput::isEdgeDown(){
	return EdgeInput[KEY_INPUT_S];
}

int KeyBoardInput::isLeft2(){
	return NowInput[KEY_INPUT_LEFT] == 1 ? 1 : 0;
	//return input.Z < 0 ? -input.Z : 0; 
}

int KeyBoardInput::isRight2(){
	return NowInput[KEY_INPUT_RIGHT] == 1 ? 1 : 0;
	//return input.Z > 0 ? input.Z : 0; 
}

bool KeyBoardInput::isPushed2(){
	return NowInput[KEY_INPUT_R];
}

int KeyBoardInput::isUp2(){
	return NowInput[KEY_INPUT_UP] == 1 ? 1 : 0;
	//return input.Rz > 0 ? input.Rz : 0;
}
int KeyBoardInput::isDown2(){
	return NowInput[KEY_INPUT_DOWN] == 1 ? 1 : 0;
	//return input.Rz < 0 ? -input.Rz : 0;
	return 0;
}


// スタートボタン取得(今回のみ押されていたか)
bool KeyBoardInput::isEdgeStartButton(){
	// キーボードの場合はスペースとなる。
	return EdgeInput[KEY_INPUT_SPACE];
}

// ダブルタップ(現在はXキー)
//2014/10/08 キーボードでは　Qキー　で
bool KeyBoardInput::isDoubleLeft(){
	return NowInput[KEY_INPUT_E] == 1 ? 1 : 0;
	//return NowInput & PAD_INPUT_2;
}

//2014/10/08 キーボードでは　Eキー　で
bool KeyBoardInput::isDoubleRight(){
	return NowInput[KEY_INPUT_Q] == 1 ? 1 : 0;
}

// ダブルタップ(現在はXキー)
//2014/10/08 キーボードでは　左SHIFTキー　で
bool KeyBoardInput::isFire(){
	//return NowInput[KEY_INPUT_LSHIFT] == 1 ? 1 : 0;
	return NowInput[KEY_INPUT_LSHIFT];
	//return NowInput & PAD_INPUT_3;
}

bool KeyBoardInput::isJump(){
	return NowInput[KEY_INPUT_C] == 1 ? 1 : 0;
}

bool KeyBoardInput::isEject(){
	return NowInput[KEY_INPUT_F];
}

bool KeyBoardInput::isEdgeFire(){
	return EdgeInput[KEY_INPUT_LSHIFT];
}

bool KeyBoardInput::isLockOn(){
	return NowInput[KEY_INPUT_RSHIFT];
}

bool KeyBoardInput::isEdgeLockON(){
	return EdgeInput[KEY_INPUT_RSHIFT];
}