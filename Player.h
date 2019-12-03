#pragma once
#include "DxLib.h"
#include "Input.h"
#include "Tama.h"
#include "Character.h"
#include <vector>

class Stage;
class Input;
class Enemy;

class Player :public Character{
protected:
	int NoWeaponModel;
	int M95WeaponModel;
	int JetModel;

	int FireSound;		/**< 攻撃音 */
	int JumpSound;		/**< ジャンプ */
	int DamageSound;	/**< ダメージ */

	int AimGraph;		/**< 照準画像 */
public:
	Player(float x,float y,float z);			// コンストラクタ
	~Player();			// デストラクタ
	
	void Draw();
	void SetMoveVec(VECTOR target,VECTOR pos);
	/**
	 * プレイヤーの移動方向のベクトルを算出する関数
	 */
	void SetDirection(float AngleV);
	void SetInputAI(Input* input);
	void ChangeModel(std::string name);
	void Damage(int damage);
	void Attack();
	void Jump();
	void SetJetMode();
	void Eject();
	void Kaihuku(int cure);
};