#pragma once
#include "DxLib.h"
#include "Tama.h"


class M95Tama:public Tama{
public:
	M95Tama(VECTOR playerPosition,float HAngle,float VAngle,bool isRight);
	void Move(Stage *stg);
};