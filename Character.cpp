#include "Character.h"
#include <math.h>
#include "Stage.h"
#include "Weapon.h"
#include "AI.h"

#define GRAVITY 0.3f		// �d��


// �R���X�g���N�^
Character::Character(float x,float y,float z){
	// �������W�̐ݒ�
	StartPos = VGet( x,y,z ) ;
	Position = StartPos;
	hitbox.position = Position;
	// ��]�l�͂O
	Angle = 0.0f ;
	AngleV =0.0f ;
	
	// �ً}����͍ŏ���false
	isRoleRight = false;
	isRoleLeft = false;
	// ��]�l�͂O
	RoleAngle = 0.0f;
	// �e��������
	tama = new std::list<Tama*>(0);
	isJump = false;
	isJet = 0;
	isFire = false;
	jump = 0.0f;
	speed = 1.0f;
	UpMoveVec = VGet(1,0,0);
	LeftMoveVec = VGet(0,0,1);

	MaxHP = 100;
	HP = MaxHP;
	isAlive = true;
	// ���O�̐ݒ�
	name = "����������";

	HIT_SLIDE_LENGTH = 5.0f;
}

void Character::SetName(std::string name){
	this->name=name;
}

// �f�X�g���N�^
Character::~Character(){
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end(); ite++){
		delete *ite;
	}
	delete tama;
}

void Character::Damage(int damage){
	HP -= damage;
	if(HP<0)
		isAlive = false;
}

HitBox Character::GetHitBox(){
	return hitbox;
}

int Character::GetDamage(){
	return weapon->GetDamage();
}



bool Character::CollCheck(Character *chara2){
    HitBox eHitBox = chara2->GetHitBox();
	// �����̕�
	// ��]
	VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
	VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
	// �ړ�
	hitbox_front = VAdd(Position,hitbox_front);	
	hitbox_back = VAdd(Position,hitbox_back);

	// ����̕�
	// ��]
	VECTOR ehitbox_front = VTransform(eHitBox.front,MGetRotY(eHitBox.angle));
	VECTOR ehitbox_back = VTransform(eHitBox.back,MGetRotY(eHitBox.angle));
	// �ړ�
	ehitbox_front = VAdd(eHitBox.position,ehitbox_front);	
	ehitbox_back = VAdd(eHitBox.position,ehitbox_back);

	if(HitCheck_Capsule_Capsule(hitbox_front,hitbox_back,hitbox.r,ehitbox_front,ehitbox_back,eHitBox.r)==TRUE){

		// �������Ă����� ch �� chk ���痣��鏈��������
		VECTOR ch_MoveVec = VGet(0,0,0);
		VECTOR ChkChToChVec ;
		VECTOR PushVec ;
		VECTOR ChPosition ;
		float Length ;
		const float CHARA_HIT_PUSH_POWER = 80.0f ;
	
	
		// �ړ���� ch �̍��W���Z�o
		ChPosition = VAdd( Position, ch_MoveVec ) ;
        
		// chk_ch ���� ch �ւ̃x�N�g�����Z�o
		ChkChToChVec = VSub( ChPosition, chara2->GetPosition() ) ;
        
		// �x���͌��Ȃ�
		ChkChToChVec.y = 0.0f ;
        
		// ��l�̋������Z�o
		Length = VSize( ChkChToChVec ) ;
        
		// chk_ch ���� ch �ւ̃x�N�g���𐳋K��( �x�N�g���̒����� 1.0f �ɂ��� )
		PushVec = VScale( ChkChToChVec, 1.0f / Length ) ;
        
		// �����o���������Z�o�A������l�̋��������l�̑傫�����������l�ɉ����o���͂𑫂��ė���Ă��܂��ꍇ�́A�҂����肭���������Ɉړ�����
		//if( Length - hitbox.r * 2.0f + CHARA_HIT_PUSH_POWER > 0.0f )
		if(0)
		{
			float TempY ;
            
			TempY = ChPosition.y ;
			ChPosition = VAdd( chara2->GetPosition(), VScale( PushVec, hitbox.r * 2.0f ) ) ; 
            
			// �x���W�͕ω������Ȃ�
			ChPosition.y = TempY ;
		}
		else
		{
			// �����o��
			ChPosition = VAdd( ChPosition, VScale( PushVec, CHARA_HIT_PUSH_POWER ) ) ;
		}
		// �����蔻�菈����̈ړ��x�N�g�����Z�b�g
		MoveVec = VSub( ChPosition, Position ) ;
		return true;
	}
	return false;
}



