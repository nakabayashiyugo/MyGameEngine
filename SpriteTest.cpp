#include "SpriteTest.h"
#include "Engine/Sprite.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

SpriteTest::SpriteTest(GameObject* parent)
	: GameObject(parent, "SpriteTest")
{
	for (int i = 0; i < MATHTYPE::MATH_MAX; i++)
	{
		hPict_[i] = -1;
	}

	for (int x = 0; x < XSIZE; x++)
	{
		for (int y = 0; y < YSIZE; y++)
		{
			math_[x][y].mathPos_.scale_ = XMFLOAT3(1.0f / Direct3D::scrWidth * MATHSIZE, 1.0f / Direct3D::scrHeight * MATHSIZE, 1);
			math_[x][y].mathPos_.position_.x = ((float)x / Direct3D::scrWidth) * MATHSIZE + ((float)(x - XSIZE) / Direct3D::scrWidth) * MATHSIZE;
			math_[x][y].mathPos_.position_.y = ((float)y / Direct3D::scrHeight) * MATHSIZE + ((float)(y - YSIZE) / Direct3D::scrHeight) * MATHSIZE;

			math_[x][y].mathType_ = MATH_FLOOR;
		}
	}
}

void SpriteTest::Initialize()
{
	hPict_[0] = Image::Load("Asetts\\math.png");
	assert(hPict_[0] >= 0);
}

void SpriteTest::Update()
{
	float mousePos = Input::GetMousePosition().x;
	if (mousePos >= (math_[0][0].mathPos_.position_.x + 1.0f) * Direct3D::scrWidth / 2)
	{
		int a = 0;
	}
}

void SpriteTest::Draw()
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int y = 0; y < YSIZE; y++)
		{
			Image::SetTransform(math_[x][y].mathType_, math_[x][y].mathPos_);
			Image::Draw(math_[x][y].mathType_);
		}
	}
	
}

void SpriteTest::Release()
{
}
