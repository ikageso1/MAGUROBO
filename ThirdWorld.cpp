#include "ThirdWorld.h"
#include "ThirdStage.h"
#include "Stage.h"
#include "Camera.h"
#include "Player.h"
#include "Character.h"
#include "NormalEnemy.h"
#include "TraceEnemy.h"
#include "M95.h"
#include "JetItem.h"


ThirdWorld::ThirdWorld(Input* input){
	stage = new ThirdStage();			// �X�e�[�W����
	player = stage->CreatePlayer();	// �v���C���[
	camera = new Camera(player);	// �J����
	stage->CreateEnemies(enemies,(Player*)player);
	stage->CreateItems(items);

	// �R���g���[���ݒ�
	((Player*)player)->SetInputAI(input);
	// BGM�ݒ�
	BGMHandle = "sound/nc95844.mp3";


}