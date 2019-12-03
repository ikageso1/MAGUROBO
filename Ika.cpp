#include "Ika.h"
#include "IkaAI.h"
#include "IkaWeapon.h"

Ika::Ika(float x,float y, float z)
:Enemy(x,y,z){
	// �������W�͌��_
	ModelHandle = MV1LoadModel("chara/ika/ika.mv1");

	HIT_WIDTH = 2.f;
	ENUM_DEFAULT_SIZE = 580.f;
	HIT_HORIZON = 1.f;
	HIT_HEIGHT = 4.f;
	JUMP_POWER	= 5.0f;
	// ���x�̒����i����������
	speed = 0.2f;

	MaxHP = 3000;
	HP = MaxHP;

	AngleV = 0;

	// ���̃x�N�g��
	UpMoveVec = VGet(0.0f,0.0f,1.0f);

	// ���̃x�N�g��
	LeftMoveVec = VGet(1.0f,0.0f,0.0f);

	ai = new IkaAI();
	weapon = new IkaWeapon();

	// ���蔻��BOX�̐ݒ�
	VECTOR hitbox_front = VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle ));
	VECTOR hitbox_back = VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle ));
	hitbox.setHitBox( hitbox_front, hitbox_back, HIT_WIDTH, HIT_HEIGHT );
	name = "����";
}


void Ika::Rotate(){
	// ���f���̊p�x���X�V
	Angle += 0.02f* GetRand(10);
	// ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
	// ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
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