#pragma once
#include "Item.h"

class Player;
class JetItem:public Item{
public:
	JetItem(float x,float y,float z);
	void Effect(Player *chara);
};