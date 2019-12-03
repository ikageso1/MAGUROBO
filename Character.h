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
	float angle;				/**< �����p�x*/
	VECTOR front;				/**< �O */
	VECTOR back;				/**< ��� */
	float r;					/**< ���a */
	float height;				/**< ���� */

	
	/**
	 * ���蔻���ݒ肷��
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
	int MoveFlag;					// ���������t���O
	Direction directionFlag;		// �����t���O
	float	speed;					// ���x�W��

	HitBox hitbox;					/**< ���蔻��{�b�N�X*/
	VECTOR	Position ;				/**< ���W */
	VECTOR  StartPos;				/**< �ŏ��̍��W*/
	VECTOR  Direction;				/**< ���� */
	int		ModelHandle ;			/**< ���f���n���h�� */
	float	Angle;					/**< �p�x */
	float	AngleV;					/**< ���������̊p�x */
	bool	isRoleRight;			/**< �E�ً}��� */
	bool	isRoleLeft;				/**< ���ً}��� */
	float   RoleAngle;				/**< �ً}���p�̊p�x */
	VECTOR  MoveVec;				/**< �ړ��x�N�g�� */
	std::list<Tama*>	*tama;		/**< ���� */
	int		tamaMax;				/**< ���܂�MAX�̐� */
	Weapon *weapon;					/**< ���� */

	bool	isFire;					
	bool	isJump;					// �W�����v�����ǂ���
	int		isJet;					// �W�F�b�g�����ǂ���
	float   jump;					// �W�����v�l

	std::string	 name;				/**< ���O */
	int		HP;
	int		MaxHP;
	bool	isAlive;

	VECTOR  UpMoveVec;				/**< ��ɓ��������߂̈ړ��x�N�g�� */
	VECTOR  LeftMoveVec;			/**< ���ɓ��������߂̈ړ��x�N�g�� */

	// ���ϐ�
	float JUMP_POWER;		
	float HIT_WIDTH;				/**< �����蔻��̕� */
	float ENUM_DEFAULT_SIZE;		/**< �����蔻������o���锼�a */
	float HIT_HORIZON;				/**< �����蔻��̐������� */
	float HIT_HEIGHT;				/**< �����蔻��̍��� */
	float HIT_SLIDE_LENGTH;			/**< ���������Ƃ��ɁA�ǂꂾ�����炷�� */

	AI	*ai;						/**< AI */

public:
	/**
	 * �R���X�g���N�^ 
	 * ���������삷��L�����N�^�[(�}�O��)�̏���������B
	 */
	Character(float x,float y,float z);	
	/**
	* �f�X�g���N�^
	* �v���C���[���ł����e�̃I�u�W�F�N�g����������B
	*/
	~Character();

	virtual void Attack();		// �U��
	/**
	 * �e�̈ړ� 
	 */
	void TamaMove(Stage *stg);				
	void TamaDeath();
	/**
	 * �����̏��� 
	 */
	virtual void Move();
	/**
	 * �`��
	 */
	virtual void Draw();					
	/**
	 * �L�����̌�����ς���i��]������j
	 * �֐�
	 */
	virtual void Rotate( void );
	/**
	 * Z�����̉�]
	 */
	void Role();			
	/**
	 *�@�X�e�[�W�Ƃ̓��蔻��
	 */
	void CheckStageColl(Stage *std);		
	virtual void Jump();
	/**
	 * ���ƂŒ����܂�
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
	// ���W�̃Q�b�^�[
	VECTOR GetPosition();
	HitBox GetHitBox();

	
private:
	void JudgeFlootOrWall(MV1_COLL_RESULT_POLY_DIM &HitDim,
		std::vector<MV1_COLL_RESULT_POLY*> *Kabe,
		std::vector<MV1_COLL_RESULT_POLY*> *Yuka);
	VECTOR AttachWall(std::vector<MV1_COLL_RESULT_POLY*> *Kabe);
};