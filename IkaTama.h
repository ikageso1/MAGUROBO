#pragma once
#include "DxLib.h"
#include "Tama.h"


class IkaTama:public Tama{
public:
	IkaTama(VECTOR playerPosition,float HAngle,float VAngle,bool isRight);
	void Move(Stage *stg);
};