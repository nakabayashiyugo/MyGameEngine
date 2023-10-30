#include "MapEditScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "resource.h"

MapEditScene::MapEditScene(GameObject* parent)
	: GameObject(parent, "MapEditScene"), mathtype_(0)
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
	hPict_[0] = Image::Load("Assets\\Math_Floor.png");
	hPict_[1] = Image::Load("Assets\\Math_Wall.png");
	assert(hPict_[0] >= 0);
}

void MapEditScene::Update()
{
	//debug出力例
	/*std::string resStr = std::to_string(mousePosX) + '\n';
	OutputDebugString(resStr.c_str());*/


	float mousePosX = Input::GetMousePosition().x;
	float mousePosY = Input::GetMousePosition().y;
	static XMFLOAT3 selectMath;
	mousePosX -= ((math_[0][0].mathPos_.position_.x + 1.0f) * Direct3D::scrWidth / 2) - MATHSIZE / 2;
	mousePosY -= ((-(math_[XSIZE - 1][YSIZE - 1].mathPos_.position_.y) + 1.0f) * Direct3D::scrHeight / 2) - MATHSIZE / 2;
	
	if (mousePosX >= 0 && mousePosY >= 0 &&
		mousePosX <= MATHSIZE * XSIZE &&
		mousePosY <= MATHSIZE * YSIZE)
	{
		selectMath.x = mousePosX / MATHSIZE;
		selectMath.y = mousePosY / MATHSIZE;
	}
	else
	{
		selectMath = XMFLOAT3(-1, -1, 0);
	}
	std::string resStr = "座標 : " + std::to_string((int)selectMath.x) + ", " + std::to_string((int)selectMath.y) + '\n';
	OutputDebugString(resStr.c_str());


	if (Input::IsMouseButton(0) && selectMath.x != -1 && selectMath.y != -1)
	{
		math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ = (MATHTYPE)mathtype_;
	}
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

BOOL MapEditScene::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		//ラジオボタンの初期値
		SendMessage(GetDlgItem(hDlg, IDC_MAPEDIT_FLOOR), BM_SETCHECK, BST_CHECKED, 0);

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case IDC_MAPEDIT_FLOOR:		mathtype_ = 0; break;
		case IDC_MAPEDIT_WALL:		mathtype_ = 1; break;
		case IDC_MAPEDIT_HOLL:		mathtype_ = 2; break;
		case IDC_MAPEDIT_CONVEYOR:	mathtype_ = 3; break;
		case IDC_MAPEDIT_TOGETOGE:	mathtype_ = 4; break;
		case IDC_MAPEDIT_PITFALL:	mathtype_ = 5; break;
		default: break;
		}

		return TRUE;
	}
	return FALSE;
}
