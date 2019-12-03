#include "TraceAI.h"
#include "Player.h"

TraceAI::TraceAI(Player* player,Character *myChara){
	this->player = player;
	this->myChara = myChara;	
}

Direction TraceAI::decideMove(){
	VECTOR playerPos = player->GetPosition();
	VECTOR pos = myChara->GetPosition();
	if(pos.x < playerPos.x - 1){
		dire.front=1000;
		dire.back=0;
	}else if( pos.x  > playerPos.x+1 ){
		dire.back=1000;
		dire.front=0;
	}
	else{
		dire.back=0;
		dire.front=0;
	}

	if(pos.z < playerPos.z - 1){
		dire.left= 0;
		dire.right=1000;


	}else if(pos.z > playerPos.z + 1){
		dire.right=0;
		dire.left=1000;


	}else{
		dire.right=0;
		dire.left=0;

	}
	if(pos.y<playerPos.y-100){
		dire.jump = 1000;
	}else{
		dire.jump = 0;
	}
	return dire;
}

bool TraceAI::doFire(){
	// 60‚Ô‚ñ‚Ì‚¢‚¿
	if(GetRand(50)==0){
			return true;
	}
	return false;
}