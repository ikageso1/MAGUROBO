#include "World4.h"
#include "Stage4.h"
#include "Stage.h"
#include "Camera.h"
#include "Player.h"
#include "Character.h"
#include "M95.h"
#include "JetItem.h"


World4::World4(Input* input){
	stage = new Stage4();			// ステージ生成
	player = stage->CreatePlayer();	// プレイヤー
	camera = new Camera(player);	// カメラ

	stage->CreateEnemies(enemies,(Player*)player);
	stage->CreateItems(items);

	// コントローラ設定
	((Player*)player)->SetInputAI(input);
	// BGM設定
	BGMHandle = "sound/nc95844.mp3";


}