#pragma once
#include "Stage.h"

class Player;
class Enemy;

class FirstStage:public Stage{
public:
	FirstStage();
	Player* CreatePlayer() ;
	void CreateEnemies(std::vector<Enemy*> *enemies,Player *player) ;
	void  CreateItems(std::vector<Item*> *items);
};