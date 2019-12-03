#pragma once
#include "DxLib.h"
#include <vector>
#include <btBulletDynamicsCommon.h>

//�v���O�}�錾�����J
#pragma comment( lib, "BulletCollision.lib" )
#pragma comment( lib, "BulletDynamics.lib" )
#pragma comment( lib, "BulletSoftBody.lib" )
#pragma comment( lib, "LinearMath.lib" )

class BtWorld{
private:
	// �Փˉ����\���o
	btSequentialImpulseConstraintSolver* solver;
	// ���U���I���E�̍쐬
	btDiscreteDynamicsWorld* dynamicsWorld;
	// broadphase�̍쐬�iSAP�@�j
	btAxisSweep3* broadphase;
	// �Փːݒ�
	btDefaultCollisionConfiguration* collisionConfiguration;
	// �f�B�X�p�b�`��
	btCollisionDispatcher* dispatcher;
	// �n�ʂ̏Փˌ`��
	btCollisionShape* groundShape;
	// �n�ʂ�MotionState
	btDefaultMotionState* groundMotionState;
	// �n�ʂ̍���
	btRigidBody* groundRigidBody;
	// �ێ����Ă��鍄�̃��X�g
	std::vector<btRigidBody*>* bodys;
public:
	// �R���X�g���N�^
	BtWorld(){
		// ���[���h�̍L��
		btVector3 worldAabbMin(-10000,-10000,-10000);
		btVector3 worldAabbMax(10000,10000,10000);
		// �v���L�V�̍ő吔�i�Փ˕��̂̂悤�Ȃ��́j
		int maxProxies = 1024;
		// broadphase�̍쐬�iSAP�@�j
		broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);

		// �f�t�H���g�̏Փːݒ�ƃf�B�X�p�b�`���̍쐬
		// �f�t�H���g�̃R���W�����R���t�B�O���쐬����
		collisionConfiguration = new btDefaultCollisionConfiguration();
		// �f�t�H���g�̃R���W�����f�B�X�p�b�`�����쐬����
		dispatcher = new btCollisionDispatcher(collisionConfiguration);

		// �Փˉ����\���o
		solver = new btSequentialImpulseConstraintSolver;
		// ���U���I���E�̍쐬
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
		// �d�͂̐ݒ�
		dynamicsWorld->setGravity(btVector3(0,-10,0));
		// �n�ʂ̏Փˌ`��̍쐬
		groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
		// �n�ʂ�MotionState�̐ݒ�
		groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));

		// �n�ʂ̏�������ݒ�
		btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
		// �n�ʂ̍��̂̍쐬
		groundRigidBody = new btRigidBody(groundRigidBodyCI);
		// ���[���h�ɒn�ʂ̍��̂�ǉ�
		dynamicsWorld->addRigidBody(groundRigidBody);

		// ���[���h�ɒǉ���������
		bodys = new  std::vector<btRigidBody*>();
	}

	// ���̂̒ǉ�
	void addBody(btRigidBody* body){
		// ���[���h�ɔ��̍��̂�ǉ�
		dynamicsWorld->addRigidBody(body);
		// ���X�g�ɒǉ�
		bodys->push_back(body);
	}
	// �V�~�����[�V������i�߂�
	void simulate(){
	    // �V�~�����[�V������i�߂�B�Ԋu��60Hz
		dynamicsWorld->stepSimulation(1/60.f,10);
	}

	// �f�X�g���N�^
	~BtWorld(){

		// ���̍��̂��폜
		for(int i=0;i<bodys->size();i++){
			dynamicsWorld->removeRigidBody((*bodys)[i]);
		}
		delete bodys;
		// �n�ʂ̍��̂��폜
		dynamicsWorld->removeRigidBody(groundRigidBody);
		delete groundRigidBody->getMotionState();
		delete groundRigidBody;
		// �n�ʂ̏Փˌ`����폜
		delete groundShape;
		// ���[���h�E�\���o�E���̑��������̍폜
		delete dynamicsWorld;
		delete solver;
		delete collisionConfiguration;
		delete dispatcher;
		delete broadphase;
	}
};