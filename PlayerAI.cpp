#include "PlayerAI.h"
#include "Character.h"
#include "Input.h"


PlayerAI::PlayerAI(Input *input){
	this->input = input;
}

Direction PlayerAI::decideMove(){
	Direction retDirection;
	// �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�č������Ɉړ�����
	if( input->isLeft()  )
	{
		retDirection.left =  input->isLeft();
	}
	// �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�ĉE�����Ɉړ�����
	else if( input->isRight() )
	{
		retDirection.right = input->isRight();
	}

	// �����{�^���u���v�����͂��ꂽ��J�����̌��Ă�������Ɉړ�����
	if( input->isUp()    )
	{
		retDirection.front = input->isUp();
	}
	// �����{�^���u���v�����͂��ꂽ��J�����̕����Ɉړ�����
	else if( input->isDown() )
	{
		retDirection.back = input->isDown();
	}

	// �v���C���[�̏�Ԃ��u�W�����v�v�ł͂Ȃ��A���W�����v�{�^����������Ă�����W�����v����
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