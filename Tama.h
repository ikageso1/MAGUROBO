#pragma once
#include "DxLib.h"

class Stage;
class Character;

class Tama{
protected:
	VECTOR position;	/**< �e�̈ʒu */
	VECTOR moveVec;		/**< �e�̓������x */
	bool isAlive;		/**< �����蔻��ɁA�e�������������ǂ����̔��� */
	int timer;			/**< �^�C�}�[�ϐ� */
	float r;			/**< ���a */
public:
	/**
	*�@�R���X�g���N�^ �e�̏�����
	*/
	Tama(VECTOR playerPosition,float HAngle,float VAngle);
	/**
	* �f�X�g���N�^�@���ɏ����͉������ĂȂ�
	*/
	~Tama();
	/** 
	 * �e�𓮂�������������֐�
	 */
	virtual void Move(Stage *stg) = 0;
	/**
	 * �e�̕`�������֐�
	 */
	void Draw();
	/**
	 * �e�������蔻��ɁA�����������ǂ����̔�����擾����֐�
	 */
	bool GetAlive();
	bool CollCheck(Character *chara);
};