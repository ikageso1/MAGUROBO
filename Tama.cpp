#include "Tama.h"
#include "Stage.h"
#include "Character.h"



Tama::Tama(VECTOR playerPosition,float HAngle,float VAngle){
	isAlive = true;

	//10月1日　追加
	timer = 0;//タイマーを0に設定
}

//9月30日　追加
//デストラクタ
Tama::~Tama(){
	
}


void Tama::Draw(){
	DrawSphere3D(position,r,20,GetColor(255,0,0),0,TRUE);
}

bool Tama::CollCheck(Character *chara){
	HitBox hitbox = chara->GetHitBox();
	VECTOR front = VAdd(hitbox.position,hitbox.front);
	VECTOR back = VAdd(hitbox.position,hitbox.back);
	
	if(HitCheck_Sphere_Capsule(position,r,front,back,hitbox.r)){
		isAlive = false;
		return true;
	}else{
		return false;
	}
}

bool Tama::GetAlive(){
	return isAlive;
}