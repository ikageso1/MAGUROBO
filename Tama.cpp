#include "Tama.h"
#include "Stage.h"
#include "Character.h"



Tama::Tama(VECTOR playerPosition,float HAngle,float VAngle){
	isAlive = true;

	//10��1���@�ǉ�
	timer = 0;//�^�C�}�[��0�ɐݒ�
}

//9��30���@�ǉ�
//�f�X�g���N�^
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