#pragma once
class Input;

class Pause{
private:
	bool isFinishFlag;		// �I���t���O
public:
	/**
	 *  �R���X�g���N�^
	 */
	Pause();			
	void Process(Input *input);		// ����
	bool isFinish();	// �I�����m�F����
};