#pragma once
#include "DxLib.h"
#include <vector>
#include <btBulletDynamicsCommon.h>

//�v���O�}�錾�����J
#pragma comment( lib, "BulletCollision.lib" )
#pragma comment( lib, "BulletDynamics.lib" )
#pragma comment( lib, "BulletSoftBody.lib" )
#pragma comment( lib, "LinearMath.lib" )

//�E�聨����ʒu�ϊ�
inline VECTOR btVGet(const btVector3 &inv){return VGet(inv.getX(), inv.getY(), -inv.getZ());}
//�E�聨�����]�ϊ�
inline VECTOR btRotVGet(const btVector3 &inv){return VGet(-inv.getX(), -inv.getY(), inv.getZ());}

inline btVector3 VbtGet(const VECTOR &inv){return btVector3(inv.x, inv.y, -inv.z);}

class BulletModel{
private:
	int Model_Handle;
	// ���W
	btVector3 position;
	// �������锠�̏Փˌ`��̍쐬
	btCollisionShape* fallShape ;
	// ����MotionState�̐ݒ�
	btDefaultMotionState* fallMotionState;
	// ���̍��̂̍쐬
	btRigidBody* fallRigidBody;

	// �ʒu���
	btTransform trans;


	// �O��̍��W
	btVector3 beforePos;

public:
	BulletModel(float x,float y,float z,const TCHAR* source){
		// �n���h���ǂݍ���
		Model_Handle = MV1LoadModel(source) ;
		// ���W
		position = btVector3(x,y,z);
		// �������锠�̏Փˌ`��̍쐬
		fallShape = new btBoxShape(btVector3(1.0f, 0.5f, 1.0f));
		// ����MotionState�̐ݒ�
		fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),position));

		// ���ʁA�����̏�����
		btScalar mass = 1;
		btVector3 fallInertia(0,0,0);
		fallShape->calculateLocalInertia(mass,fallInertia);
		// ���̏�������ݒ�
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
		// ���̍��̂̍쐬
		fallRigidBody = new btRigidBody(fallRigidBodyCI);	
	}
	~BulletModel(){
		// �ǂݍ��񂾃��f���̍폜
		MV1DeleteModel( Model_Handle ) ;
		delete fallRigidBody->getMotionState();
		delete fallRigidBody;
		// ���̏Փˌ`����폜
		delete fallShape;
	}

	// �V�~�����[�g
	void simulate(){
		beforePos = position;
		position.setY(0.0f);
		trans.setOrigin( btVector3(0.0f,0.0f,0.0f) );
		

		// ���̈ʒu�p�����̎�
		fallRigidBody->getMotionState()->getWorldTransform(trans);
		// fallRigidBody->getWorldTransform().setOrigin(position);
		position = trans.getOrigin();
		

		// �ʒu�擾
		//VECTOR pos = btVGet(position) ;
		
		//�ʎ擾��
		VECTOR nowVec;
		nowVec.x = btVGet(position).x;
		nowVec.y = btVGet(position).y;
		nowVec.z = btVGet(position).z;
		MV1SetPosition( Model_Handle, nowVec ) ;

		// ��]
		rotate();
	}

	// ������Ԃ�
	VECTOR getMoveVec(){
		return VSub(btVGet(position),btVGet(beforePos));
	}

	void rotate(){
		// �p�x�擾
		btMatrix3x3 rot = trans.getBasis();
		btVector3 euler;
		rot.getEulerZYX(euler[2], euler[1], euler[0]);
		MV1SetRotationXYZ(Model_Handle, btRotVGet(euler));

	}

	void setMoveVec(VECTOR moveVec){
		//fallRigidBody->applyCentralForce(VbtGet(moveVec));
		//fallRigidBody->getMotionState()->getWorldTransform(trans);
		//position = VbtGet(moveVec);
		//fallRigidBody->getWorldTransform().setOrigin(VbtGet(moveVec));
	}

	void draw(){
		// ���f����`��
		MV1DrawModel( Model_Handle ) ;
	}
	int getModelHandle(){
		return Model_Handle;
	}
	btRigidBody* getBody(){
		return this->fallRigidBody;
	}
};