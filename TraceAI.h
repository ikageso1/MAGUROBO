#pragma once
#include "AI.h"

class Player;
class Character;
class TraceAI :public AI{
private:
	int moveTimer;
	Direction dire;
	Player* player;
	Character *myChara;
public:
	TraceAI(Player* player,Character *myChara);
	Direction decideMove();
	bool doFire();
};