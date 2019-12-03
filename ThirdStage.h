#pragma once
#include "Stage.h"

class Player;
class Enemy;

class ThirdStage:public Stage{
public:
	ThirdStage();
	Player* CreatePlayer() ;
	void  CreateEnemies(std::vector<Enemy*> *enemies,Player *player) ;
	void  CreateItems(std::vector<Item*> *items);
};