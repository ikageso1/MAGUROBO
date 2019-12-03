#include "NoWeapon.h"
#include "NormalTama.h"

NoWeapon::NoWeapon(){
	damage = 100;
	timer = 400;
	nowTime = 0;
	oldTime = 0;
}

void NoWeapon::CreateTama(VECTOR playerPos,float AngleH,float AngleV,std::list<Tama*> *tama){
	nowTime = GetNowCount();
	if(nowTime - oldTime > timer){
		oldTime = nowTime;
		tama->push_back(new NormalTama(playerPos,AngleH,AngleV));

	}
}

void NoWeapon::Draw(){
}