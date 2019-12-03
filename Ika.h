#pragma once
#include "Enemy.h"

class Ika:public Enemy{
public:
	Ika(float x,float y, float z);
	void Rotate();
};