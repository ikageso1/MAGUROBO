#include "M95Tama.h"
#include "Stage.h"

#define HANKEI  1.5f
#define SPEED	5.0f
#define DISTANCE 120

M95Tama::M95Tama(VECTOR playerPosition,float HAngle,float VAngle,bool isRight)
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
	// 垂直方向への回転
	moveVec = VTransform(moveVec,MGetRotX(VAngle));
	// 水平方向への回転
	moveVec = VTransform(moveVec,MGetRotY(HAngle));

	r = HANKEI;
}

void M95Tama::Move(Stage *stg){
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
		// 当たり判定情報の後始末
        MV1CollResultPolyDimTerminate( HitPolyDim ) ;
	}
}