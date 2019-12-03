#include "DxLib.h"
#include "Enemy.h"
#include "NoWeapon.h"

Enemy::Enemy(float x,float y, float z)
:Character(x,y,z){
	isDraw = false;
	name = "���}�O��";
}

// �v���C���[�̈ړ������̃x�N�g�����Z�o
void Enemy::SetDirection(VECTOR target,VECTOR pos){
	// �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���̓J�����̎�����������x�����𔲂�������
	UpMoveVec =  VGet( 1.0f, 0.0f ,0.0f );
	UpMoveVec.y = 0.0f ;
	// �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���͏���������Ƃ��̕����x�N�g���Ƃx���̃v���X�����̃x�N�g���ɐ����ȕ���
	LeftMoveVec = VCross( UpMoveVec, VGet( 0.0f, 1.0f, 0.0f ) ) ;

	// ��̃x�N�g���𐳋K��( �x�N�g���̒������P�D�O�ɂ��邱�� )
	UpMoveVec = VNorm( UpMoveVec ) ;
	LeftMoveVec = VNorm( LeftMoveVec ) ;
}

void Enemy::Draw(){
	if(isDraw){
		// ���O�\��
		DrawFormatString(400,400,GetColor(255,255,255),"%s",name.c_str());
		// HP�Q�[�W�`��
		DrawBox(400,420,400+((float)HP/(float)MaxHP)*200,430,GetColor(255,0,0),1);
	}
	// ���蔻��`��
	// DrawCapsule3D(hitbox_front,hitbox_back,hitbox.r,0,GetColor(255,0,0),0,TRUE);
	Character::Draw();
}

void Enemy::SetisDraw(){
	isDraw = true;
}

void Enemy::ResetisDraw(){
	isDraw = false;
}