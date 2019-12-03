#pragma once
#include "DxLib.h"
#include <vector>
#include <btBulletDynamicsCommon.h>

//プラグマ宣言リンカ
#pragma comment( lib, "BulletCollision.lib" )
#pragma comment( lib, "BulletDynamics.lib" )
#pragma comment( lib, "BulletSoftBody.lib" )
#pragma comment( lib, "LinearMath.lib" )

//右手→左手位置変換
inline VECTOR btVGet(const btVector3 &inv){return VGet(inv.getX(), inv.getY(), -inv.getZ());}
//右手→左手回転変換
inline VECTOR btRotVGet(const btVector3 &inv){return VGet(-inv.getX(), -inv.getY(), inv.getZ());}

inline btVector3 VbtGet(const VECTOR &inv){return btVector3(inv.x, inv.y, -inv.z);}

class BulletModel{
private:
	int Model_Handle;
	// 座標
	btVector3 position;
	// 落下する箱の衝突形状の作成
	btCollisionShape* fallShape ;
	// 箱のMotionStateの設定
	btDefaultMotionState* fallMotionState;
	// 箱の剛体の作成
	btRigidBody* fallRigidBody;

	// 位置情報
	btTransform trans;


	// 前回の座標
	btVector3 beforePos;

public:
	BulletModel(float x,float y,float z,const TCHAR* source){
		// ハンドル読み込み
		Model_Handle = MV1LoadModel(source) ;
		// 座標
		position = btVector3(x,y,z);
		// 落下する箱の衝突形状の作成
		fallShape = new btBoxShape(btVector3(1.0f, 0.5f, 1.0f));
		// 箱のMotionStateの設定
		fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),position));

		// 質量、慣性の初期化
		btScalar mass = 1;
		btVector3 fallInertia(0,0,0);
		fallShape->calculateLocalInertia(mass,fallInertia);
		// 箱の初期情報を設定
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
		// 箱の剛体の作成
		fallRigidBody = new btRigidBody(fallRigidBodyCI);	
	}
	~BulletModel(){
		// 読み込んだモデルの削除
		MV1DeleteModel( Model_Handle ) ;
		delete fallRigidBody->getMotionState();
		delete fallRigidBody;
		// 箱の衝突形状を削除
		delete fallShape;
	}

	// シミュレート
	void simulate(){
		beforePos = position;
		position.setY(0.0f);
		trans.setOrigin( btVector3(0.0f,0.0f,0.0f) );
		

		// 箱の位置姿勢情報の取
		fallRigidBody->getMotionState()->getWorldTransform(trans);
		// fallRigidBody->getWorldTransform().setOrigin(position);
		position = trans.getOrigin();
		

		// 位置取得
		//VECTOR pos = btVGet(position) ;
		
		//個別取得例
		VECTOR nowVec;
		nowVec.x = btVGet(position).x;
		nowVec.y = btVGet(position).y;
		nowVec.z = btVGet(position).z;
		MV1SetPosition( Model_Handle, nowVec ) ;

		// 回転
		rotate();
	}

	// 差分を返す
	VECTOR getMoveVec(){
		return VSub(btVGet(position),btVGet(beforePos));
	}

	void rotate(){
		// 角度取得
		btMatrix3x3 rot = trans.getBasis();
		btVector3 euler;
		rot.getEulerZYX(euler[2], euler[1], euler[0]);
		MV1SetRotationXYZ(Model_Handle, btRotVGet(euler));

	}

	void setMoveVec(VECTOR moveVec){
		//fallRigidBody->applyCentralForce(VbtGet(moveVec));
		//fallRigidBody->getMotionState()->getWorldTransform(trans);
		//position = VbtGet(moveVec);
		//fallRigidBody->getWorldTransform().setOrigin(VbtGet(moveVec));
	}

	void draw(){
		// モデルを描画
		MV1DrawModel( Model_Handle ) ;
	}
	int getModelHandle(){
		return Model_Handle;
	}
	btRigidBody* getBody(){
		return this->fallRigidBody;
	}
};