// ����
void Character::Fall(){

	// �x�������̑��x���d�͕����Z����
	jump -= GRAVITY ;

	// �ړ��x�N�g���̂x�������x�������̑��x�ɂ���
	MoveVec.y += jump ;
	// �ޗ�����
	if(Position.y < -1000.f){
		Position = StartPos;
	}
}

void Character::Jump(){
	if(!isJump){
		// ��Ԃ��u�W�����v�v�ɂ���
		isJump = true;

		// �x�������̑��x���Z�b�g
		jump = JUMP_POWER;

		MoveVec.y += jump*3;

		MoveFlag = 1;
	}else{
		Jet();
	}
}

void Character::Jet(){
	if(isJet>0){
		jump += 0.35f;
		isJet -= 1;
	}
}

void Character::Attack(){
	if(isFire){
		weapon->CreateTama(Position,Angle,AngleV/2.f,tama);
	}
}

void Character::TamaMove(Stage *stg){
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end(); ite++){
		(*ite)->Move(stg);
	}
}

void Character::Draw(){
	MV1DrawModel(ModelHandle);
	
	

	// ��]
	VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
	VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
	// �ړ�
	hitbox_front = VAdd(Position,hitbox_front);	
	hitbox_back = VAdd(Position,hitbox_back);	


	// �e��`��
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end(); ite++){
		if((*ite)->GetAlive())
			(*ite)->Draw();
	}
}

void Character::TamaDeath(){
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end();){
		if(!(*ite)->GetAlive()){
			delete (*ite);
			ite = tama->erase(ite);
		}else{
			ite++;
		}
	}
}

// �L�����N�^�[�̌�����ς��鏈��
void Character::Rotate( void )
{
	float TargetAngle ;			// �ڕW�p�x
	float SaAngle ;				// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�

	// �ڕW�̕����x�N�g������p�x�l���Z�o����
	TargetAngle = atan2( Direction.x, Direction.z ) ;

	// �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
	{
		// �ŏ��͒P���Ɉ����Z
		SaAngle = TargetAngle - Angle ;

		// ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
		// ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
		if( SaAngle < -DX_PI_F )
		{
			SaAngle += DX_TWO_PI_F ;
		}
		else
			if( SaAngle > DX_PI_F )
			{
				SaAngle -= DX_TWO_PI_F ;
			}
	}

	// �p�x�̍����O�ɋ߂Â���
	if( SaAngle > 0.0f )
	{
		// �����v���X�̏ꍇ�͈���
		SaAngle -= ANGLE_SPEED ;
		if( SaAngle < 0.0f )
		{
			SaAngle = 0.0f ;
		}
	}
	else
	{
		// �����}�C�i�X�̏ꍇ�͑���
		SaAngle += ANGLE_SPEED ;
		if( SaAngle > 0.0f )
		{
			SaAngle = 0.0f ;
		}
	}

	// ���f���̊p�x���X�V
	Angle = TargetAngle - SaAngle ;
	MV1SetRotationXYZ( ModelHandle, VGet( 0.0f, Angle + DX_PI_F, 0.0f ) ) ;

}

