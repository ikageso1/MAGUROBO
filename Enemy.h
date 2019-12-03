#pragma once
#include "DxLib.h"
#include "Input.h"
#include "Tama.h"
#include "Character.h"
#include <vector>

class Stage;


class Enemy :public Character{
protected:
	bool isDraw;
public:
	Enemy(float x,float y, float z);			// コンストラクタ
	~Enemy();			// デストラクタ
	void SetDirection(VECTOR target,VECTOR pos);
	void Draw();
	void SetisDraw();
	void ResetisDraw();
};