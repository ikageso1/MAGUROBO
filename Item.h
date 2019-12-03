#pragma once
#include "DxLib.h"
class Player;
class Character;

class Item{
protected:
	VECTOR position;
	bool isAvailable;
	int ModelHandle;
	float angleSpeed;
	float  r;			// �����蔻��̔��a
	float Angle;		// �p�x
public:
	Item(float x,float y,float z);
	bool CollCheck(Character *chara);
	void Draw();
	bool GetAvailavle();
	void Rotate();
	virtual void Effect(Player *chara)=0;
};