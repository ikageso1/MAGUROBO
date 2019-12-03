#pragma once
#include "Weapon.h"

class IkaWeapon:public Weapon{
public:
	IkaWeapon();
	void CreateTama(VECTOR playerPos,float AngleH,float AngleV,std::list<Tama*> *tama);
	void Draw();
};