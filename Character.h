#pragma once
#include "DxLib.h"
#include "Input.h"
#include "Tama.h"
#include <list>
#include <vector>
#include "AI.h"

class Weapon;
class Stage;
class AI;

#define ANGLE_SPEED 0.2f
#define ROLE_SPEED 0.2f
#define HIT_TRYNUM 16

struct HitBox{
	VECTOR position;
	float angle;				/**< 水平角度*/
	VECTOR front;				/**< 前 */
	VECTOR back;				/**< 後ろ */
	float r;					/**< 半径 */
	float height;				/**< 高さ */

	
	/**
	 * 当り判定を設定する
	 */
	void setHitBox(	VECTOR hitbox_front,VECTOR hitbox_back,float r,	float height){
		this->front = hitbox_front;	
		this->back = hitbox_back;
		this->r = r;
		this->height = height;
	}
};



class Character{
protected:	
	int MoveFlag;					// 動いたかフラグ
	Direction directionFlag;		// 方向フラグ
	float	speed;					// 速度係数

	HitBox hitbox;					/**< 当り判定ボックス*/
	VECTOR	Position ;				/**< 座標 */
	VECTOR  StartPos;				/**< 最初の座標*/
	VECTOR  Direction;				/**< 方向 */
	int		ModelHandle ;			/**< モデルハンドル */
	float	Angle;					/**< 角度 */
	float	AngleV;					/**< 垂直方向の角度 */
	bool	isRoleRight;			/**< 右緊急回避 */
	bool	isRoleLeft;				/**< 左緊急回避 */
	float   RoleAngle;				/**< 緊急回避用の角度 */
	VECTOR  MoveVec;				/**< 移動ベクトル */
	std::list<Tama*>	*tama;		/**< たま */
	int		tamaMax;				/**< たまのMAXの数 */
	Weapon *weapon;					/**< 武器 */

	bool	isFire;					
	bool	isJump;					// ジャンプ中かどうか
	int		isJet;					// ジェット中かどうか
	float   jump;					// ジャンプ値

	std::string	 name;				/**< 名前 */
	int		HP;
	int		MaxHP;
	bool	isAlive;

	VECTOR  UpMoveVec;				/**< 上に動かすための移動ベクトル */
	VECTOR  LeftMoveVec;			/**< 左に動かすための移動ベクトル */

	// 環境変数
	float JUMP_POWER;		
	float HIT_WIDTH;				/**< 当たり判定の幅 */
	float ENUM_DEFAULT_SIZE;		/**< 当たり判定を検出する半径 */
	float HIT_HORIZON;				/**< 当たり判定の水平距離 */
	float HIT_HEIGHT;				/**< 当たり判定の高さ */
	float HIT_SLIDE_LENGTH;			/**< 当たったときに、どれだけずらすか */

	AI	*ai;						/**< AI */

public:
	/**
	 * コンストラクタ 
	 * 自分が操作するキャラクター(マグロ)の初期化する。
	 */
	Character(float x,float y,float z);	
	/**
	* デストラクタ
	* プレイヤーが打った弾のオブジェクトを消去する。
	*/
	~Character();

	virtual void Attack();		// 攻撃
	/**
	 * 弾の移動 
	 */
	void TamaMove(Stage *stg);				
	void TamaDeath();
	/**
	 * 動きの処理 
	 */
	virtual void Move();
	/**
	 * 描画
	 */
	virtual void Draw();					
	/**
	 * キャラの向きを変える（回転させる）
	 * 関数
	 */
	virtual void Rotate( void );
	/**
	 * Z方向の回転
	 */
	void Role();			
	/**
	 *　ステージとの当り判定
	 */
	void CheckStageColl(Stage *std);		
	virtual void Jump();
	/**
	 * あとで直します
	 */ 
	void Jet();
	void Think();
	void UpdatePosition();
	bool CollCheck(Character *chara2);
	virtual void Damage(int damage);
	bool TamaCollCheck(Character *target);
	bool GetisAlive();
	void SetWeapon(Weapon* w);
	void Fall();
	void SetName(std::string name);

	int GetDamage();
	// 座標のゲッター
	VECTOR GetPosition();
	HitBox GetHitBox();

	
private:
	void JudgeFlootOrWall(MV1_COLL_RESULT_POLY_DIM &HitDim,
		std::vector<MV1_COLL_RESULT_POLY*> *Kabe,
		std::vector<MV1_COLL_RESULT_POLY*> *Yuka);
	VECTOR AttachWall(std::vector<MV1_COLL_RESULT_POLY*> *Kabe);
};