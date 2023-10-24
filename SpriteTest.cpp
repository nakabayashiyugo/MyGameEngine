#include "SpriteTest.h"
#include "Engine/Sprite.h"
#include "Engine/SceneManager.h"

SpriteTest::SpriteTest(GameObject* parent)
	: GameObject(parent, "SpriteTest")
{
	pSprite = new Sprite();
}

void SpriteTest::Initialize()
{
	pSprite->Initialize();
}

void SpriteTest::Update()
{
}

void SpriteTest::Draw()
{
	pSprite->Draw(this->transform_);
}

void SpriteTest::Release()
{
}
