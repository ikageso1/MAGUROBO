#include "NormalEnemy.h"
#include <math.h>
#include "Stage.h"
#include "RandomAI.h"
#include "NoWeapon.h"

#define GRAVITY 0.3f		// �d��

// �R���X�g���N�^
NormalEnemy::NormalEnemy(float x,float y, float z)
:Enemy(x,y,z){
	// �������W�͌��_
	ModelHandle = MV1LoadModel("chara/small.mv1");

	HIT_WIDTH = 2.f;
	ENUM_DEFAULT_SIZE = 580.f;
	HIT_HORIZON = 1.f;
	HIT_HEIGHT = 4.f;
	JUMP_POWER	= 5.0f;
	// ���x�̒����i����������
	speed = 0.2f;

	MaxHP = 300;
	HP = MaxHP;



	// ���̃x�N�g��
	UpMoveVec = VGet(0.0f,0.0f,1.0f);

	// ���̃x�N�g��
	LeftMoveVec = VGet(1.0f,0.0f,0.0f);

	ai = new RandomAI();
	weapon = new NoWeapon();

	// ���蔻��BOX�̐ݒ�
	VECTOR hitbox_front = VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle ));
	VECTOR hitbox_back = VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle ));
	hitbox.setHitBox( hitbox_front, hitbox_back, HIT_WIDTH, HIT_HEIGHT );
}

// �f�X�g���N�^
Enemy::~Enemy(){

}

