#include "SecondWorld.h"
#include "SecondStage.h"
#include "Stage.h"
#include "Camera.h"
#include "Player.h"
#include "Character.h"
#include "NormalEnemy.h"
#include "TraceEnemy.h"
#include "M95.h"
#include "JetItem.h"


SecondWorld::SecondWorld(Input* input){
	stage = new SecondStage();			// ステージ生成
	player = stage->CreatePlayer();	// プレイヤー
	camera = new Camera(player);	// カメラ
	stage->CreateEnemies(enemies,(Player*)player);
	stage->CreateItems(items);

	// コントローラ設定
	((Player*)player)->SetInputAI(input);
	// BGM設定
	BGMHandle = "sound/nc95844.mp3";


}