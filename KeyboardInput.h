#pragma once
#include "Input.h"

class KeyBoardInput:public Input{
	private:
	char NowInput[256];			/**< 現在押されたボタン */
	char OldInput[256];			/**< 前回押されたボタン */
	char EdgeInput[256];		/**< 前回押されていなくて、今回押されたボタン */

public:
	/**
	* コンストラクタ　キーボードの入力状態の初期化
	*/
	KeyBoardInput();				// コンストラクタ
	void update();				// 更新
	bool isEdgeStartButton();
	int isLeft();
	int isRight();
	int isUp();
	int isEdgeUp();
	int isDown();
	int isEdgeDown();
	int isLeft2(); //カメラ移動
	int isRight2();//カメラ移動
	int isUp2();//カメラ移動
	int isDown2();//カメラ移動
	bool isDoubleRight();
	bool isDoubleLeft();
	bool isFire();
	bool isJump();
	bool isEject();
	bool isPushed2();
	bool isEdgeFire();
	bool isLockOn();
	bool isEdgeLockON();
	/**
	* デストラクタ　何にもしてねー
	*/
	~KeyBoardInput();	
};