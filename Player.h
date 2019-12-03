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

	int FireSound;		/**< �U���� */
	int JumpSound;		/**< �W�����v */
	int DamageSound;	/**< �_���[�W */

	int AimGraph;		/**< �Ə��摜 */
public:
	Player(float x,float y,float z);			// �R���X�g���N�^
	~Player();			// �f�X�g���N�^
	
	void Draw();
	void SetMoveVec(VECTOR target,VECTOR pos);
	/**
	 * �v���C���[�̈ړ������̃x�N�g�����Z�o����֐�
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