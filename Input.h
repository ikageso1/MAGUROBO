#pragma once

class Input{
private:
	// いらない気がする
	int NowInput;	/**< 今回の入力状態　*/
	int OldInput;   /**< 前回の入力状態　*/
	int EdgeInput;  /**< 今回入力され、前回は入力されていない状態 */

public:
	/**
	*　コンストラクタ 入力状態の初期化
	*/
	Input();
	/**
	 * 入力状態を更新する関数 
	 */
	virtual void update()=0;
	/**
	 * スタートボタンが押されたか判定する関数 
	 */
	virtual bool isEdgeStartButton()=0;	
	/**
	 * 左にキャラクターを動かす入力がされたかどうか
	 */
	virtual int isLeft() = 0;
	/**
	 * 右にキャラクターを動かす入力がされたかどうか
	 */
	virtual int isRight() = 0;
	/**
	 * 上にキャラクターを動かす入力がされたかどうか
	 */
	virtual int isUp() = 0;
	/**
	 * 下にキャラクターを動かす入力がされたかどうか
	 */
	virtual int isDown() = 0;
	/**
	 * 上にキャラクターを動かす入力がされたかどうか(えっじ
	 */
	virtual int isEdgeUp() = 0;
	/**
	 * 下にキャラクターを動かす入力がされたかどうか(えっじ
	 */
	virtual int isEdgeDown() = 0;

	/**
	 * 左にカメラを動かす入力がされたかどうか
	 */
	virtual int isLeft2() = 0;
	/**
	 * 右にカメラを動かす入力がされたかどうか
	 */
	virtual int isRight2() = 0;
	/**
	 * 上にカメラを動かす入力がされたかどうか
	 */
	virtual int isUp2() = 0;

	virtual bool isPushed2() = 0;
	/**
	 * 下にカメラを動かす入力がされたかどうか
	 */
	virtual int isDown2() = 0;
	/**
	 * 右にローリングする入力がされたかどうか
	 */
	virtual bool isDoubleRight() = 0;
	/**
	 * 左にローリングする入力がされたかどうか
	 */
	virtual bool isDoubleLeft() = 0;
	/**
	 * 弾を発射する入力がされたかどうか
	 */
	virtual bool isFire() = 0;
	virtual bool isEdgeFire() = 0;
	/**
	 * ジャンプをする入力がされたかどうか
	 */
	virtual bool isJump() = 0;
	virtual bool isEject() = 0;
	virtual bool isLockOn() = 0;
	virtual bool isEdgeLockON() = 0;
	/**
	 * デストラクタ　特に何もしていない
	 */
	~Input();				
};