void Character::CheckStageColl(Stage *stg){
	//if(!isRoleRight && !isRoleLeft) {
		int i, j, k ;						// �ėp�J�E���^�ϐ�
		int MoveFlag ;						// ���������Ɉړ��������ǂ����̃t���O( �O:�ړ����Ă��Ȃ�  �P:�ړ����� )
		int HitFlag ;						// �|���S���ɓ����������ǂ������L�����Ă����̂Ɏg���ϐ�( �O:�������Ă��Ȃ�  �P:�������� )
		MV1_COLL_RESULT_POLY_DIM HitDim ;			// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
		int KabeNum ;						// �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
		int YukaNum ;						// ���|���S���Ɣ��f���ꂽ�|���S���̐�
		MV1_COLL_RESULT_POLY *Poly ;				// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^( �g��Ȃ��Ă��ς܂����܂����v���O�����������Ȃ�̂ŁE�E�E )
		HITRESULT_LINE LineRes ;				// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
		VECTOR OldPos ;						// �ړ��O�̍��W	
		VECTOR NowPos ;						// �ړ���̍��W
		std::vector<MV1_COLL_RESULT_POLY*> Kabe;
		std::vector<MV1_COLL_RESULT_POLY*> Yuka; 

		// �ړ��O�̍��W��ۑ�
		OldPos = Position ;

		// �ړ���̍��W���Z�o
		NowPos = VAdd( Position, MoveVec ) ;

		// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
		// ( ���o����͈͈͂ړ��������l������ )
		HitDim = stg->GetStagePoly(Position,ENUM_DEFAULT_SIZE + VSize( MoveVec ));


		//VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle )));
		//VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle )));

		// ��]
		VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
		VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
		// �ړ�
		hitbox_front = VAdd(NowPos,hitbox_front);	
		hitbox_back = VAdd(NowPos,hitbox_back);	
		//VECTOR hitbox_front = hitbox.front;
		//VECTOR hitbox_back = hitbox.back;



		
		// (1) ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f����
		JudgeFlootOrWall(HitDim,&Kabe,&Yuka);


		// (2) �ǃ|���S���Ƃ̓����蔻�菈��
		NowPos = AttachWall(&Kabe);


		YukaNum = Yuka.size();
		// (3) ���|���S���Ƃ̓����蔻��
		if( YukaNum != 0 ){
			float MaxY ;

			// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
			HitFlag = 0 ;

			// ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
			MaxY = 0.0f ;

			// ���|���S���̐������J��Ԃ�
			for( i = 0 ; i < YukaNum ; i ++ ){
				// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
				Poly = Yuka[ i ] ;

				// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
				LineRes = HitCheck_Line_Triangle( VAdd( NowPos, VGet( 0.0f, HIT_HEIGHT, 0.0f ) ), 
					VAdd( NowPos, VGet( 0.0f, -40.0f, 0.0f ) ), Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) ;

				// �������Ă��Ȃ������牽�����Ȃ�
				if( LineRes.HitFlag == FALSE ) continue ;

				// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
				if( HitFlag == 1 && MaxY > LineRes.Position.y ) continue ;

				// �|���S���ɓ��������t���O�𗧂Ă�
				HitFlag = 1 ;

				// �ڐG�����x���W��ۑ�����
				MaxY = LineRes.Position.y ;
			}

			// ���|���S���ɓ����������ǂ����ŏ����𕪊�
			if( HitFlag == 1 && MoveVec.y < 0){
				// ���������ꍇ
				// �x�������̈ړ����x�͂O��
				MoveVec.y = 0.0f ;
				jump = 0.0f;

				// �����W�����v���������ꍇ�͒��n��Ԃɂ���
				if(isJump)
				{
					isJump = false; 
				}	
				// �ڐG�����|���S���ň�ԍ����x���W���v���C���[�̂x���W�ɂ���
				NowPos.y = MaxY ;
			}
			else{
				// ���R���W�����ɓ������Ă��Ȃ��Ċ��W�����v��Ԃł͂Ȃ������ꍇ��
				if( !isJump)
				{
					// �W�����v���ɂ���
					isJump = true;
					jump = 0;
				}

			}

		}
		// �V�������W��ۑ�����
		Position = NowPos ;

		// �v���C���[�̃��f���̍��W���X�V����
		MV1SetPosition( ModelHandle, Position ) ;

		// ���o�����v���C���[�̎��͂̃|���S�������J������
		MV1CollResultPolyDimTerminate( HitDim ) ;
	//}
}


