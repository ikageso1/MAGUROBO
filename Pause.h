#pragma once
class Input;

class Pause{
private:
	bool isFinishFlag;		// 終了フラグ
public:
	/**
	 *  コンストラクタ
	 */
	Pause();			
	void Process(Input *input);		// 処理
	bool isFinish();	// 終了か確認する
};