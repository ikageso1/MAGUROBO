#pragma once
#include "AI.h"

class IkaAI :public AI{
private:
	int moveTimer;
	Direction dire;
public:
	IkaAI();
	Direction decideMove();
	bool doFire();
};