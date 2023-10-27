#include "SpriteTest.h"
#include "Engine/Sprite.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

SpriteTest::SpriteTest(GameObject* parent)
	: GameObject(parent, "SpriteTest"), hPict_(-1)
{
}

void SpriteTest::Initialize()
{
	hPict_ = Image::Load("Asetts\\math.png");
	assert(hPict_ >= 0);
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
			sprPos.scale_ = XMFLOAT3(1.0f/800.0f * 30.0f, 1.0f / 600.0f * 30.0f, 1);
			sprPos.position_.x = ((float)x / 800) * 60 + (((float)x - (15 / 2)) / 800) * 60;
			sprPos.position_.y = ((float)y / 600) * 60 + (((float)y - (15 / 2)) / 800) * 60;
			
			Image::SetTransform(hPict_, sprPos);
			Image::Draw(hPict_);
		}
	}
	
}

void SpriteTest::Release()
{
}
