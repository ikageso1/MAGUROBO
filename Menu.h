#pragma once
#include <vector>

class Input;
class Menu{
protected:
	int Model;
	float Angle;

	//���j���[��ʂ̔w�i
	int menuGraph;
	//���W(�f�t�H���g��0)
	int x,y;
	// �}��ϐ�(�ׂ���)
	int t;
	//�Ԃ̑傫��
	int height;
	//�J�[�\��
	int cursor;
	//�����F
	int color;
	//�I�����̕����F
	int selectedColor;
	//���ʉ�
	int sound;
	int dicideSound;
	//BGM�̃t�@�C����
	char *bgm;
	//���j���[��ʂ̃��X�g
	std::vector<char*> menuList;
	//�I���t���O�l
	int retFlag;
public:
	//�f�t�H���g�R���X�g���N�^(�����F�̓f�t�H���g�Ŕ��j
	Menu();
	//�����t���R���X�g���N�^
	//�������F�����F
	Menu(int color);
	//�����t���R���X�g���N�^
	//�������F�����F�A�������F�w�i�摜
	Menu(int color,char* source);
	//�I�����̐F��ݒ�(�f�t�H���g�͐�)
	void setSelectedColor(int color);
	//���j���[���X�g�ɕ������ǉ�
	void addMenuList(char* str);
	//���W�̐ݒ�
	void setPoint(int x,int y);
	//������Ԃ̑傫���̐ݒ�(�f�t�H���g��20)
	void setHeight(int h);
	//�J�[�\���ړ����̌��ʉ��̓o�^
	void setSound(char *file);
	//���j���[��ʂ�BGM�̓o�^
	void setBGM(char *file);
	//�\��
	virtual void show();
	//���j���[��ʏ������֐������[�v�t���ŃX�^�[�g
	//Enter�������ꂽ�ꍇ��ture��Ԃ��B������Ă��Ȃ��ꍇ��false
	//ESC�L�[�Ȃǂ������ꂽ�ꍇ��-1��Ԃ�
	bool start(Input *input);
	//�I�����ꂽ�I�����̏��Ԃ̒l��Ԃ��i1����n�܂�ԍ�)
	int getSelectChoice();
	// �x�W�F�Ȑ�
	void Bezier(double x1,double y1,double x2,double y2,double x3,double y3,int t,int *ansX,int *ansY);

	void Rotate();
	void ChengeSelectStageMenu();
};