#pragma once
#include "Input.h"

class JoypadInput:public Input{
private:
	int oldButtonInput;			/**< 前回のボタンの入力状態 */
	int nowButtonInput;			/**< ボタンの入力状態 */
	int edgeButtonInput;		/**< 今回入力されて、前回入力されていないボタン */
	DINPUT_JOYSTATE input ;		/**< スティックの入力状態 */
	DINPUT_JOYSTATE oldInput ;	/**< 前のスティックの入力状態 */
	int doubleRightTimer;		/**< クイックﾀｰﾝ用タイマ（右) */
	bool doubleRightBack;		/**< 一回戻したかどうか(右 */
	int doubleLeftTimer;		/**< クイックﾀｰﾝ用タイマ（左 */
	bool doubleLeftBack;		/**< 一回戻したかどうか(左) */
	
public:
	JoypadInput();				// コンストラクタ
	void update();				// 更新
	bool isEdgeStartButton();
	int isLeft();
	int isRight();
	int isUp();
	int isDown();
	int isEdgeUp();
	int isEdgeDown();
	int isLeft2();
	int isRight2();
	int isUp2();
	int isDown2();
	bool isPushed2();
	bool isDoubleRight();
	bool isDoubleLeft();
	bool isFire();
	bool isJump();
	bool isEject();
	bool isEdgeFire();
	bool isLockOn();
	bool isEdgeLockON();
	~JoypadInput();				// デストラクタ
};