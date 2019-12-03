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
	int timer;			// �^�C�}�[
	Character* player;	// �v���C���[
	Stage* stage;		// �X�e�[�W
	Camera* camera;		// �J����
	char*	BGMHandle;		/**< BGB�̃������n���h��*/


	std::vector<Item*> *items;		// ����
	std::vector<Enemy*> *enemies;
public:
	// �R���X�g���N�^
	World();
	// �f�X�g���N�^
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