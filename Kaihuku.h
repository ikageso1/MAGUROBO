#pragma once
#include "Item.h"

class Kaihuku:public Item{
public:
	Kaihuku(float x,float y,float z);
	void Effect(Player *chara);
};