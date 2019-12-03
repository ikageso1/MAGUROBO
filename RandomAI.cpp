#include "RandomAI.h"
#include "DxLib.h"

#define TIME_LIMIT 60

RandomAI::RandomAI(){
	this->moveTimer = 0;
}

Direction RandomAI::decideMove(){
	if( moveTimer++ >= TIME_LIMIT){
		moveTimer = 0;
		switch(GetRand(3)){
		case 0:
			dire.front = 1000;
			dire.right = 0;
			dire.back = 0;
			dire.left = 0;
			break;
		case 1:
			dire.right = 1000;
			dire.front = 0;
			dire.back = 0;
			dire.left = 0;
			break;
		case 2:
			dire.back = 1000;
			dire.right = 0;
			dire.front = 0;
			dire.left = 0;
			break;
		case 3:
			dire.left = 1000;
			dire.right = 0;
			dire.back = 0;
			dire.front = 0;
			break;
		}		// •ûŒü
	}
	if(GetRand(1)){
		
	}
	// 0:ª 1:¨  2:«  3:©
	return dire;
}

bool RandomAI::doFire(){
	// 10‚Ô‚ñ‚Ì‚¢‚¿
	if(!GetRand(9)){
		return true;
	}
	return false;
}

