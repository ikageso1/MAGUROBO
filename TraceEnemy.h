#pragma once
#include "Enemy.h"

class Player;

class TraceEnemy:public Enemy{
	Player* player;
public:
	TraceEnemy(float x,float y, float z,Player *player);
	void SetDirection();
	void Move();
};