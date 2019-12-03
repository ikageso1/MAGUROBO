#pragma once
#include "Input.h"
#include <DxLib.h>



//�v���O�}�錾�����J
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
	bool endFlag;	/**< �I���t���O */
public:
	/**
	* �R���X�g���N�^�@�^�C�g����ʂ̏�����
	*/
	Title();		
	/**
	 * �^�C�g����ʂ̏�������֐� 
	 */
	void process(Input* input);	// ����
	/**
	 * �I���Ȃ̂����肷��t���O��Ԃ��֐� 
	 */
	bool isFinish();	
	/**
	 * �f�X�g���N�^�@�������ĂȂ�
	 */
	~Title();		
};