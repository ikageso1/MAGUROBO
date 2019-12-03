#include "Camera.h"
#include "Stage.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"

#define CAMERA_HEIGHT				10.0f
#define CAMERA_WIDTH				20.0f
#define TERGET_HEIGHT				10.0f	
//#define CAMERA_ANGLE_SPEED		0.5f		// ���񑬓x
#define CAMERA_ANGLE_SPEED			0.05f		// ���񑬓x
#define CAMERA_PLAYER_LENGTH		10.0f		// �v���C���[�Ƃ̋���
#define CAMERA_COLLISION_SIZE		0.1f		// �J�����̓����蔻��T�C�Y
#define LOCK_ON_DISTANCE			30000.f


Camera::Camera(Character *chara){
	// �J�����̃N���b�v������ݒ�
	SetCameraNearFar(1.0f,20000.0f);
	position = VGet(-30.0f,120.0f,-30.0f);
	target = VGet(0.0f,0.0f,0.0f);
	// �J�����̍��W��ݒ�
	SetCameraPositionAndTarget_UpVecY(position,target);
	targetChara = chara;
	AngleH=0.f;
	AngleV=0.f;
	lockOnEnemy = 0;
	beforeEnemySize = 0;
}

void Camera::Move(){
	target = targetChara->GetPosition();
	VECTOR temp = VGet( CAMERA_WIDTH, CAMERA_HEIGHT, 0.0f );
	
	// ���������̉�]�͂x����]
	MATRIX RotY = MGetRotY( AngleH ) ;

	// ���������̉�]�͂y����] )
	MATRIX RotZ = MGetRotZ( AngleV ) ;
	
	// �J�����̍��W���Z�o
	// �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
	// ����������]( �y����] )���������Ɛ���������]( �x����] )
	temp= VTransform( VTransform( temp, RotZ ), RotY );

	position = VAdd( target,temp ) ;

}
void Camera::Rotate(Input *input){

	// �u���v�{�^����������Ă����琅���p�x���}�C�i�X����
	if( input->isLeft2() )
	{
		//AngleH -= (float)input->isLeft2()*CAMERA_ANGLE_SPEED ;
		AngleH -= CAMERA_ANGLE_SPEED ;

		// �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
		if( AngleH < -DX_PI_F )
		{
			AngleH += DX_TWO_PI_F ;
		}
	}

	// �u���v�{�^����������Ă����琅���p�x���v���X����
	if( input->isRight2() )
	{
		//AngleH += (float)input->isRight2()*CAMERA_ANGLE_SPEED ;
		AngleH += CAMERA_ANGLE_SPEED ;

		// �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
		if( AngleH > DX_PI_F )
		{
			AngleH -= DX_TWO_PI_F ;
		}
	}

	// �u���v�{�^����������Ă����琂���p�x���}�C�i�X����
	if( input->isUp2() )
	{
		//AngleV -= (float)input->isUp2()*CAMERA_ANGLE_SPEED ;
		AngleV -= CAMERA_ANGLE_SPEED ;

		// ������p�x�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
		if( AngleV < -DX_PI_F / 2.0f + 0.6f )
		{
			AngleV = -DX_PI_F / 2.0f + 0.6f ;
		}
	}

	// �u���v�{�^����������Ă����琂���p�x���v���X����
	if( input->isDown2())
	{
		//AngleV += (float)input->isDown2()*CAMERA_ANGLE_SPEED ;
		AngleV += CAMERA_ANGLE_SPEED ;

		// ������p�x�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
		if( AngleV > DX_PI_F / 2.0f - 0.6f )
		{
			AngleV = DX_PI_F / 2.0f - 0.6f ;
		}
	}
	if(input->isPushed2()){
		AngleV = -20.0f * DX_PI_F/180.f;
	}
}


void Camera::Update(){
	VECTOR newTarget = VTransform(VGet(20.0f,0.f,0.f),MGetRotY(AngleH));
	// �J�����̍��W��ݒ�
	SetCameraPositionAndTarget_UpVecY(position,VAdd(target,newTarget));
	// SetCameraPositionAndTarget_UpVecY(VGet(500.f,600.f,0.f),target);
}

void Camera::DebugDraw(){
	DrawCapsule3D(position,VAdd(target,VGet(0.f,1.0f,0.f)),CAMERA_COLLISION_SIZE,0,GetColor(0,0,255),0,1);
}

Camera::~Camera(){

}

VECTOR Camera::GetPos(){
	return position;
}

VECTOR Camera::GetTarget(){
	return target;
}

float Camera::GetAngleH(){
	return AngleH;
}

float Camera::GetAngleV(){
	return AngleV;
}

