#include "DxLib.h"
#include "Menu.h"
#include "Input.h"



//C++11��delegating constructor�@�\���g����
//�R���X�g���N�^���Ŏ��N���X�̕ʂ̃R���X�g���N�^���Ăׂ邪�A
//���݁A�����g�p���Ă���J������C++11�̋@�\���g���Ȃ��̂Œf�O
//�܂��A���̃R���X�g���N�^�ł͏������q���X�g���g�p���Ă���B
Menu::Menu()
	:x(),y(),menuGraph(-1),cursor(),height(20),
	sound(),bgm(),t(100)
{
	color=GetColor(255,255,255);
	selectedColor=GetColor(255,0,0);
	addMenuList("�͂��߂���");
	addMenuList("�X�e�[�W�I��");
	addMenuList("�I�v�V����");
	addMenuList("�I��");
	setPoint(240,200);
	SetFontSize(22);
	menuGraph = LoadGraph("Jellyfish.jpg");
	sound = LoadSoundMem("sound/Windows Error.wav");
	dicideSound = LoadSoundMem("sound/chime01.wav");

	Model = MV1LoadModel("chara/1.pmd");
	SetCameraPositionAndTarget_UpVecY(VGet(15.0f,2.0f,-40.0f),VGet(15.0f,0.0f,0.0f));
	MV1SetPosition(Model,VGet(0.0f,0.0f,0.0f));
	Angle = 0;

}
Menu::Menu(int aColor)
	:x(),y(),menuGraph(-1),color(aColor),cursor(),height(20),
	sound(),bgm(),t(100)
{
	selectedColor=GetColor(255,0,0);
}
Menu::Menu(int aColor,char* source)
	:x(),y(),menuGraph(-1),color(aColor),cursor(),height(20),
	sound(),bgm(),t(100)
{
	selectedColor=GetColor(255,0,0);
	menuGraph = LoadGraph(source);
}

void Menu::ChengeSelectStageMenu(){
	menuList.clear();
	cursor = 1;
	addMenuList("�X�e�[�W1");
	addMenuList("�X�e�[�W2");
	addMenuList("�X�e�[�W3");
	addMenuList("�X�e�[�W4");
}

// �x�W�F
void Menu::Bezier(double x1,double y1,double x2,double y2,double x3,double y3,int t,int *ansX,int *ansY){
	const int T = 300;
	float b = (float)t/T;
	float a = 1-b;
	*ansX = a*a*x1 + 2*a*b*x2 + 3*b*b*x3;
	*ansY = a*a*y1 + 2*a*b*y2 + 3*b*b*y3;
}

void Menu::Rotate(){
	Angle +=  0.05f;
	if( Angle > DX_TWO_PI_F )
	{
		Angle = 0.0f ;
	}
	// ���f���̊p�x���X�V
	MV1SetRotationXYZ( Model, VGet( 0.0f, Angle, 0.0f ) ) ;
}

void Menu::setSelectedColor(int color){
	selectedColor=color;
}

void Menu::addMenuList(char* str){
	menuList.push_back(str);
}

void Menu::setPoint(int x,int y){
	this->x = x;
	this->y = y;
}
void Menu::setHeight(int h){
	this->height = h;
}

void Menu::setSound(char *file){
	sound = LoadSoundMem(file);
}

void Menu::setBGM(char *file){
	bgm = file;
}


void Menu::show(){
	Rotate();
	MV1DrawModel(Model);
	if(menuGraph!=-1)
		DrawGraph(0,0,menuGraph,FALSE);
	/*for(unsigned int i=0;i<menuList.size();i++){
		if(i==cursor)DrawFormatString(x,y+i*20,selectedColor,menuList[i]);
		else DrawFormatString(x,y+i*height,color,menuList[i]);
	}*/
	for(unsigned int i=0;i<menuList.size();i++){
		int tempX,tempY;
		Bezier(300,0,600,200,100,200,t+i*20,&tempX,&tempY);
		//if(i==cursor)DrawFormatString(x,y+i*20-cursor*height,selectedColor,menuList[i]);
		//else DrawFormatString(x,y+i*height-cursor*height,color,menuList[i]);
		if(i==cursor)DrawFormatString(tempX,tempY,selectedColor,menuList[i]);
		else DrawFormatString(tempX,tempY,color,menuList[i]);
	}
	
}

bool Menu::start(Input *input){
	if(bgm!=NULL&&CheckMusic()==0)
		PlayMusic(bgm,DX_PLAYTYPE_LOOP);

	//Enter�������ꂽ�ꍇ�A���[�v�𔲂���
	if(input->isEdgeFire()){
		PlaySoundMem(dicideSound,DX_PLAYTYPE_BACK);
		if(bgm!=NULL)
			StopMusic();
		//�t���O�l�ɑI�����ꂽ�I�����̏��Ԃ��i�[�i1����n�܂�l)
		retFlag = cursor+1;
		return true;
	}

	//���L�[
	if(input->isEdgeUp()){
		if(sound!=NULL)
			PlaySoundMem(sound,DX_PLAYTYPE_BACK);
		if(cursor!=0){
			cursor--;
			t += 20;
		}
	}
	//���L�[
	if(input->isEdgeDown()){
		if(sound!=NULL)
			PlaySoundMem(sound,DX_PLAYTYPE_BACK);
		if(cursor!=menuList.size()-1){
			cursor++;
			t -= 20;
		}
	}
	//�`��
	show();
	return false;
}

int Menu::getSelectChoice(){
	return retFlag;
}