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
	Enemy(float x,float y, float z);			// �R���X�g���N�^
	~Enemy();			// �f�X�g���N�^
	void SetDirection(VECTOR target,VECTOR pos);
	void Draw();
	void SetisDraw();
	void ResetisDraw();
};