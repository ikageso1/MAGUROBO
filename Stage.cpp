#include "Stage.h"

Stage::Stage(){
}

// デストラクタ
Stage::~Stage(){
	// ステージモデルの後始末
	MV1DeleteModel( ModelHandle ) ;
}

void Stage::Draw(){
	// ステージモデルの描画
	MV1DrawModel( ModelHandle ) ;
}



// ファイル読み込み
void Stage::LoadStage(const TCHAR* filename){
	ModelHandle = MV1LoadModel(filename) ;
}


// プレイヤーの周囲にあるステージポリゴンを取得する
MV1_COLL_RESULT_POLY_DIM Stage::GetStagePoly(VECTOR pos,float r){
	// プレイヤーの周囲にあるステージポリゴンを取得する
	// ( 検出する範囲は移動距離も考慮する )
	return MV1CollCheck_Sphere( ModelHandle, -1,pos,r) ;
}

// プレイヤーの周囲にあるステージポリゴンを取得する
MV1_COLL_RESULT_POLY_DIM Stage::CollCheckCapsule(VECTOR pos1,VECTOR pos2,float r){
	// プレイヤーの周囲にあるステージポリゴンを取得する
	// ( 検出する範囲は移動距離も考慮する )
	return MV1CollCheck_Capsule( ModelHandle, -1,pos1,pos2,r) ;
}