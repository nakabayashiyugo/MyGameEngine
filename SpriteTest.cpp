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
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			Transform sprPos;
			sprPos.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
			sprPos.position_.x = ((float)x / 800) * 60;
			sprPos.position_.y = ((float)y / 600) * 60;
			
			pSprite->Draw(sprPos);
		}
	}
	
}

void SpriteTest::Release()
{
}
