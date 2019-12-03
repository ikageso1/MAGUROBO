#include "SecondStage.h"
#include "Player.h"
#include "TraceEnemy.h"
#include "NormalEnemy.h"
#include "M95.h"
#include "JetItem.h"
#include "Item.h"

// コンストラクタ
SecondStage::SecondStage(){
	 
	// ステージ読み込み
	//LoadStage("stage/stage5/stage55.mqo") ;
	LoadStage("stage/stage2/stage.x");
	//LoadStage("stage/stage3/minecraft.mqo");
	//LoadStage("stage/stage1/stage12.mqo");
	
	// 座標設定
	MV1SetPosition(ModelHandle,VGet(0,0,0));
}



Player* SecondStage::CreatePlayer(){
	return new Player(10.0f,0.f,10.0f);
}

void SecondStage::CreateEnemies(std::vector<Enemy*> *enemies,Player *player){
	enemies->push_back(new NormalEnemy(0.0f,0.0f,-100.0f));
	enemies->push_back(new NormalEnemy(100.f,0.f,0.f));
	enemies->push_back(new TraceEnemy(-100.0f,0.0f,-100.0f,player));
	enemies->push_back(new TraceEnemy(100.f,50.f,100.f,player));
}

void  SecondStage::CreateItems(std::vector<Item*> *items){
	items->push_back(new M95(0.f,-50.f,100.f));
	items->push_back(new JetItem(0.f,-25.f,-100.f));
}