#pragma once
#include "AI.h"

class Input;
class PlayerAI:public AI{
private:
	Input *input;
public:
	PlayerAI(Input *input);
	Direction decideMove();
	bool doFire();
};