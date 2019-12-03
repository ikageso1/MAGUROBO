#pragma once
#include "DxLib.h"
#include "Input.h"
#include <vector>

class Character;
class Player;
class Enemy;
class Stage;

// カメラ情報構造体
class Camera{
private:
	VECTOR position;		/**< カメラ座標 */
	VECTOR target;			/**< カメラの向いている方向 */
	Character *targetChara;	/**< 追尾するキャラクタ */
	float AngleH;			/**< カメラのアングル（水平方向） */
	float AngleV;			/**< カメラのアングル（垂直方向） */
	Enemy* lockOnEnemy;
	int  beforeEnemySize;	/**< 無効なポインタ参照防止用（もっといい方法求む）*/
public:	
	/**
	 *  コンストラクタ 
	 *  カメラの初期化処理
	 */
	Camera(Character* chara) ;
	/**
	 * カメラの回転 
	 */
	void Rotate(Input *input);	
	/**
 	 * カメラの移動 
	 */
	void Move();	
	/**
	 * デストラクタ 何もしてない
	 */
	~Camera();


	/**
	 * カメラの位置座標を取得する 
	 */
	VECTOR GetPos();
	/**
	 * 追尾するキャラの位置座標の取得 
	 */
	VECTOR GetTarget();
	float GetAngleH();
	float GetAngleV();

	void CheckStageColl(Stage *stage);
	void Update();
	void DebugDraw();
	void LockOn(Player *player,std::vector<Enemy*> *enemie,bool sameEnemyLockON);
} ;