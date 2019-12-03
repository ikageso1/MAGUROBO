#pragma once
#include "Input.h"
#include <DxLib.h>



//プラグマ宣言リンカ
#pragma comment( lib, "BulletCollision.lib" )
#pragma comment( lib, "BulletDynamics.lib" )
#pragma comment( lib, "BulletSoftBody.lib" )
#pragma comment( lib, "LinearMath.lib" )

class BtWorld;
class BulletModel;

class Title{
private:
	BtWorld* world;		
	BulletModel* model[10];
	VECTOR modelPos[10];
	bool endFlag;	/**< 終了フラグ */
public:
	/**
	* コンストラクタ　タイトル画面の初期化
	*/
	Title();		
	/**
	 * タイトル画面の処理する関数 
	 */
	void process(Input* input);	// 処理
	/**
	 * 終了なのか判定するフラグを返す関数 
	 */
	bool isFinish();	
	/**
	 * デストラクタ　何もしてない
	 */
	~Title();		
};