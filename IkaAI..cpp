#include "IkaAI.h"
#include "DxLib.h"


IkaAI::IkaAI(){
	dire.front = false;
	dire.back = false;
	dire.jump = false;
	dire.right = false;
	dire.left = false;
}

Direction IkaAI::decideMove(){

	// 0:�� 1:��  2:��  3:��
	return dire;
}

bool IkaAI::doFire(){
	// 4�Ԃ�̂���
	if(!GetRand(1)){
		return true;
	}
	return false;
}

