#include "FirstStage.h"
#include "Player.h"
#include "NormalEnemy.h"
#include "TraceEnemy.h"
#include "M95.h"
#include "JetItem.h"
#include "Kaihuku.h"

// コンストラクタ
FirstStage::FirstStage(){
	 
	// ステージ読み込み
	//LoadStage("stage/stage5/stage55.mqo") ;
	//LoadStage("stage/stage3/minecraft.mqo");
	LoadStage("stage/stage1/stage12.mqo");


	// 座標設定
	MV1SetPosition(ModelHandle,VGet(0,0,0));
}



Player* FirstStage::CreatePlayer(){
	return new Player(10.0f,0.f,10.0f);
}
void FirstStage::CreateEnemies(std::vector<Enemy*> *enemies,Player *player){
	enemies->push_back(new NormalEnemy(0.0f,0.0f,-100.0f));
	enemies->push_back(new NormalEnemy(100.f,0.f,0.f));
	enemies->push_back(new NormalEnemy(-100.0f,0.0f,-100.0f));
	enemies->push_back(new NormalEnemy(100.f,0.f,100.f));

	enemies->push_back(new NormalEnemy(-524.f,-30.f,-316.f));
	enemies->push_back(new NormalEnemy(638.f,-100.f,-224.f));
}

void FirstStage::CreateItems(std::vector<Item*> *items){
	items->push_back(new M95(0.f,-70.f,100.f));
	items->push_back(new M95(-1444.f,-138.f,262.f));
	

	items->push_back(new JetItem(0.f,-25.f,-100.f));
	items->push_back(new JetItem(-406.f,-70.f,-842.f));

	items->push_back(new Kaihuku(-200.f,-74.f,-200.f));
	items->push_back(new Kaihuku(453.f,-70.f,210.f));
}