#include "Game.h"
#include "Pause.h"
#include "Player.h"
#include "JoypadInput.h"
#include "KeyBoardInput.h"
#include "Menu.h"
#include "Option.h"
#include "FirstWorld.h"
#include "SecondWorld.h"
#include "ThirdWorld.h"
#include "World4.h"


// �R���X�g���N�^
Game::Game(){
	world = 0;
	menu = 0;
	option = new Option();
	if(GetJoypadNum() ){
		input = new JoypadInput();	// �R���g���[���[
	}
	else{
		input = new KeyBoardInput();
	}

	title = new Title();			// �^�C�g�����
	pause = new Pause();			// �|�[�Y���

	mainflag = FLAG::TITLE;	// �ŏ��̉�ʂ̓^�C�g��
	zanki = 2;
}

// �c�d�`�s�g�Ƃ炭��
Game::~Game(){
	delete input;
	delete title;
	delete menu;
	delete option;
}

// �܂����[��
void Game::MainLoop(){
	while( ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE)==0){		// ���C�����[�v
		ClearDrawScreen();				// ��ʂ�����
		input->update();				// ���͏�ԍX�V
		// �^�C�g�����
		if(mainflag == FLAG::TITLE){
			title->process(input);			// �^�C�g����ʏ���
			if(title->isFinish()){
				mainflag = FLAG::MENU;		// �X�e�[�W�Ɉڍs
				if(menu)
					delete menu;
				menu = new Menu();				//���j���[
			}
		}
		else if(mainflag==FLAG::MENU){
			if(menu->start(input)){
				switch(menu->getSelectChoice()){
				case 1:
					mainflag=FLAG::STAGE;
					stageNum = 1;
					world = new FirstWorld(input);
					world->StartBGM();
					break;
				case 2:
					mainflag=FLAG::STAGESELECT;
					menu->ChengeSelectStageMenu();
					break;
				case 3:
					mainflag=FLAG::OPTION;
					break;
				case 4:
					throw "END";
					break;
				}
			}
		}
		else if(mainflag==FLAG::STAGESELECT){
			if(menu->start(input)){
				switch(menu->getSelectChoice()){
				case 1:
					mainflag=FLAG::STAGE;
					stageNum = 1;
					world = new FirstWorld(input);
					world->StartBGM();
					break;
				case 2:
					mainflag=FLAG::STAGE;
					stageNum = 2;
					world = new SecondWorld(input);
					world->StartBGM();
					break;
				case 3:
					mainflag=FLAG::STAGE;
					stageNum = 3;
					world = new ThirdWorld(input);
					world->StartBGM();
					break;
				case 4:
					mainflag=FLAG::STAGE;
					stageNum = 4;
					world = new World4(input);
					world->StartBGM();
					break;
				}
			}
		}
		// �I�v�V����
		else if(mainflag==FLAG::OPTION){
			if(option->start(input)){
				switch(option->getSelectChoice()){
				case 1:
					option->setZanki(input);
					break;
				case 2:
					mainflag=FLAG::MENU;
					break;
				}
			}
			switch(option->getSelectChoice()){
			case 1:
				option->setZanki(input);
				break;
			}
		}
		// �X�e�[�W���
		else if(mainflag == FLAG::STAGE){
			switch( world->Process(input) ){
				// �N���A�[ 
			case 1:
				stageNum += 1;
				delete world;
				switch(stageNum){
				case 1:
					world = new FirstWorld(input);
					break;
				case 2:
					world = new SecondWorld(input);
					break;
				case 3:
					world = new ThirdWorld(input);
					break;
				case 4:
					world = new World4(input);
					break;
				case 5:
					mainflag = FLAG::CLEAR;
					break;
				}
				break;
				// ���S
			case 2:
				zanki -= 1;
				delete world;

				if(zanki < 0){
					mainflag = FLAG::GAMEOVER;
				}else{
					switch(stageNum){
					case 1:
						world = new FirstWorld(input);
						break;
					case 2:
						world = new SecondWorld(input);
						break;
					case 3:
						world = new ThirdWorld(input);
						break;
					case 4:
						world = new World4(input);
						break;
					}
				}
				break;
			}
			// �|�[�Y��ʂւ̑J�ڏ���
			if(input->isEdgeStartButton()){
				mainflag = FLAG::PAUSE;
			}

		}
		else if(mainflag==FLAG::GAMEOVER){
			DrawFormatString(300,300,GetColor(255,255,255),"���[�ނ��[�΁[");
			ScreenFlip();
			WaitTimer(1000);
			zanki = 3;
			mainflag = FLAG::TITLE;
			if(title)
				delete title;
			title = new Title();
		}
		else if(mainflag==FLAG::CLEAR){
			DrawFormatString(300,300,GetColor(255,255,255),"���肠�[!!!");
			ScreenFlip();
			WaitTimer(1000);
			zanki = 3;
			mainflag = FLAG::TITLE;
			if(title)
				delete title;
			title = new Title();
		}
		// �|�[�Y���
		else if(mainflag == FLAG::PAUSE){
			world->Draw();
			// �|�[�Y����
			pause->Process(input);
			// �Q�[����ʂւ̑J�ڏ���
			if(pause->isFinish()){
				mainflag = FLAG::STAGE;
			}
		}
		ScreenFlip();				// ����ʂ�K�p
	}
}