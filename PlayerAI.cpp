#include "PlayerAI.h"
#include "Character.h"
#include "Input.h"


PlayerAI::PlayerAI(Input *input){
	this->input = input;
}

Direction PlayerAI::decideMove(){
	Direction retDirection;
	// 方向ボタン「←」が入力されたらカメラの見ている方向から見て左方向に移動する
	if( input->isLeft()  )
	{
		retDirection.left =  input->isLeft();
	}
	// 方向ボタン「→」が入力されたらカメラの見ている方向から見て右方向に移動する
	else if( input->isRight() )
	{
		retDirection.right = input->isRight();
	}

	// 方向ボタン「↑」が入力されたらカメラの見ている方向に移動する
	if( input->isUp()    )
	{
		retDirection.front = input->isUp();
	}
	// 方向ボタン「↓」が入力されたらカメラの方向に移動する
	else if( input->isDown() )
	{
		retDirection.back = input->isDown();
	}

	// プレイヤーの状態が「ジャンプ」ではなく、且つジャンプボタンが押されていたらジャンプする
	if( input->isJump()  )
	{
		retDirection.jump=true;
	}else{
		retDirection.jump = false;
	}
	if( input->isDoubleLeft()){
		retDirection.roleLeft = true;
	}else{
		retDirection.roleLeft = false;
	}
	if( input->isDoubleRight()){
		retDirection.roleRight = true;
	}else{
		retDirection.roleRight = false;
	}


	return retDirection;
}

bool PlayerAI::doFire(){
	return input->isFire();
}