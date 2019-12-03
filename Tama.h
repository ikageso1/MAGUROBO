#pragma once
#include "DxLib.h"

class Stage;
class Character;

class Tama{
protected:
	VECTOR position;	/**< 弾の位置 */
	VECTOR moveVec;		/**< 弾の動く速度 */
	bool isAlive;		/**< 当たり判定に、弾が当たったかどうかの判定 */
	int timer;			/**< タイマー変数 */
	float r;			/**< 半径 */
public:
	/**
	*　コンストラクタ 弾の初期化
	*/
	Tama(VECTOR playerPosition,float HAngle,float VAngle);
	/**
	* デストラクタ　特に処理は何もしてない
	*/
	~Tama();
	/** 
	 * 弾を動かす処理をする関数
	 */
	virtual void Move(Stage *stg) = 0;
	/**
	 * 弾の描画をする関数
	 */
	void Draw();
	/**
	 * 弾が当たり判定に、当たったかどうかの判定を取得する関数
	 */
	bool GetAlive();
	bool CollCheck(Character *chara);
};