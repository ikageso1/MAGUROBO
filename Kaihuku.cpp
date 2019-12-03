#include "Kaihuku.h"
#include "Player.h"
#include "M95Weapon.h"

Kaihuku::Kaihuku(float x,float y,float z)
	:Item(x,y,z)
{
	ModelHandle = MV1LoadModel("kaihuku/jet.x");
	MV1SetPosition( ModelHandle, position ) ;
}

void Kaihuku::Effect(Player *chara){
	chara->Kaihuku(50);
}