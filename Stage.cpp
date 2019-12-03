#include "Stage.h"

Stage::Stage(){
}

// �f�X�g���N�^
Stage::~Stage(){
	// �X�e�[�W���f���̌�n��
	MV1DeleteModel( ModelHandle ) ;
}

void Stage::Draw(){
	// �X�e�[�W���f���̕`��
	MV1DrawModel( ModelHandle ) ;
}



// �t�@�C���ǂݍ���
void Stage::LoadStage(const TCHAR* filename){
	ModelHandle = MV1LoadModel(filename) ;
}


// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
MV1_COLL_RESULT_POLY_DIM Stage::GetStagePoly(VECTOR pos,float r){
	// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
	// ( ���o����͈͈͂ړ��������l������ )
	return MV1CollCheck_Sphere( ModelHandle, -1,pos,r) ;
}

// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
MV1_COLL_RESULT_POLY_DIM Stage::CollCheckCapsule(VECTOR pos1,VECTOR pos2,float r){
	// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
	// ( ���o����͈͈͂ړ��������l������ )
	return MV1CollCheck_Capsule( ModelHandle, -1,pos1,pos2,r) ;
}