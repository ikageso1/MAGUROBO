#pragma once
#include "Weapon.h"

class M95Weapon:public Weapon{
private:
	int tamaNum;
public:
	M95Weapon();
	void CreateTama(VECTOR playerPos,float AngleH,float AngleV,std::list<Tama*> *tama);
	void Draw();
};