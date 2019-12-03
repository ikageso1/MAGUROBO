#include "NormalEnemy.h"
#include <math.h>
#include "Stage.h"
#include "RandomAI.h"
#include "NoWeapon.h"

#define GRAVITY 0.3f		// 重力

// コンストラクタ
NormalEnemy::NormalEnemy(float x,float y, float z)
:Enemy(x,y,z){
	// 初期座標は原点
	ModelHandle = MV1LoadModel("chara/small.mv1");

	HIT_WIDTH = 2.f;
	ENUM_DEFAULT_SIZE = 580.f;
	HIT_HORIZON = 1.f;
	HIT_HEIGHT = 4.f;
	JUMP_POWER	= 5.0f;
	// 速度の調整（おそくする
	speed = 0.2f;

	MaxHP = 300;
	HP = MaxHP;



	// ↑のベクトル
	UpMoveVec = VGet(0.0f,0.0f,1.0f);

	// ←のベクトル
	LeftMoveVec = VGet(1.0f,0.0f,0.0f);

	ai = new RandomAI();
	weapon = new NoWeapon();

	// 当り判定BOXの設定
	VECTOR hitbox_front = VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle ));
	VECTOR hitbox_back = VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle ));
	hitbox.setHitBox( hitbox_front, hitbox_back, HIT_WIDTH, HIT_HEIGHT );
}

// デストラクタ
Enemy::~Enemy(){

}

