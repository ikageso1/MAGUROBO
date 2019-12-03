#include "DxLib.h"
#include "Menu.h"
#include "Input.h"



//C++11のdelegating constructor機能を使えば
//コンストラクタ内で自クラスの別のコンストラクタを呼べるが、
//現在、私が使用している開発環境はC++11の機能を使えないので断念
//また、このコンストラクタでは初期化子リストを使用している。
Menu::Menu()
	:x(),y(),menuGraph(-1),cursor(),height(20),
	sound(),bgm(),t(100)
{
	color=GetColor(255,255,255);
	selectedColor=GetColor(255,0,0);
	addMenuList("はじめから");
	addMenuList("ステージ選択");
	addMenuList("オプション");
	addMenuList("終了");
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
	addMenuList("ステージ1");
	addMenuList("ステージ2");
	addMenuList("ステージ3");
	addMenuList("ステージ4");
}

// ベジェ
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
	// モデルの角度を更新
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

	//Enterが押された場合、ループを抜ける
	if(input->isEdgeFire()){
		PlaySoundMem(dicideSound,DX_PLAYTYPE_BACK);
		if(bgm!=NULL)
			StopMusic();
		//フラグ値に選択された選択肢の順番を格納（1から始まる値)
		retFlag = cursor+1;
		return true;
	}

	//↑キー
	if(input->isEdgeUp()){
		if(sound!=NULL)
			PlaySoundMem(sound,DX_PLAYTYPE_BACK);
		if(cursor!=0){
			cursor--;
			t += 20;
		}
	}
	//↓キー
	if(input->isEdgeDown()){
		if(sound!=NULL)
			PlaySoundMem(sound,DX_PLAYTYPE_BACK);
		if(cursor!=menuList.size()-1){
			cursor++;
			t -= 20;
		}
	}
	//描画
	show();
	return false;
}

int Menu::getSelectChoice(){
	return retFlag;
}