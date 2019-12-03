#include "DxLib.h"
#include "Title.h"
#include <btBulletDynamicsCommon.h>
#include "BulletModel.h"
#include "BulletWorld.h"


// コンストラクタ
Title::Title(){
	endFlag = false;

	//カメラポジション
	VECTOR CameraPos ;

	// カメラの座標を初期化
	CameraPos.x = 0.0f ;
	CameraPos.y = 5.0f ;
	CameraPos.z = -20.0f ;

	//モデル構造体
	struct MODEL_DICE
	{
		VECTOR		pos ;
	} ;

	// モデル情報の実体宣言
	MODEL_DICE mdl,mdl2 ;
	mdl.pos.x = 0.0f ;
	mdl.pos.y = 200.0f;
	mdl.pos.z = 0.0f ;

	mdl2.pos.x = 0.0f ;
	mdl2.pos.y = 40.0f;
	mdl2.pos.z = 0.0f ;


	// ワールドの生成
	world = new BtWorld();
	// モデルの生成
	for(int i=0;i<10;i++){
		model[i] = new BulletModel(0.0f,0.0f+20*i,0.0f,"chara/small.mv1" );
		world->addBody( model[i]->getBody() );
		modelPos[i] = VGet(0.0f,0.0f+20*i,0.0f);
	}

	//クリップ距離
	SetCameraNearFar(1.0f,20000.0f);
	// カメラの位置と注視点をセット
	SetCameraPositionAndTarget_UpVecY( CameraPos, VGet( 0.0f, 10.0f, 0.0f ) ) ;

}
// デストラクタ
Title::~Title(){
	delete world;

	for(int i=0;i<10;i++)
		delete model[i];
}

// 処理
void Title::process(Input* input){
	VECTOR moveVec[10];
	for(int i=0;i<10;i++){
		moveVec[i] = VGet(0.0f,0.0f,0.0f);
	}
	// シミュレーション
	world->simulate();
	if(CheckHitKey(KEY_INPUT_LEFT)){
		moveVec[0] = VAdd(moveVec[0],VGet(-10.0f,0.0f,0.0f));
	}
	if(CheckHitKey(KEY_INPUT_RIGHT)){
		moveVec[0] = VAdd(moveVec[0],VGet(10.0f,0.0f,0.0f));
	}

	for(int i=0;i<10;i++){
		model[i]->simulate();
		moveVec[i] = VAdd(moveVec[i],model[i]->getMoveVec());
		modelPos[i] = VAdd(modelPos[i],moveVec[i]);
		//MV1SetPosition(model[i]->getModelHandle(),modelPos[i]);
		model[i]->setMoveVec(moveVec[i]);

		model[i]->draw();
	}

	DrawFormatString(350,100,GetColor(255,255,255),"M A G U R O B O");


	// スタートボタンが押されたらタイトル画面終了
	if(input->isEdgeStartButton()){
		endFlag = true;
	}
}
bool Title::isFinish(){
	return endFlag;
}


