#include "JetItem.h"
#include "Player.h"

JetItem::JetItem(float x,float y,float z)
	:Item(x,y,z)
{
	// ModelHandle = MV1LoadModel("jet/jet.x");
	ModelHandle = MV1LoadModel("jetpack/jetpack.x");
	MV1SetPosition( ModelHandle, position ) ;
}


void JetItem::Effect(Player *chara){
	chara->SetJetMode();
	chara->ChangeModel("Jet");
}