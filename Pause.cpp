#include "Pause.h"
#include "Input.h"
#include "DxLib.h"

// �R���X�g���N�^
Pause::Pause(){
	isFinishFlag = false;
}

void Pause::Process(Input *input){
	if(input->isEdgeStartButton()){
		isFinishFlag = true;
	}
	DrawFormatString(200,200,GetColor(255,255,255),"�ς���");
}

bool Pause::isFinish(){
	if(isFinishFlag){
		isFinishFlag = false;
		return true;
	}else{
		return false;
	}
}