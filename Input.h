#pragma once

class Input{
private:
	// ����Ȃ��C������
	int NowInput;	/**< ����̓��͏�ԁ@*/
	int OldInput;   /**< �O��̓��͏�ԁ@*/
	int EdgeInput;  /**< ������͂���A�O��͓��͂���Ă��Ȃ���� */

public:
	/**
	*�@�R���X�g���N�^ ���͏�Ԃ̏�����
	*/
	Input();
	/**
	 * ���͏�Ԃ��X�V����֐� 
	 */
	virtual void update()=0;
	/**
	 * �X�^�[�g�{�^���������ꂽ�����肷��֐� 
	 */
	virtual bool isEdgeStartButton()=0;	
	/**
	 * ���ɃL�����N�^�[�𓮂������͂����ꂽ���ǂ���
	 */
	virtual int isLeft() = 0;
	/**
	 * �E�ɃL�����N�^�[�𓮂������͂����ꂽ���ǂ���
	 */
	virtual int isRight() = 0;
	/**
	 * ��ɃL�����N�^�[�𓮂������͂����ꂽ���ǂ���
	 */
	virtual int isUp() = 0;
	/**
	 * ���ɃL�����N�^�[�𓮂������͂����ꂽ���ǂ���
	 */
	virtual int isDown() = 0;
	/**
	 * ��ɃL�����N�^�[�𓮂������͂����ꂽ���ǂ���(������
	 */
	virtual int isEdgeUp() = 0;
	/**
	 * ���ɃL�����N�^�[�𓮂������͂����ꂽ���ǂ���(������
	 */
	virtual int isEdgeDown() = 0;

	/**
	 * ���ɃJ�����𓮂������͂����ꂽ���ǂ���
	 */
	virtual int isLeft2() = 0;
	/**
	 * �E�ɃJ�����𓮂������͂����ꂽ���ǂ���
	 */
	virtual int isRight2() = 0;
	/**
	 * ��ɃJ�����𓮂������͂����ꂽ���ǂ���
	 */
	virtual int isUp2() = 0;

	virtual bool isPushed2() = 0;
	/**
	 * ���ɃJ�����𓮂������͂����ꂽ���ǂ���
	 */
	virtual int isDown2() = 0;
	/**
	 * �E�Ƀ��[�����O������͂����ꂽ���ǂ���
	 */
	virtual bool isDoubleRight() = 0;
	/**
	 * ���Ƀ��[�����O������͂����ꂽ���ǂ���
	 */
	virtual bool isDoubleLeft() = 0;
	/**
	 * �e�𔭎˂�����͂����ꂽ���ǂ���
	 */
	virtual bool isFire() = 0;
	virtual bool isEdgeFire() = 0;
	/**
	 * �W�����v��������͂����ꂽ���ǂ���
	 */
	virtual bool isJump() = 0;
	virtual bool isEject() = 0;
	virtual bool isLockOn() = 0;
	virtual bool isEdgeLockON() = 0;
	/**
	 * �f�X�g���N�^�@���ɉ������Ă��Ȃ�
	 */
	~Input();				
};