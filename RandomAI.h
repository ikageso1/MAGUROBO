#pragma once
#include "AI.h"

class RandomAI :public AI{
private:
	int moveTimer;
	Direction dire;
public:
	RandomAI();
	Direction decideMove();
	bool doFire();
};