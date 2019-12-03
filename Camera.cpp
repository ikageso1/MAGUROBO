#include "Camera.h"
#include "Stage.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"

#define CAMERA_HEIGHT				10.0f
#define CAMERA_WIDTH				20.0f
#define TERGET_HEIGHT				10.0f	
//#define CAMERA_ANGLE_SPEED		0.5f		// 旋回速度
#define CAMERA_ANGLE_SPEED			0.05f		// 旋回速度
#define CAMERA_PLAYER_LENGTH		10.0f		// プレイヤーとの距離
#define CAMERA_COLLISION_SIZE		0.1f		// カメラの当たり判定サイズ
#define LOCK_ON_DISTANCE			30000.f


Camera::Camera(Character *chara){
	// カメラのクリップ距離を設定
	SetCameraNearFar(1.0f,20000.0f);
	position = VGet(-30.0f,120.0f,-30.0f);
	target = VGet(0.0f,0.0f,0.0f);
	// カメラの座標を設定
	SetCameraPositionAndTarget_UpVecY(position,target);
	targetChara = chara;
	AngleH=0.f;
	AngleV=0.f;
	lockOnEnemy = 0;
	beforeEnemySize = 0;
}

void Camera::Move(){
	target = targetChara->GetPosition();
	VECTOR temp = VGet( CAMERA_WIDTH, CAMERA_HEIGHT, 0.0f );
	
	// 水平方向の回転はＹ軸回転
	MATRIX RotY = MGetRotY( AngleH ) ;

	// 垂直方向の回転はＺ軸回転 )
	MATRIX RotZ = MGetRotZ( AngleV ) ;
	
	// カメラの座標を算出
	// Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
	// 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )
	temp= VTransform( VTransform( temp, RotZ ), RotY );

	position = VAdd( target,temp ) ;

}
void Camera::Rotate(Input *input){

	// 「←」ボタンが押されていたら水平角度をマイナスする
	if( input->isLeft2() )
	{
		//AngleH -= (float)input->isLeft2()*CAMERA_ANGLE_SPEED ;
		AngleH -= CAMERA_ANGLE_SPEED ;

		// －１８０度以下になったら角度値が大きくなりすぎないように３６０度を足す
		if( AngleH < -DX_PI_F )
		{
			AngleH += DX_TWO_PI_F ;
		}
	}

	// 「→」ボタンが押されていたら水平角度をプラスする
	if( input->isRight2() )
	{
		//AngleH += (float)input->isRight2()*CAMERA_ANGLE_SPEED ;
		AngleH += CAMERA_ANGLE_SPEED ;

		// １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
		if( AngleH > DX_PI_F )
		{
			AngleH -= DX_TWO_PI_F ;
		}
	}

	// 「↑」ボタンが押されていたら垂直角度をマイナスする
	if( input->isUp2() )
	{
		//AngleV -= (float)input->isUp2()*CAMERA_ANGLE_SPEED ;
		AngleV -= CAMERA_ANGLE_SPEED ;

		// ある一定角度以下にはならないようにする
		if( AngleV < -DX_PI_F / 2.0f + 0.6f )
		{
			AngleV = -DX_PI_F / 2.0f + 0.6f ;
		}
	}

	// 「↓」ボタンが押されていたら垂直角度をプラスする
	if( input->isDown2())
	{
		//AngleV += (float)input->isDown2()*CAMERA_ANGLE_SPEED ;
		AngleV += CAMERA_ANGLE_SPEED ;

		// ある一定角度以上にはならないようにする
		if( AngleV > DX_PI_F / 2.0f - 0.6f )
		{
			AngleV = DX_PI_F / 2.0f - 0.6f ;
		}
	}
	if(input->isPushed2()){
		AngleV = -20.0f * DX_PI_F/180.f;
	}
}


void Camera::Update(){
	VECTOR newTarget = VTransform(VGet(20.0f,0.f,0.f),MGetRotY(AngleH));
	// カメラの座標を設定
	SetCameraPositionAndTarget_UpVecY(position,VAdd(target,newTarget));
	// SetCameraPositionAndTarget_UpVecY(VGet(500.f,600.f,0.f),target);
}

void Camera::DebugDraw(){
	DrawCapsule3D(position,VAdd(target,VGet(0.f,1.0f,0.f)),CAMERA_COLLISION_SIZE,0,GetColor(0,0,255),0,1);
}

Camera::~Camera(){

}

VECTOR Camera::GetPos(){
	return position;
}

