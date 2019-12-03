#pragma once
#include "Tama.h"

class NormalTama:public Tama{
public:
	NormalTama(VECTOR playerPosition,float HAngle,float VAngle);
	void Move(Stage *stg);
};