#include "World.h"
#include "FirstStage.h"
#include "Stage.h"
#include "Camera.h"
#include "Player.h"
#include "Character.h"
#include "Enemy.h"
#include "Item.h"

World::World(){
	player = 0;
	camera = 0;
	stage = 0;
	timer = 0;
	items = new std::vector<Item*>(0);
	enemies = new std::vector<Enemy*>(0);
	isGameOver = false;
	isGameClear = false;
}

World::~World(){
	if(stage)
		delete stage;
	if(camera)
		delete camera;
	if(player)
		delete player;
	if(enemies)
		delete enemies;
	if(items)
		delete items;
}

int World::Process(Input* input){
	player->Think();
	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->Think();
	camera->Rotate(input);
	camera->Move();
	camera->CheckStageColl(stage);
	if(input->isLockOn()){
		camera->LockOn((Player*)player,enemies,!input->isEdgeLockON());
	}
	camera->Update();

	
	((Player*)player)->SetMoveVec(camera->GetTarget(),camera->GetPos());

	player->Move();		// �v���C���[�ړ�
	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->Move();
	if(input->isEject())
		((Player*)player)->Eject();
	((Player*)player)->SetDirection(camera->GetAngleV());
	player->Rotate();
	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->Rotate();
	for(int i=0;i<items->size();i++)
		items->at(i)->Rotate();
	player->Fall();
	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->Fall();
	player->Role();
	player->CheckStageColl(stage);
	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->CheckStageColl(stage);
	for(int i=0;i<enemies->size();i++){
		if(player->CollCheck((*enemies)[i])){
			player->Damage(enemies->at(i)->GetDamage());
		}
	}

	player->UpdatePosition();
	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->UpdatePosition();

	player->Attack();
	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->Attack();

	player->TamaMove(stage);			// �e�̈ړ�
	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->TamaMove(stage);

	{
		Enemy* isDamageEnemy = 0;
		for(int i=0;i<enemies->size();i++){
			if(player->TamaCollCheck((*enemies)[i])){
				isDamageEnemy = (*enemies)[i];
			}
		}
		if(isDamageEnemy){
			for(int i=0;i<enemies->size();i++){
				enemies->at(i)->ResetisDraw();
			}
			isDamageEnemy->SetisDraw();
		}		
	}

	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->TamaCollCheck(player);

	player->TamaDeath();
	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->TamaDeath();
	CheckItem();

	// ���S����
	CheckDeath();


	// �Q�[���N���A����
	if(isGameClear){
		GameClear();
		if(timer == 120){
			StopBGM();
			return 1;
		}
		timer++;
	}
	// �Q�[���I�[�o�[����
	else if(isGameOver){
		GameOver();
		if(timer == 120){
			StopBGM();
			return 2;
		}
		timer++;
	}

	Draw();

	return 0;
}

void World::Draw(){
	stage->Draw();		// �X�e�[�W�`��
	player->Draw();		// �v���C���[�`��
	// �G
	for(int i=0;i<enemies->size();i++)
		enemies->at(i)->Draw();
	// ����(�A�C�e��
	for(int i=0;i<items->size();i++)
		items->at(i)->Draw();
	DrawFormatString(10,50,GetColor(255,255,255),"�c��̓G�̐�:%d",enemies->size());
}

void World::CheckDeath(){
	// �����̎��S����
	if(!player->GetisAlive()){
		isGameOver = true;
	}
	// �G�̎��S����
	std::vector<Enemy*>::iterator ite;
	for(ite=enemies->begin();ite!=enemies->end();){
		if(!(*ite)->GetisAlive()){
			ite = enemies->erase(ite);
		}else{
			ite++;
		}
	}
	if(enemies->size()==0){
		isGameClear = true;
	}

}

void World::GameClear(){

}


void World::GameOver(){
	
}
void World::CheckItem(){
	// ����(�A�C�e��
	for(int i=0;i<items->size();i++){
		if(items->at(i)->CollCheck(player)){
			items->at(i)->Effect((Player*)player);
		}
	}

}


void World::StartBGM(){
	PlayMusic(BGMHandle,DX_PLAYTYPE_LOOP) ;
}

void World::StopBGM(){
	StopMusic();
}