VECTOR Camera::GetTarget(){
	return target;
}

float Camera::GetAngleH(){
	return AngleH;
}

float Camera::GetAngleV(){
	return AngleV;
}

void Camera::LockOn(Player* player,std::vector<Enemy*> *enemies,bool sameEnemyLockON){
	if(sameEnemyLockON && lockOnEnemy && beforeEnemySize == enemies->size()){
		if(lockOnEnemy){
			target = lockOnEnemy->GetPosition();
			/*
			VECTOR pPos = player->GetPosition();
			float takasa = target.y - pPos.y;
			float teihen = pow(target.x - pPos.x,2) + pow(target.z - pPos.z ,2);
			teihen = sqrt(teihen);
			AngleV = atan(takasa/teihen)*3.14;
			AngleV -= 0.44f;
			*/
		}	
	}else{
		beforeEnemySize = enemies->size();
		// 距離を求める
		float minDistance = LOCK_ON_DISTANCE;
		lockOnEnemy = 0;
		VECTOR pPos = player->GetPosition();
		for(int i=0;i<enemies->size();i++){
			VECTOR tempPos = enemies->at(i)->GetPosition();
			VECTOR distanceVec = VSub(pPos,tempPos);
			float tempDistance = VSize(distanceVec);
			if(minDistance > tempDistance){
				minDistance = tempDistance;
				lockOnEnemy = (*enemies)[i];	
			}
		}
		if(lockOnEnemy){
			target = lockOnEnemy->GetPosition();
			float takasa = target.y - pPos.y;
			float teihen = pow(target.x - pPos.x,2) + pow(target.z - pPos.z ,2);
			teihen = sqrt(teihen);
			AngleV = atan(takasa/teihen)*3.14/2.f;
			AngleV -= 0.44f;
		}	
	}
}


void Camera::CheckStageColl(Stage* stage){
	// カメラの座標を決定する

	MATRIX RotZ, RotY ;
	float Camera_Player_Length ;
	MV1_COLL_RESULT_POLY_DIM HRes ;
	int HitNum ;

	// 水平方向の回転はＹ軸回転
	RotY = MGetRotY( AngleH ) ;

	// 垂直方向の回転はＺ軸回転 )
	RotZ = MGetRotZ( AngleV ) ;

	// カメラからプレイヤーまでの初期距離をセット
	Camera_Player_Length = 30.0f;

	// カメラの座標を算出
	// Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
	// 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
	// 注視点の座標を足したものがカメラの座標
	position = VAdd( VTransform( VTransform( VGet( -Camera_Player_Length, 0.0f, 0.0f ), RotZ ), RotY ), target ) ;

	
	// 注視点からカメラの座標までの間にステージのポリゴンがあるか調べる
	HRes = stage->CollCheckCapsule(position,VAdd(target,VGet(0.f,1.0f,0.f)),CAMERA_COLLISION_SIZE );
	HitNum = HRes.HitNum ;
	MV1CollResultPolyDimTerminate( HRes ) ;
	if( HitNum != 0 )
	{
		float NotHitLength ;
		float HitLength ;
		float TestLength ;
		VECTOR TestPosition ;

		// あったら無い位置までプレイヤーに近づく

		// ポリゴンに当たらない距離をセット
		NotHitLength = 0.0f ;

		// ポリゴンに当たる距離をセット
		HitLength = Camera_Player_Length ;
		do
		{
			// 当たるかどうかテストする距離をセット( 当たらない距離と当たる距離の中間 )
			TestLength = NotHitLength + ( HitLength - NotHitLength ) / 2.0f ;

			// テスト用のカメラ座標を算出
			TestPosition = VAdd( VTransform( VTransform( VGet( -TestLength, 0.0f, 0.0f ), RotZ ), RotY ), position ) ;

			// 新しい座標で壁に当たるかテスト
			HRes = stage->CollCheckCapsule(TestPosition,target,CAMERA_COLLISION_SIZE );
			HitNum = HRes.HitNum ;
			MV1CollResultPolyDimTerminate( HRes ) ;
			if( HitNum != 0 )
			{
				// 当たったら当たる距離を TestLength に変更する
				HitLength = TestLength ;
			}
			else
			{
				// 当たらなかったら当たらない距離を TestLength に変更する
				NotHitLength = TestLength ;
			}

			// HitLength と NoHitLength が十分に近づいていなかったらループ
		}while( HitLength - NotHitLength > 0.1f ) ;

		// カメラの座標をセット
		position = TestPosition ;
	}
}