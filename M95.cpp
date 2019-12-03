#include "M95.h"
#include "Player.h"
#include "M95Weapon.h"

M95::M95(float x,float y,float z)
	:Item(x,y,z)
{
	ModelHandle = MV1LoadModel("weapon/M95.pmd");
	MV1SetPosition( ModelHandle, position ) ;
}

void M95::Effect(Player *chara){
	chara->SetWeapon(new M95Weapon());
	chara->ChangeModel("M95");
}