#include "M95Weapon.h"
#include "M95Tama.h"
#include "DxLib.h"

M95Weapon::M95Weapon(){
	tamaNum = 100;
	damage = 100;
}

void M95Weapon::CreateTama(VECTOR playerPos,float AngleH,float AngleV,std::list<Tama*> *tama){
	if(tamaNum>0){
		tama->push_back(new M95Tama(playerPos,AngleH,AngleV,true));	
		tama->push_back(new M95Tama(playerPos,AngleH,AngleV,false));
		tamaNum -= 2;
	}
}

void M95Weapon::Draw(){
	DrawFormatString(10,70,GetColor(255,255,255),"écíeêî:%d",tamaNum);
}