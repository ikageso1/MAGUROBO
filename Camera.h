#pragma once
#include "DxLib.h"
#include "Input.h"
#include <vector>

class Character;
class Player;
class Enemy;
class Stage;

// �J�������\����
class Camera{
private:
	VECTOR position;		/**< �J�������W */
	VECTOR target;			/**< �J�����̌����Ă������ */
	Character *targetChara;	/**< �ǔ�����L�����N�^ */
	float AngleH;			/**< �J�����̃A���O���i���������j */
	float AngleV;			/**< �J�����̃A���O���i���������j */
	Enemy* lockOnEnemy;
	int  beforeEnemySize;	/**< �����ȃ|�C���^�Q�Ɩh�~�p�i�����Ƃ������@���ށj*/
public:	
	/**
	 *  �R���X�g���N�^ 
	 *  �J�����̏���������
	 */
	Camera(Character* chara) ;
	/**
	 * �J�����̉�] 
	 */
	void Rotate(Input *input);	
	/**
 	 * �J�����̈ړ� 
	 */
	void Move();	
	/**
	 * �f�X�g���N�^ �������ĂȂ�
	 */
	~Camera();


	/**
	 * �J�����̈ʒu���W���擾���� 
	 */
	VECTOR GetPos();
	/**
	 * �ǔ�����L�����̈ʒu���W�̎擾 
	 */
	VECTOR GetTarget();
	float GetAngleH();
	float GetAngleV();

	void CheckStageColl(Stage *stage);
	void Update();
	void DebugDraw();
	void LockOn(Player *player,std::vector<Enemy*> *enemie,bool sameEnemyLockON);
} ;