#include "TraceEnemy.h"
#include <math.h>
#include "Stage.h"
#include "TraceAI.h"
#include "NoWeapon.h"
#include "Player.h"

#define GRAVITY 0.3f		// 重力

// コンストラクタ
TraceEnemy::TraceEnemy(float x,float y, float z,Player *player)
:Enemy(x,y,z){
	// 初期座標は原点
	ModelHandle = MV1LoadModel("chara/1.mv1");

	HIT_WIDTH = 4.f;
	ENUM_DEFAULT_SIZE = 580.f;
	HIT_HORIZON = 3.f;
	HIT_HEIGHT = 8.f;
	JUMP_POWER	= 5.0f;
	// 速度の調整（おそくする
	speed = 0.2f;

	
	MaxHP = 400;
	HP = MaxHP;


	// ↑のベクトル
	UpMoveVec = VGet(1.0f,0.0f,0.0f);

	// ←のベクトル
	LeftMoveVec = VGet(0.0f,0.0f,1.0f);

	ai = new TraceAI(player,this);
	weapon = new NoWeapon();

	// 当り判定BOXの設定
	VECTOR hitbox_front = VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle ));
	VECTOR hitbox_back = VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle ));
	hitbox.setHitBox( hitbox_front, hitbox_back, HIT_WIDTH, HIT_HEIGHT );

	name = "中マグロ";
	this->player = player;
}

void TraceEnemy::SetDirection()
{
	VECTOR pPos = player->GetPosition();
	float takasa = pPos.y - Position.y;
	float teihen = pow(pPos.x - Position.x,2) + pow(pPos.z - Position.z ,2);
	teihen = sqrt(teihen);
	AngleV = -atan(takasa/teihen)*3.14/2.f;
	// AngleV *= DX_PI_F/180.f;
}


void TraceEnemy::Move(){
	Character::Move();
	SetDirection();
	
}