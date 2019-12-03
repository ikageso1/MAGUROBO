#pragma once
#include "Stage.h"
class Stage4:public Stage{
public:
	Stage4();
	Player* CreatePlayer() ;
	void  CreateEnemies(std::vector<Enemy*> *enemies,Player *player) ;
	void  CreateItems(std::vector<Item*> *items);	
};