#include "Option.h"
#include "DxLib.h"
#include "Input.h"

Option::Option(){
	color=GetColor(255,255,255);
	selectedColor=GetColor(255,0,0);
	menuList.clear();
	addMenuList("Žc‹@");
	addMenuList("‚à‚Ç‚é");
	setPoint(240,200);
	SetFontSize(20);
	menuGraph = LoadGraph("Jellyfish.jpg");
	sound = LoadSoundMem("Windows Error.wav");
	zanki = 1;
}

void Option::show(){
	for(unsigned int i=0;i<menuList.size();i++){
		if(i==cursor){
			if(i==0){
				DrawFormatString(x,y+i*height-cursor*height,selectedColor,menuList[i]);
				DrawFormatString(x+150,y+i*height-cursor*height,selectedColor,"%d",zanki);
			}
			else{
				DrawFormatString(x,y+i*height-cursor*height,color,menuList[i]);
			}
		}
		else {
			if(i==0){
				DrawFormatString(x,y+i*height-cursor*height,color,menuList[i]);
				DrawFormatString(x+150,y+i*height-cursor*height,color,"%d",zanki);
			}
			else{
				DrawFormatString(x,y+i*height-cursor*height,color,menuList[i]);
			}
		}
	}
}

void Option::setZanki(Input *input){
	if(input->isLeft()){
		zanki -= 1;
	}
	else if(input->isRight()){
		zanki += 1;
	}
}