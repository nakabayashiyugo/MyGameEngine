#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	GameObject* pPlayer = Instantiate<Player>(this);
	GameObject* pEnemy = Instantiate<Enemy>(this);
	pEnemy->SetTransformPos(XMFLOAT3(0, 0, 10.0f));
	pEnemy->SetTransformSca(XMFLOAT3(0.5f, 0.5f, 0.5f));
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
