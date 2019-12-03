#pragma once
#include "DxLib.h"
#include <vector>
#include <btBulletDynamicsCommon.h>

//プラグマ宣言リンカ
#pragma comment( lib, "BulletCollision.lib" )
#pragma comment( lib, "BulletDynamics.lib" )
#pragma comment( lib, "BulletSoftBody.lib" )
#pragma comment( lib, "LinearMath.lib" )

class BtWorld{
private:
	// 衝突解決ソルバ
	btSequentialImpulseConstraintSolver* solver;
	// 離散動的世界の作成
	btDiscreteDynamicsWorld* dynamicsWorld;
	// broadphaseの作成（SAP法）
	btAxisSweep3* broadphase;
	// 衝突設定
	btDefaultCollisionConfiguration* collisionConfiguration;
	// ディスパッチャ
	btCollisionDispatcher* dispatcher;
	// 地面の衝突形状
	btCollisionShape* groundShape;
	// 地面のMotionState
	btDefaultMotionState* groundMotionState;
	// 地面の剛体
	btRigidBody* groundRigidBody;
	// 保持している剛体リスト
	std::vector<btRigidBody*>* bodys;
public:
	// コンストラクタ
	BtWorld(){
		// ワールドの広さ
		btVector3 worldAabbMin(-10000,-10000,-10000);
		btVector3 worldAabbMax(10000,10000,10000);
		// プロキシの最大数（衝突物体のようなもの）
		int maxProxies = 1024;
		// broadphaseの作成（SAP法）
		broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);

		// デフォルトの衝突設定とディスパッチャの作成
		// デフォルトのコリジョンコンフィグを作成する
		collisionConfiguration = new btDefaultCollisionConfiguration();
		// デフォルトのコリジョンディスパッチャを作成する
		dispatcher = new btCollisionDispatcher(collisionConfiguration);

		// 衝突解決ソルバ
		solver = new btSequentialImpulseConstraintSolver;
		// 離散動的世界の作成
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
		// 重力の設定
		dynamicsWorld->setGravity(btVector3(0,-10,0));
		// 地面の衝突形状の作成
		groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
		// 地面のMotionStateの設定
		groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));

		// 地面の初期情報を設定
		btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
		// 地面の剛体の作成
		groundRigidBody = new btRigidBody(groundRigidBodyCI);
		// ワールドに地面の剛体を追加
		dynamicsWorld->addRigidBody(groundRigidBody);

		// ワールドに追加した剛体
		bodys = new  std::vector<btRigidBody*>();
	}

	// 剛体の追加
	void addBody(btRigidBody* body){
		// ワールドに箱の剛体を追加
		dynamicsWorld->addRigidBody(body);
		// リストに追加
		bodys->push_back(body);
	}
	// シミュレーションを進める
	void simulate(){
	    // シミュレーションを進める。間隔は60Hz
		dynamicsWorld->stepSimulation(1/60.f,10);
	}

	// デストラクタ
	~BtWorld(){

		// 箱の剛体を削除
		for(int i=0;i<bodys->size();i++){
			dynamicsWorld->removeRigidBody((*bodys)[i]);
		}
		delete bodys;
		// 地面の剛体を削除
		dynamicsWorld->removeRigidBody(groundRigidBody);
		delete groundRigidBody->getMotionState();
		delete groundRigidBody;
		// 地面の衝突形状を削除
		delete groundShape;
		// ワールド・ソルバ・その他もろもろの削除
		delete dynamicsWorld;
		delete solver;
		delete collisionConfiguration;
		delete dispatcher;
		delete broadphase;
	}
};