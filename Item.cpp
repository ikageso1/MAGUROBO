#include "Item.h"
#include "Character.h"

Item::Item(float x,float y,float z){
	position = VGet(x,y,z);
	isAvailable = true;
	angleSpeed = 0.05f;
	Angle = 0.f;
	r = 8.0f;
}

bool Item::GetAvailavle(){
	return isAvailable;
}

void Item::Rotate(){

	Angle += angleSpeed ;
	if( Angle > DX_TWO_PI_F )
	{
		Angle = 0.0f ;
	}
	// ƒ‚ƒfƒ‹‚ÌŠp“x‚ðXV
	MV1SetRotationXYZ( ModelHandle, VGet( 0.0f, Angle, 0.0f ) ) ;
}


bool Item::CollCheck(Character *chara){
	HitBox hitbox = chara->GetHitBox();
	// ‰ñ“]
	VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
	VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
	// ˆÚ“®
	hitbox_front = VAdd(hitbox.position,hitbox_front);	
	hitbox_back = VAdd(hitbox.position,hitbox_back);	
	if(HitCheck_Sphere_Capsule(position,r,hitbox_front,hitbox_back,hitbox.r)){
		isAvailable = false;
		return true;
	}
	return false;
}

void Item::Draw(){
	if(isAvailable)
		MV1DrawModel(ModelHandle);
	// DrawSphere3D(position,r,0,GetColor(0,255,0),0,1);
}