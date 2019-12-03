#pragma once
#include "Item.h"
class Player;

class M95:public Item{
public:
	M95(float x,float y,float z);
	void Effect(Player *chara);
};