#include "IkaTama.h"
#include "Stage.h"

#define HANKEI  1.5f
#define SPEED	10.0f
#define DISTANCE 200

IkaTama::IkaTama(VECTOR playerPosition,float HAngle,float VAngle,bool isRight)
	:Tama(playerPosition,HAngle,VAngle)
{
	if(isRight){
		position = VAdd(playerPosition,VTransform(VGet(2.0f,0,0),MGetRotY(HAngle)));
	}
	else{
		position = VAdd(playerPosition,VTransform(VGet(-2.0f,0,0),MGetRotY(HAngle)));
	}

	position = VAdd(position,VGet(0.0f,5.0f,0.0f));

	moveVec = VGet(0.0f,0.0f,SPEED);
	// ���������ւ̉�]
	moveVec = VTransform(moveVec,MGetRotX(VAngle));
	// ���������ւ̉�]
	moveVec = VTransform(moveVec,MGetRotY(HAngle));

	r = HANKEI;
}

void IkaTama::Move(Stage *stg){
	if(isAlive){
		timer++;
		position = VAdd(position,moveVec);
		if(timer >= DISTANCE){
			isAlive = false;
		}
		MV1_COLL_RESULT_POLY_DIM HitPolyDim = stg->GetStagePoly(position,r );
		if(	HitPolyDim.HitNum ){
			isAlive = false;
		}
		// �����蔻����̌�n��
        MV1CollResultPolyDimTerminate( HitPolyDim ) ;
	}
}