void Character::JudgeFlootOrWall(MV1_COLL_RESULT_POLY_DIM &HitDim,
	std::vector<MV1_COLL_RESULT_POLY*> *Kabe,
	std::vector<MV1_COLL_RESULT_POLY*> *Yuka){

		// ���o���ꂽ�|���S���̐������J��Ԃ�
		for(int i = 0 ; i < HitDim.HitNum ; i ++ )
		{
			// �w�y���ʂɐ������ǂ����̓|���S���̖@���̂x�������O�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
			// if( HitDim.Dim[ i ].Normal.y < 0.000001f && HitDim.Dim[ i ].Normal.y > -0.000001f )
			// if( HitDim.Dim[ i ].Normal.y < 0.1f && HitDim.Dim[ i ].Normal.y > -0.1f )
			if( HitDim.Dim[ i ].Normal.y < 0.0f)
			{
				// �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�v���C���[�̂x���W�{�P�D�O����荂���|���S���̂ݓ����蔻����s��
				if( HitDim.Dim[ i ].Position[ 0 ].y > Position.y + 1.0f ||
					HitDim.Dim[ i ].Position[ 1 ].y > Position.y + 1.0f ||
					HitDim.Dim[ i ].Position[ 2 ].y > Position.y + 1.0f )
				{

					// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
					Kabe->push_back( &HitDim.Dim[ i ]);
				}
			}
			else
			{
				// �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
				Yuka->push_back(&HitDim.Dim[ i ] );
			}
		}
}

VECTOR Character::AttachWall(std::vector<MV1_COLL_RESULT_POLY*> *Kabe){
	int HitFlag;
	int KabeNum = Kabe->size();
	int j;
	MV1_COLL_RESULT_POLY *Poly ;				// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^( �g��Ȃ��Ă��ς܂����܂����v���O�����������Ȃ�̂ŁE�E�E )
	int MoveFlag;
	VECTOR OldPos ;						// �ړ��O�̍��W	
	VECTOR NowPos ;						// �ړ���̍��W

	// x����z�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v�t���O���P�ɂ���
	if( fabs( MoveVec.x ) > 0.01f || fabs( MoveVec.z ) > 0.01f )
	{
		MoveFlag = 1 ;
	}
	else
	{
		MoveFlag = 0 ;
	}

	// �ړ��O�̍��W��ۑ�
	OldPos = Position ;

	// �ړ���̍��W���Z�o
	NowPos = VAdd( Position, MoveVec ) ;

	// ��]
	VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
	VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
	// �ړ�
	hitbox_front = VAdd(NowPos,hitbox_front);	
	hitbox_back = VAdd(NowPos,hitbox_back);	

	if( KabeNum != 0 )
	{
		// �ǂɓ����������ǂ����̃t���O�͏�����Ԃł́u�������Ă��Ȃ��v�ɂ��Ă���
		HitFlag = 0 ;

		// �ړ��������ǂ����ŏ����𕪊�
		if( MoveFlag == 1 )
		{
			// �ǃ|���S���̐������J��Ԃ�
			for( int i = 0 ; i < KabeNum ; i ++ )
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				Poly = (*Kabe)[i];

				// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
				if( HitCheck_Capsule_Triangle(  hitbox_front,hitbox_back,
					HIT_WIDTH, Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) == FALSE ) continue ;

				// �����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
				HitFlag = 1 ;

				// �ǂɓ���������ǂɎՂ��Ȃ��ړ������������ړ�����
				{
					VECTOR SlideVec ;	// �v���C���[���X���C�h������x�N�g��

					// �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o
					SlideVec = VCross( MoveVec, Poly->Normal ) ;

					// �Z�o�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o�A���ꂪ
					// ���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g��
					SlideVec = VCross( Poly->Normal, SlideVec ) ;

					// ������ړ��O�̍��W�ɑ��������̂�V���ȍ��W�Ƃ���
					NowPos = VAdd( OldPos, SlideVec ) ;
				}
				hitbox_front = VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle )));
				hitbox_back = VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle )));

				// �V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
				
				for( j = 0 ; j < KabeNum ; j ++ )
				{
					// j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					Poly = (*Kabe)[ j ] ;

					// �������Ă����烋�[�v���甲����
					if( HitCheck_Capsule_Triangle( hitbox_front,hitbox_back,
						HIT_WIDTH, Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) == TRUE ) break ;
				}

				// j �� KabeNum �������ꍇ�͂ǂ̃|���S���Ƃ�������Ȃ������Ƃ������ƂȂ̂�
				// �ǂɓ��������t���O��|������Ń��[�v���甲����
				if( j == KabeNum )
				{
					HitFlag = 0 ;
					break ;
				}
			}
		}
		else
		{
			// �ړ����Ă��Ȃ��ꍇ�̏���

			// �ǃ|���S���̐������J��Ԃ�
			for( int i = 0 ; i < KabeNum ; i ++ )
			{
				// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
				Poly = (*Kabe)[ i ] ;

				// �|���S���ɓ������Ă����瓖�������t���O�𗧂Ă���Ń��[�v���甲����
				if( HitCheck_Capsule_Triangle( hitbox_front,hitbox_back,
					HIT_WIDTH, Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) == TRUE )
				{
					HitFlag = 1 ;
					break ;
				}
			}
		}

		// �ǂɓ������Ă�����ǂ��牟���o���������s��
		if( HitFlag == 1 )
		{
			// �ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
			for(int k = 0 ; k < HIT_TRYNUM ; k ++ )
			{
				int i;
				// �ǃ|���S���̐������J��Ԃ�
				for(i = 0 ; i < KabeNum ; i ++ )
				{
					// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					Poly = (*Kabe)[ i ] ;

					// �v���C���[�Ɠ������Ă��邩�𔻒�
					if( HitCheck_Capsule_Triangle(hitbox_front,hitbox_back,
						HIT_WIDTH, Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) == FALSE ) continue ;

					// �������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
					NowPos = VAdd( NowPos, VScale( Poly->Normal, HIT_SLIDE_LENGTH ) ) ;
					hitbox_front = VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle )));
					hitbox_back = VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle )));


					// �ړ�������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
					for( j = 0 ; j < KabeNum ; j ++ )
					{
						// �������Ă����烋�[�v�𔲂���
						Poly = (*Kabe)[ j ] ;
						if( HitCheck_Capsule_Triangle( hitbox_front,hitbox_back,
							HIT_WIDTH, Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) == TRUE ) break ;
					}

					// �S�Ẵ|���S���Ɠ������Ă��Ȃ������炱���Ń��[�v�I��
					if( j == KabeNum ) break ;
				}

				// i �� KabeNum �ł͂Ȃ��ꍇ�͑S���̃|���S���ŉ����o�������݂�O�ɑS�Ă̕ǃ|���S���ƐڐG���Ȃ��Ȃ����Ƃ������ƂȂ̂Ń��[�v���甲����
				if( i != KabeNum ) break ;
			}
		}
	}

	return NowPos;
}

