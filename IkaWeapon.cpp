#include "IkaWeapon.h"
#include "IkaTama.h"
#include "DxLib.h"

IkaWeapon::IkaWeapon(){
	damage = 100;
}

void IkaWeapon::CreateTama(VECTOR playerPos,float AngleH,float AngleV,std::list<Tama*> *tama){
	tama->push_back(new IkaTama(playerPos,AngleH,AngleV,true));	
	tama->push_back(new IkaTama(playerPos,AngleH,AngleV,false));
}

void IkaWeapon::Draw(){
}