#pragma once
#include "Stage.h"
#include "Camera.h"
#include "Input.h"
#include "Title.h"
#include "Character.h"
class Menu;
class Pause;
class World;
class Option;

namespace FLAG{
	enum{
		TITLE, /**<タイトル画面 */
		STAGE, /**< ステージ画面 */
		PAUSE, /**< ポーズ画面 */
		MENU,
		STAGESELECT,
		OPTION,
		CLEAR,
		GAMEOVER
	};
}

class Game{
private:
	Option *option;
	Menu* menu;			/**< メニュー */
	Input* input;		/**< キー入力 */
	Title* title;		/**< タイトル */
	Pause *pause;		/**< ポーズ画面 */
	World* world;
	int mainflag;		// ゲームメインフラグ
	int stageNum;		
	int zanki;		
public:
	/**
	* コンストラクタ ゲーム全般にかかわる初期化
	* (ステージ生成,コントローラー,プレイヤー（キャラ）,カメラ,画面)
	*/
	Game();	
	/**
	* デストラクタ　ゲーム全般に関わるオブジェクトの消去
	* (ステージ生成,コントローラー,プレイヤー（キャラ）,カメラ,画面)
	*/
	~Game();
	/**
	 * ゲーム全般の処理をする関数
	 */
	void MainLoop();
	void GameOver();
	void GameClear();
};