// �ً}���
void Character::Role(){
	float AngleSpeed = 0.f;
	if(isRoleRight){
		AngleSpeed = -ROLE_SPEED ;
	}
	else if(isRoleLeft){
		AngleSpeed = ROLE_SPEED;
	}else{
		// �֐��𔲂���
		return ;
	}
	RoleAngle += AngleSpeed;

	MATRIX addPos = MGetTranslate(VGet(0.f,-3.2f,0.f));
	MATRIX temp = MMult(addPos,MGetRotZ(AngleSpeed));
	temp = MMult(temp ,MInverse(addPos));
	temp = MMult(temp, MV1GetMatrix(ModelHandle));
	MATRIX roleMove;
	if(AngleSpeed < 0){
		roleMove =  MGetTranslate(VScale(LeftMoveVec,2.0f));
	}else{
		roleMove =  MGetTranslate(VScale(LeftMoveVec,-2.0f));
	}
	temp = MMult(temp,roleMove);
	Position = VTransform(Position,roleMove);
	MV1SetMatrix(ModelHandle,temp);

	if(isRoleRight && RoleAngle <= -DX_TWO_PI_F ){
		RoleAngle = 0.0f;
		isRoleRight=false;
		MV1SetMatrix(ModelHandle,MGetIdent());
	}
	else if(isRoleLeft && RoleAngle >= DX_TWO_PI_F ){
		RoleAngle = 0.0f;
		isRoleLeft=false;
		MV1SetMatrix(ModelHandle,MGetIdent());
	}
}

VECTOR Character::GetPosition(){
	return Position;
}

