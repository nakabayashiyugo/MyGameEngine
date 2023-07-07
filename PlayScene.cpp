#include "PlayScene.h"
#include "Player.h"


PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	Player* pPlayer;
	pPlayer = new Player(this);//�v���C���[�̐e�́A����(PlayScene)

	pPlayer->Initialize();
	childList_.push_back(pPlayer);//PlayScene�̎q�Ƃ��āA�v���C���[��o�^
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{

}
