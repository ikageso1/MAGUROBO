#include "NormalTama.h"
#include "Stage.h"

#define HANKEI  1.5f
#define SPEED	5.0f
#define DISTANCE 120

NormalTama::NormalTama(VECTOR playerPosition,float HAngle,float VAngle)
	:Tama(playerPosition,HAngle,VAngle)
{
	position = VAdd(playerPosition,VGet(0.0f,5.0f,0.0f));
	moveVec = VGet(0.0f,0.0f,SPEED);
	// ‚’¼•ûŒü‚Ö‚Ì‰ñ“]
	moveVec = VTransform(moveVec,MGetRotX(VAngle));
	// …•½•ûŒü‚Ö‚Ì‰ñ“]
	moveVec = VTransform(moveVec,MGetRotY(HAngle));

	r = HANKEI;
}

void NormalTama::Move(Stage *stg){
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
		// “–‚½‚è”»’èî•ñ‚ÌŒãn––
        MV1CollResultPolyDimTerminate( HitPolyDim ) ;
	}
}