#pragma once
#include "Stage.h"

class Player;
class Enemy;

class SecondStage:public Stage{
public:
	SecondStage();
	Player* CreatePlayer() ;
	void  CreateEnemies(std::vector<Enemy*> *enemies,Player *player) ;
	void  CreateItems(std::vector<Item*> *items);
};