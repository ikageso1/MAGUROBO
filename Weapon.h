#pragma once
#include "DxLib.h"
#include <list>

class Character;
class Tama;
class Weapon{
protected:
	int timer;
	int damage;
public:
	Weapon();
	int GetDamage();
	virtual void CreateTama(VECTOR playerPos,float AngleH,float AngleV,std::list<Tama*> *tama) = 0;
	virtual void Draw() = 0;
};