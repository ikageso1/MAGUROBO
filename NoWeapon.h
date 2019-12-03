#pragma once
#include "Weapon.h"

class NoWeapon:public Weapon{
private:
	int nowTime;
	int oldTime;
public:
	NoWeapon();
	void CreateTama(VECTOR playerPos,float AngleH,float AngleV,std::list<Tama*> *tama);
	void Draw();
};