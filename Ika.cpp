#include "Ika.h"
#include "IkaAI.h"
#include "IkaWeapon.h"

Ika::Ika(float x,float y, float z)
:Enemy(x,y,z){
	// 初期座標は原点
	ModelHandle = MV1LoadModel("chara/ika/ika.mv1");

	HIT_WIDTH = 2.f;
	ENUM_DEFAULT_SIZE = 580.f;
	HIT_HORIZON = 1.f;
	HIT_HEIGHT = 4.f;
	JUMP_POWER	= 5.0f;
	// 速度の調整（おそくする
	speed = 0.2f;

	MaxHP = 3000;
	HP = MaxHP;

	AngleV = 0;

	// ↑のベクトル
	UpMoveVec = VGet(0.0f,0.0f,1.0f);

	// ←のベクトル
	LeftMoveVec = VGet(1.0f,0.0f,0.0f);

	ai = new IkaAI();
	weapon = new IkaWeapon();

	// 当り判定BOXの設定
	VECTOR hitbox_front = VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle ));
	VECTOR hitbox_back = VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle ));
	hitbox.setHitBox( hitbox_front, hitbox_back, HIT_WIDTH, HIT_HEIGHT );
	name = "いか";
}


void Ika::Rotate(){
	// モデルの角度を更新
	Angle += 0.02f* GetRand(10);
	// ある方向からある方向の差が１８０度以上になることは無いので
	// 差の値が１８０度以上になっていたら修正する
	if( Angle < -DX_PI_F )
	{
		Angle += DX_TWO_PI_F ;
	}
	else
		if( Angle > DX_PI_F )
		{
			Angle -= DX_TWO_PI_F ;
		}

	MV1SetRotationXYZ( ModelHandle, VGet( 0.0f, Angle + DX_PI_F, 0.0f ) ) ;
}