#include "Game.h"
#include "Pause.h"
#include "Player.h"
#include "JoypadInput.h"
#include "KeyBoardInput.h"
#include "Menu.h"
#include "Option.h"
#include "FirstWorld.h"
#include "SecondWorld.h"
#include "ThirdWorld.h"
#include "World4.h"


// コンストラクタ
Game::Game(){
	world = 0;
	menu = 0;
	option = new Option();
	if(GetJoypadNum() ){
		input = new JoypadInput();	// コントローラー
	}
	else{
		input = new KeyBoardInput();
	}

	title = new Title();			// タイトル画面
	pause = new Pause();			// ポーズ画面

	mainflag = FLAG::TITLE;	// 最初の画面はタイトル
	zanki = 2;
}

// ＤＥＡＴＨとらくた
Game::~Game(){
	delete input;
	delete title;
	delete menu;
	delete option;
}

// まいんるーぷ
void Game::MainLoop(){
	while( ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE)==0){		// メインループ
		ClearDrawScreen();				// 画面を消去
		input->update();				// 入力状態更新
		// タイトル画面
		if(mainflag == FLAG::TITLE){
			title->process(input);			// タイトル画面処理
			if(title->isFinish()){
				mainflag = FLAG::MENU;		// ステージに移行
				if(menu)
					delete menu;
				menu = new Menu();				//メニュー
			}
		}
		else if(mainflag==FLAG::MENU){
			if(menu->start(input)){
				switch(menu->getSelectChoice()){
				case 1:
					mainflag=FLAG::STAGE;
					stageNum = 1;
					world = new FirstWorld(input);
					world->StartBGM();
					break;
				case 2:
					mainflag=FLAG::STAGESELECT;
					menu->ChengeSelectStageMenu();
					break;
				case 3:
					mainflag=FLAG::OPTION;
					break;
				case 4:
					throw "END";
					break;
				}
			}
		}
		else if(mainflag==FLAG::STAGESELECT){
			if(menu->start(input)){
				switch(menu->getSelectChoice()){
				case 1:
					mainflag=FLAG::STAGE;
					stageNum = 1;
					world = new FirstWorld(input);
					world->StartBGM();
					break;
				case 2:
					mainflag=FLAG::STAGE;
					stageNum = 2;
					world = new SecondWorld(input);
					world->StartBGM();
					break;
				case 3:
					mainflag=FLAG::STAGE;
					stageNum = 3;
					world = new ThirdWorld(input);
					world->StartBGM();
					break;
				case 4:
					mainflag=FLAG::STAGE;
					stageNum = 4;
					world = new World4(input);
					world->StartBGM();
					break;
				}
			}
		}
		// オプション
		else if(mainflag==FLAG::OPTION){
			if(option->start(input)){
				switch(option->getSelectChoice()){
				case 1:
					option->setZanki(input);
					break;
				case 2:
					mainflag=FLAG::MENU;
					break;
				}
			}
			switch(option->getSelectChoice()){
			case 1:
				option->setZanki(input);
				break;
			}
		}
		// ステージ画面
		else if(mainflag == FLAG::STAGE){
			switch( world->Process(input) ){
				// クリアー 
			case 1:
				stageNum += 1;
				delete world;
				switch(stageNum){
				case 1:
					world = new FirstWorld(input);
					break;
				case 2:
					world = new SecondWorld(input);
					break;
				case 3:
					world = new ThirdWorld(input);
					break;
				case 4:
					world = new World4(input);
					break;
				case 5:
					mainflag = FLAG::CLEAR;
					break;
				}
				break;
				// 死亡
			case 2:
				zanki -= 1;
				delete world;

				if(zanki < 0){
					mainflag = FLAG::GAMEOVER;
				}else{
					switch(stageNum){
					case 1:
						world = new FirstWorld(input);
						break;
					case 2:
						world = new SecondWorld(input);
						break;
					case 3:
						world = new ThirdWorld(input);
						break;
					case 4:
						world = new World4(input);
						break;
					}
				}
				break;
			}
			// ポーズ画面への遷移処理
			if(input->isEdgeStartButton()){
				mainflag = FLAG::PAUSE;
			}

		}
		else if(mainflag==FLAG::GAMEOVER){
			DrawFormatString(300,300,GetColor(255,255,255),"げーむおーばー");
			ScreenFlip();
			WaitTimer(1000);
			zanki = 3;
			mainflag = FLAG::TITLE;
			if(title)
				delete title;
			title = new Title();
		}
		else if(mainflag==FLAG::CLEAR){
			DrawFormatString(300,300,GetColor(255,255,255),"くりあー!!!");
			ScreenFlip();
			WaitTimer(1000);
			zanki = 3;
			mainflag = FLAG::TITLE;
			if(title)
				delete title;
			title = new Title();
		}
		// ポーズ画面
		else if(mainflag == FLAG::PAUSE){
			world->Draw();
			// ポーズ処理
			pause->Process(input);
			// ゲーム画面への遷移処理
			if(pause->isFinish()){
				mainflag = FLAG::STAGE;
			}
		}
		ScreenFlip();				// 裏画面を適用
	}
}