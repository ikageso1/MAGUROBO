#include "DxLib.h"
#include "Enemy.h"
#include "NoWeapon.h"

Enemy::Enemy(float x,float y, float z)
:Character(x,y,z){
	isDraw = false;
	name = "小マグロ";
}

// プレイヤーの移動方向のベクトルを算出
void Enemy::SetDirection(VECTOR target,VECTOR pos){
	// 方向ボタン「↑」を押したときのプレイヤーの移動ベクトルはカメラの視線方向からＹ成分を抜いたもの
	UpMoveVec =  VGet( 1.0f, 0.0f ,0.0f );
	UpMoveVec.y = 0.0f ;
	// 方向ボタン「←」を押したときのプレイヤーの移動ベクトルは上を押したときの方向ベクトルとＹ軸のプラス方向のベクトルに垂直な方向
	LeftMoveVec = VCross( UpMoveVec, VGet( 0.0f, 1.0f, 0.0f ) ) ;

	// 二つのベクトルを正規化( ベクトルの長さを１．０にすること )
	UpMoveVec = VNorm( UpMoveVec ) ;
	LeftMoveVec = VNorm( LeftMoveVec ) ;
}

void Enemy::Draw(){
	if(isDraw){
		// 名前表示
		DrawFormatString(400,400,GetColor(255,255,255),"%s",name.c_str());
		// HPゲージ描画
		DrawBox(400,420,400+((float)HP/(float)MaxHP)*200,430,GetColor(255,0,0),1);
	}
	// 当り判定描画
	// DrawCapsule3D(hitbox_front,hitbox_back,hitbox.r,0,GetColor(255,0,0),0,TRUE);
	Character::Draw();
}

void Enemy::SetisDraw(){
	isDraw = true;
}

void Enemy::ResetisDraw(){
	isDraw = false;
}