// �l����
void Character::Think(){
	directionFlag = ai->decideMove();
	isFire = ai->doFire();
}

bool Character::GetisAlive(){
	return isAlive;
}

// �ړ�
void Character::Move() {
	MoveFlag  = 0;			// �ړ��������ǂ����̃t���O( 1:�ړ�����  0:�ړ����Ă��Ȃ� )
	MoveVec = VGet( 0.0f, 0.0f, 0.0f ) ;				// ���̃t���[���̈ړ��x�N�g��


	// ���[�g�t���[���̂y�������̈ړ��p�����[�^�𖳌��ɂ���
	{
		MATRIX LocalMatrix ;

		// ���[�U�[�s�����������
		MV1ResetFrameUserLocalMatrix( ModelHandle, 2 ) ;

		// ���݂̃��[�g�t���[���̍s����擾����
		LocalMatrix = MV1GetFrameLocalMatrix( ModelHandle, 2 ) ;

		// �y�������̕��s�ړ������𖳌��ɂ���
		LocalMatrix.m[ 3 ][ 2 ] = 0.0f ;

		// ���[�U�[�s��Ƃ��ĕ��s�ړ������𖳌��ɂ����s������[�g�t���[���ɃZ�b�g����
		MV1SetFrameUserLocalMatrix( ModelHandle, 2, LocalMatrix ) ;
	}

	// �v���C���[�̈ړ�����
	// ������
	if( directionFlag.left )
	{
		float move = -(float)directionFlag.left/1000.0f;
		move *= speed;
		// �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
		MoveVec = VAdd( MoveVec, VScale( LeftMoveVec, move )) ;
		// �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
		MoveFlag = 1 ;
	}

	//�E����
	if( directionFlag.right)
	{
		float move = (float)directionFlag.right /1000.0f;
		move *= speed;
		// �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g���𔽓]�������̂����Z����
		MoveVec = VAdd( MoveVec, VScale( LeftMoveVec, move )) ;
		// �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
		MoveFlag = 1 ;
	}

	// �O����
	if( directionFlag.front )
	{
		float move = (float)directionFlag.front /1000.0f;
		move *= speed;
		// �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
		MoveVec = VAdd( MoveVec, VScale( UpMoveVec, move ) ) ;
		// �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
		MoveFlag = 1 ;
	}

	// �����
	if( directionFlag.back )
	{
		float move = -(float)directionFlag.back/1000.0f;
		move *= speed;
		// �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g���𔽓]�������̂����Z����
		MoveVec = VAdd( MoveVec, VScale(UpMoveVec,move)) ;
		// �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
		MoveFlag = 1 ;
	}
	// �ً}����L�[�������ꂽ
	if(!isRoleRight &&  directionFlag.roleRight){
		isRoleRight = true;	// �ً}����t���O��on�ɂ���
	}
	if(!isRoleLeft && directionFlag.roleLeft ){
		isRoleLeft = true;
	}

	// �v���C���[�̏�Ԃ��u�W�����v�v�ł͂Ȃ��A���{�^��2��������Ă�����W�����v����
	if( directionFlag.jump )
	{
		Jump();

	}
	// ������ݒ�
	if(MoveFlag){
		Direction = VNorm(MoveVec);
	}
}

// �ړ��X�V
void Character::UpdatePosition(){
	if(!isRoleRight && !isRoleLeft) {
		// �ړ��{�^���������ꂽ�ꍇ�Ɉړ�����
		if( MoveFlag )
		{
			// �������w��
			Direction = VNorm( UpMoveVec ) ;
			// �ړ�
			Position = VAdd(Position,MoveVec);	
		}
		// �v���C���[�̃��f���̍��W���X�V����
		MV1SetPosition( ModelHandle, Position ) ;
		hitbox.position = Position;
		hitbox.angle = Angle;
	}
}



bool Character::TamaCollCheck(Character* target){
	bool flag = false;
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end();ite++){
		if((*ite)->CollCheck(target)){
			flag = true;
			target->Damage(weapon->GetDamage());
		}
	}
	return flag;
}


void Character::SetWeapon(Weapon* w){
	if(weapon)
		delete weapon;
	weapon = w;
}