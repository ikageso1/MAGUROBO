#pragma once
#include "DxLib.h"
#include <vector>

class Player;
class Enemy;
class Item;

// �X�e�[�W���\����
class Stage
{
protected:
	int		ModelHandle ;				/**< 3D���f���n���h�� */
	
public:
	/**
	* �R���X�g���N�^�@�X�e�[�W�̏�����
	*/
	Stage();			
	/**
	* �f�X�g���N�^�@�X�e�[�W�̏���
	*/
	~Stage();		
	/**
	 * �X�e�[�W�̕`�������֐� 
	 */
	void Draw();



	/**
	 * �X�e�[�W�̃|���S�����擾����֐� 
	 */
	MV1_COLL_RESULT_POLY_DIM GetStagePoly(VECTOR pos,float r);
	MV1_COLL_RESULT_POLY_DIM CollCheckCapsule(VECTOR pos1,VECTOR pos2,float r);
	/**
	 * �X�e�[�W�ǂݍ��݂�����֐� 
	 */
	void LoadStage(const TCHAR* filename);
	virtual Player* CreatePlayer() = 0;
	virtual void  CreateEnemies(std::vector<Enemy*> *enemies,Player *player) = 0;
	virtual void  CreateItems(std::vector<Item*> *items) = 0;
} ;
