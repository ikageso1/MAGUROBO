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

#define GRAVITY 0.3f		// 重力


// コンストラクタ
Player::Player(float x,float y,float z)
	:Character(x,y,z){
	// 初期座標は原点
 
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

	// 当り判定BOXの設定
	VECTOR hitbox_front = VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle ));
	VECTOR hitbox_back = VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle ));
	hitbox.setHitBox( hitbox_front, hitbox_back, HIT_WIDTH, HIT_HEIGHT );

	weapon = new NoWeapon();

	SetName("マグロボ");
}

void Player::SetInputAI(Input* input){
	ai = new PlayerAI(input);
}


// デストラクタ
Player::~Player(){

}

void Player::Kaihuku(int cure){
	HP += cure;
	if(HP > MaxHP){
		HP = MaxHP;
	}
}


// プレイヤーの移動方向のベクトルを算出
void Player::SetMoveVec(VECTOR target,VECTOR pos){
	// 方向ボタン「↑」を押したときのプレイヤーの移動ベクトルはカメラの視線方向からＹ成分を抜いたもの
	UpMoveVec = VSub( target, pos ) ;
	UpMoveVec.y = 0.0f ;
	// 方向ボタン「←」を押したときのプレイヤーの移動ベクトルは上を押したときの方向ベクトルとＹ軸のプラス方向のベクトルに垂直な方向
	LeftMoveVec = VCross( UpMoveVec, VGet( 0.0f, 1.0f, 0.0f ) ) ;

	// 二つのベクトルを正規化( ベクトルの長さを１．０にすること )
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
	
	// 照準
	DrawGraph(270,90,AimGraph,TRUE);
	// 名前表示
	DrawFormatString(10,10,GetColor(255,255,255),"%s",name.c_str());
	// HPゲージ描画
	DrawBox(10,30,10+((float)HP/(float)MaxHP)*200,40,GetColor(255,0,0),1);
	// 武器情報描画
	weapon->Draw();
	if(isJet>0){
		DrawFormatString(10,70,GetColor(255,255,255),"燃料:%d",isJet);
	}

	// 回転
	VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
	VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
	// 移動
	hitbox_front = VAdd(Position,hitbox_front);	
	hitbox_back = VAdd(Position,hitbox_back);	

	// 当り判定描画
	//DrawCapsule3D(hitbox_front,hitbox_back,hitbox.r,0,GetColor(255,0,0),0,TRUE);

	// 弾を描画
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end(); ite++){
		if((*ite)->GetAlive())
			(*ite)->Draw();
	}
	// デバック用
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