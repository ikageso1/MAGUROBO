#pragma once
class Character;

struct Direction{
	bool	stop;
	bool	jump;
	int		front;
	int		right;
	int		back;
	int		left;
	bool	roleRight;
	bool	roleLeft;
	// コンストラクタ
	Direction():left(false),jump(false),
	front(false),right(false),back(false),
	roleRight(false),roleLeft(false)
	{

	}
};

class AI{
public:
	// 純粋仮想関数
	virtual Direction decideMove()=0;
	virtual bool doFire() = 0;
};