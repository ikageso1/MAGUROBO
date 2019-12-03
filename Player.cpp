#include "Player.h"
#include <math.h>
#include "Stage.h"
#include "Input.h"
#include "RandomAI.h"
#include "PlayerAI.h"
#include "NoWeapon.h"
#include "M95Weapon.h"
#include <string>
#include "Enemy.h"

#define GRAVITY 0.3f		// �d��


// �R���X�g���N�^
Player::Player(float x,float y,float z)
	:Character(x,y,z){
	// �������W�͌��_
 
	//ModelHandle = MV1LoadModel("chara/small.mv1");
	// ModelHandle = MV1LoadModel("chara/4.pmx");
	NoWeaponModel = MV1LoadModel("chara/1.mv1");
	JetModel = MV1LoadModel("chara/52.mqo");
	M95WeaponModel = MV1LoadModel("chara/2.pmx");
	ModelHandle = NoWeaponModel;


	HIT_WIDTH = 4.f;
	ENUM_DEFAULT_SIZE = 580.f;
	HIT_HORIZON = 3.f;
	HIT_HEIGHT = 8.f;
	JUMP_POWER	= 5.0f;

	MaxHP = 1000;
	HP = MaxHP;
	speed = 2.0f;

	FireSound = LoadSoundMem("sound/gun-fire03.mp3");
	JumpSound = LoadSoundMem("sound/jump02.mp3");
	DamageSound = LoadSoundMem("sound/hit02.mp3");
	AimGraph = LoadGraph("aim/aim.png");

	// ���蔻��BOX�̐ݒ�
	VECTOR hitbox_front = VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle ));
	VECTOR hitbox_back = VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle ));
	hitbox.setHitBox( hitbox_front, hitbox_back, HIT_WIDTH, HIT_HEIGHT );

	weapon = new NoWeapon();

	SetName("�}�O���{");
}

void Player::SetInputAI(Input* input){
	ai = new PlayerAI(input);
}


// �f�X�g���N�^
Player::~Player(){

}

void Player::Kaihuku(int cure){
	HP += cure;
	if(HP > MaxHP){
		HP = MaxHP;
	}
}


// �v���C���[�̈ړ������̃x�N�g�����Z�o
void Player::SetMoveVec(VECTOR target,VECTOR pos){
	// �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���̓J�����̎�����������x�����𔲂�������
	UpMoveVec = VSub( target, pos ) ;
	UpMoveVec.y = 0.0f ;
	// �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���͏���������Ƃ��̕����x�N�g���Ƃx���̃v���X�����̃x�N�g���ɐ����ȕ���
	LeftMoveVec = VCross( UpMoveVec, VGet( 0.0f, 1.0f, 0.0f ) ) ;

	// ��̃x�N�g���𐳋K��( �x�N�g���̒������P�D�O�ɂ��邱�� )
	UpMoveVec = VNorm( UpMoveVec ) ;
	LeftMoveVec = VNorm( LeftMoveVec ) ;
}


void Player::SetDirection(float AngleV){
	this->AngleV = -AngleV - 0.38f;
	Direction = VNorm(UpMoveVec);
}


void Player::Draw(){
	MV1DrawModel(ModelHandle);
	// DrawFormatString(100,100,GetColor(255,255,255),"%f,%f",Position.x,Position.z);
	
	// �Ə�
	DrawGraph(270,90,AimGraph,TRUE);
	// ���O�\��
	DrawFormatString(10,10,GetColor(255,255,255),"%s",name.c_str());
	// HP�Q�[�W�`��
	DrawBox(10,30,10+((float)HP/(float)MaxHP)*200,40,GetColor(255,0,0),1);
	// ������`��
	weapon->Draw();
	if(isJet>0){
		DrawFormatString(10,70,GetColor(255,255,255),"�R��:%d",isJet);
	}

	// ��]
	VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
	VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
	// �ړ�
	hitbox_front = VAdd(Position,hitbox_front);	
	hitbox_back = VAdd(Position,hitbox_back);	

	// ���蔻��`��
	//DrawCapsule3D(hitbox_front,hitbox_back,hitbox.r,0,GetColor(255,0,0),0,TRUE);

	// �e��`��
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end(); ite++){
		if((*ite)->GetAlive())
			(*ite)->Draw();
	}
	// �f�o�b�N�p
	//DrawFormatString(100,300,GetColor(255,255,255),"%f:%f:%f",Position.x,Position.y,Position.z);
}

void Player::Eject(){
	if(ModelHandle != NoWeaponModel){
		ModelHandle = NoWeaponModel;
		isJet = 0;
		SetWeapon(new NoWeapon());
	}
}



void Player::ChangeModel(std::string name){
	if(name == "NoWeapon"){
		ModelHandle = NoWeaponModel;
	}else if(name == "M95"){
		ModelHandle = M95WeaponModel;
	}else if(name == "Jet"){
		ModelHandle = JetModel;
	}
}

void Player::SetJetMode(){
	isJet = 500;
	SetWeapon(new NoWeapon());
}

void Player::Damage(int damage){
	PlaySoundMem(DamageSound,DX_PLAYTYPE_BACK);
	Character::Damage(damage);
}

void Player::Attack(){
	if(isFire){
		PlaySoundMem(FireSound,DX_PLAYTYPE_BACK);
	}
	Character::Attack();
}

void Player::Jump(){
	PlaySoundMem(JumpSound,DX_PLAYTYPE_BACK);
	Character::Jump();
}