void Camera::LockOn(Player* player,std::vector<Enemy*> *enemies,bool sameEnemyLockON){
	if(sameEnemyLockON && lockOnEnemy && beforeEnemySize == enemies->size()){
		if(lockOnEnemy){
			target = lockOnEnemy->GetPosition();
			/*
			VECTOR pPos = player->GetPosition();
			float takasa = target.y - pPos.y;
			float teihen = pow(target.x - pPos.x,2) + pow(target.z - pPos.z ,2);
			teihen = sqrt(teihen);
			AngleV = atan(takasa/teihen)*3.14;
			AngleV -= 0.44f;
			*/
		}	
	}else{
		beforeEnemySize = enemies->size();
		// ���������߂�
		float minDistance = LOCK_ON_DISTANCE;
		lockOnEnemy = 0;
		VECTOR pPos = player->GetPosition();
		for(int i=0;i<enemies->size();i++){
			VECTOR tempPos = enemies->at(i)->GetPosition();
			VECTOR distanceVec = VSub(pPos,tempPos);
			float tempDistance = VSize(distanceVec);
			if(minDistance > tempDistance){
				minDistance = tempDistance;
				lockOnEnemy = (*enemies)[i];	
			}
		}
		if(lockOnEnemy){
			target = lockOnEnemy->GetPosition();
			float takasa = target.y - pPos.y;
			float teihen = pow(target.x - pPos.x,2) + pow(target.z - pPos.z ,2);
			teihen = sqrt(teihen);
			AngleV = atan(takasa/teihen)*3.14/2.f;
			AngleV -= 0.44f;
		}	
	}
}


void Camera::CheckStageColl(Stage* stage){
	// �J�����̍��W�����肷��

	MATRIX RotZ, RotY ;
	float Camera_Player_Length ;
	MV1_COLL_RESULT_POLY_DIM HRes ;
	int HitNum ;

	// ���������̉�]�͂x����]
	RotY = MGetRotY( AngleH ) ;

	// ���������̉�]�͂y����] )
	RotZ = MGetRotZ( AngleV ) ;

	// �J��������v���C���[�܂ł̏����������Z�b�g
	Camera_Player_Length = 30.0f;

	// �J�����̍��W���Z�o
	// �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
	// ����������]( �y����] )���������Ɛ���������]( �x����] )���čX��
	// �����_�̍��W�𑫂������̂��J�����̍��W
	position = VAdd( VTransform( VTransform( VGet( -Camera_Player_Length, 0.0f, 0.0f ), RotZ ), RotY ), target ) ;

	
	// �����_����J�����̍��W�܂ł̊ԂɃX�e�[�W�̃|���S�������邩���ׂ�
	HRes = stage->CollCheckCapsule(position,VAdd(target,VGet(0.f,1.0f,0.f)),CAMERA_COLLISION_SIZE );
	HitNum = HRes.HitNum ;
	MV1CollResultPolyDimTerminate( HRes ) ;
	if( HitNum != 0 )
	{
		float NotHitLength ;
		float HitLength ;
		float TestLength ;
		VECTOR TestPosition ;

		// �������疳���ʒu�܂Ńv���C���[�ɋ߂Â�

		// �|���S���ɓ�����Ȃ��������Z�b�g
		NotHitLength = 0.0f ;

		// �|���S���ɓ����鋗�����Z�b�g
		HitLength = Camera_Player_Length ;
		do
		{
			// �����邩�ǂ����e�X�g���鋗�����Z�b�g( ������Ȃ������Ɠ����鋗���̒��� )
			TestLength = NotHitLength + ( HitLength - NotHitLength ) / 2.0f ;

			// �e�X�g�p�̃J�������W���Z�o
			TestPosition = VAdd( VTransform( VTransform( VGet( -TestLength, 0.0f, 0.0f ), RotZ ), RotY ), position ) ;

			// �V�������W�ŕǂɓ����邩�e�X�g
			HRes = stage->CollCheckCapsule(TestPosition,target,CAMERA_COLLISION_SIZE );
			HitNum = HRes.HitNum ;
			MV1CollResultPolyDimTerminate( HRes ) ;
			if( HitNum != 0 )
			{
				// ���������瓖���鋗���� TestLength �ɕύX����
				HitLength = TestLength ;
			}
			else
			{
				// ������Ȃ������瓖����Ȃ������� TestLength �ɕύX����
				NotHitLength = TestLength ;
			}

			// HitLength �� NoHitLength ���\���ɋ߂Â��Ă��Ȃ������烋�[�v
		}while( HitLength - NotHitLength > 0.1f ) ;

		// �J�����̍��W���Z�b�g
		position = TestPosition ;
	}
}