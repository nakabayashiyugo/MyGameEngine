#include "PlayScene.h"
#include "Engine/Image.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), hPict_(-1)
{
}

void PlayScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Assets\\dice.png");
	assert(hPict_ >= 0);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void PlayScene::Release()
{

}
