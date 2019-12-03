#include "World4.h"
#include "Stage4.h"
#include "Stage.h"
#include "Camera.h"
#include "Player.h"
#include "Character.h"
#include "M95.h"
#include "JetItem.h"


World4::World4(Input* input){
	stage = new Stage4();			// �X�e�[�W����
	player = stage->CreatePlayer();	// �v���C���[
	camera = new Camera(player);	// �J����

	stage->CreateEnemies(enemies,(Player*)player);
	stage->CreateItems(items);

	// �R���g���[���ݒ�
	((Player*)player)->SetInputAI(input);
	// BGM�ݒ�
	BGMHandle = "sound/nc95844.mp3";


}