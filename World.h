#pragma once
#include <vector>

class Stage;
class Character;
class Camera;
class Input;
class Enemy;
class Item;

class World{
protected:
	bool isGameClear;
	bool isGameOver;
	int timer;			// タイマー
	Character* player;	// プレイヤー
	Stage* stage;		// ステージ
	Camera* camera;		// カメラ
	char*	BGMHandle;		/**< BGBのメモリハンドル*/


	std::vector<Item*> *items;		// 武器
	std::vector<Enemy*> *enemies;
public:
	// コンストラクタ
	World();
	// デストラクタ
	~World();
	
	int Process(Input* input);
	void Draw();
	void CheckItem();
	void CheckDeath();
	void GameClear();
	void GameOver();
	void StartBGM();
	void StopBGM();
};