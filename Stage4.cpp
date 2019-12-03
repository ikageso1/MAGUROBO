#include "Stage4.h"
#include "Player.h"
#include "Ika.h"
#include "M95.h"
#include "JetItem.h"
#include "Kaihuku.h"

// �R���X�g���N�^
Stage4::Stage4(){
	 
	// �X�e�[�W�ǂݍ���
	//LoadStage("stage/stage5/stage55.mqo") ;
	//LoadStage("stage/stage3/minecraft.mqo");
	LoadStage("stage/stage1/stage3.mqo");


	// ���W�ݒ�
	MV1SetPosition(ModelHandle,VGet(0,0,0));
}



Player* Stage4::CreatePlayer(){
	return new Player(10.0f,0.f,10.0f);
}
void Stage4::CreateEnemies(std::vector<Enemy*> *enemies,Player *player){
	enemies->push_back(new Ika(25.f,0.f,100.f));
	enemies->push_back(new Ika(0.f,0.f,125.f));
	enemies->push_back(new Ika(-25.f,0.f,100.f));
}

void Stage4::CreateItems(std::vector<Item*> *items){
	items->push_back(new Kaihuku(0.f,-25.f,-50.f));
}