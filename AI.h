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
	// �R���X�g���N�^
	Direction():left(false),jump(false),
	front(false),right(false),back(false),
	roleRight(false),roleLeft(false)
	{

	}
};

class AI{
public:
	// �������z�֐�
	virtual Direction decideMove()=0;
	virtual bool doFire() = 0;
};