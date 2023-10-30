#include <stdio.h>
#include "MapEditScene.h"
#include "Engine/Sprite.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

MapEditScene::MapEditScene(GameObject* parent)
	: GameObject(parent, "MapEditScene")
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

void MapEditScene::Initialize()
{
	hPict_[0] = Image::Load("Asetts\\math.png");
	assert(hPict_[0] >= 0);
}

void MapEditScene::Update()
{
	//debugèoóÕó·
	/*std::string resStr = std::to_string(mousePosX) + '\n';
	OutputDebugString(resStr.c_str());*/


	float mousePosX = Input::GetMousePosition().x;
	float mousePosY = Input::GetMousePosition().y;
	static XMFLOAT3 selectMath;
	mousePosX -= ((math_[0][0].mathPos_.position_.x + 1.0f) * Direct3D::scrWidth / 2) - MATHSIZE / 2;
	mousePosY -= ((-(math_[XSIZE - 1][YSIZE - 1].mathPos_.position_.y) + 1.0f) * Direct3D::scrHeight / 2) - MATHSIZE / 2;
	
	if (mousePosX >= 0 && mousePosY >= 0)
	{
		selectMath.x = mousePosX / MATHSIZE;
		selectMath.y = mousePosY / MATHSIZE;
	}
	std::string resStr = "ç¿ïW : " + std::to_string((int)selectMath.x) + ", " + std::to_string((int)selectMath.y) + '\n';
	OutputDebugString(resStr.c_str());
}

void MapEditScene::Draw()
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

void MapEditScene::Release()
{
}
