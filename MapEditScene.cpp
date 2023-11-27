#include "MapEditScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "resource.h"
#include "SceneTransition.h"

MapEditScene::MapEditScene(GameObject* parent)
	: GameObject(parent, "MapEditScene"), mathtype_(0), YSIZE(ZSIZE)
{
	for (int i = 0; i < MATHTYPE::MATH_MAX; i++)
	{
		hPict_[i] = -1;
	}
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize_x();
	YSIZE = (int)pTrans_->GetMathSize_z();

	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);

	Math_Resize(XSIZE, YSIZE, &math_);
	Math_Resize(XSIZE, YSIZE, &math_origin_);

	Texture* pTexture = (Texture*)FindObject("Texture");

	Read();
	for (int x = 0; x < XSIZE; x++)
	{
		for (int y = 0; y < YSIZE; y++)
		{
			math_origin_[x][y] = math_[x][y];
			math_[x][y].mathPos_.scale_ = XMFLOAT3(1.0f / pTexture->GetSize().x * MATHSIZE, 1.0f / pTexture->GetSize().y * MATHSIZE, 1);
			math_[x][y].mathPos_.position_.x = ((float)x / Direct3D::scrWidth) * MATHSIZE + ((float)(x - XSIZE) / Direct3D::scrWidth) * MATHSIZE;
			math_[x][y].mathPos_.position_.y = ((float)y / Direct3D::scrHeight) * MATHSIZE + ((float)(y - YSIZE) / Direct3D::scrHeight) * MATHSIZE;
		}
	}
}

void MapEditScene::Initialize()
{
	std::string filename[MATH_MAX + 1] =
	{
		"Math_Floor.png",
		"Math_Wall.png",
		"Math_Holl.png",
		"Math_Conveyor.png",
		"Math_Togetoge.png",
		"Math_PitFall.png",
		"Math_Start.png",
		"Math_Goal.png",
		"Math_Rotate.png"
	};
	for (int i = 0; i < MATH_MAX + 1; i++)
	{
		filename[i] = "Assets\\" + filename[i];
		hPict_[i] = Image::Load(filename[i]);
		assert(hPict_[i] >= 0);
	}
	
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

	selectMath.x = mousePosX / MATHSIZE;
	selectMath.y = mousePosY / MATHSIZE;

	if (selectMath.x < 0 || selectMath.x >= XSIZE ||
		selectMath.y < 0 || selectMath.y >= YSIZE)
	{
		selectMath = XMFLOAT3(-1, -1, 0);
	}
	std::string resStr = "座標 : " + std::to_string((int)selectMath.x) + ", " + std::to_string((int)selectMath.y) + '\n';
	OutputDebugString(resStr.c_str());

	if (selectMath.x != -1 && selectMath.y != -1)
	{
		if (Input::IsMouseButtonDown(0))
		{
			if (math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ !=
				math_origin_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ ||
				math_origin_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ == MATH_FLOOR)
			{
				if ((MATHTYPE)mathtype_ == MATHTYPE::MATH_START)
				{
					for (int x = 0; x < XSIZE; x++)
					{
						for (int y = 0; y < YSIZE; y++)
						{
							if (math_[x][y].mathType_ == MATH_START)
							{
								math_[x][y].mathType_ = MATH_FLOOR;
							}
						}
					}
				}
				if ((MATHTYPE)mathtype_ == MATHTYPE::MATH_GOAL)
				{
					for (int x = 0; x < XSIZE; x++)
					{
						for (int y = 0; y < YSIZE; y++)
						{
							if (math_[x][y].mathType_ == MATH_GOAL)
							{
								math_[x][y].mathType_ = MATH_FLOOR;
							}
						}
					}
				}
				if ((MATHTYPE)mathtype_ == MATHTYPE::MATH_CONVEYOR &&
					math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ == MATHTYPE::MATH_CONVEYOR)
				{
					math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].converyor_rotate_++;
					math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].converyor_rotate_ %= 4;
				}
				else
				{
					math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ = (MATHTYPE)mathtype_;
				}
			}
		}

	}
}

void MapEditScene::Draw()
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int y = 0; y < YSIZE; y++)
		{
			if (math_[x][YSIZE - 1 - y].mathType_ == MATHTYPE::MATH_CONVEYOR)
			{
				float mathSin = abs(sin(XMConvertToRadians(math_[x][YSIZE - 1 - y].mathPos_.rotate_.z)));
				math_[x][YSIZE - 1 - y].mathPos_.scale_ =
					XMFLOAT3(1.0f / (Direct3D::scrWidth - (Direct3D::scrWidth - Direct3D::scrHeight) * mathSin) * MATHSIZE,
					1.0f / (Direct3D::scrHeight + (Direct3D::scrWidth - Direct3D::scrHeight) * mathSin) * MATHSIZE, 
					1);

				if (math_[x][YSIZE - 1 - y].mathPos_.rotate_.z >= math_[x][YSIZE - 1 - y].converyor_rotate_ * 90)
				{
					math_[x][YSIZE - 1 - y].mathPos_.rotate_.z = math_[x][YSIZE - 1 - y].converyor_rotate_ * 90;
				}
				else
				{
					math_[x][YSIZE - 1 - y].mathPos_.rotate_.z += 5;
				}
			}
			Image::SetTransform(hPict_[math_[x][y].mathType_], math_[x][y].mathPos_);
			Image::Draw(hPict_[math_[x][y].mathType_]);
			
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
		bool startFlg = false, goalFlg = false;
		switch (LOWORD(wp))
		{
		case IDC_MAPEDIT_FLOOR:		mathtype_ = 0; break;
		case IDC_MAPEDIT_WALL:		mathtype_ = 1; break;
		case IDC_MAPEDIT_HOLL:		mathtype_ = 2; break;
		case IDC_MAPEDIT_CONVEYOR:	mathtype_ = 3; break;
		case IDC_MAPEDIT_TOGETOGE:	mathtype_ = 4; break;
		case IDC_MAPEDIT_PITFALL:	mathtype_ = 5; break;
		case IDC_MAPEDIT_START:		mathtype_ = 6; break;
		case IDC_MAPEDIT_GOAL:		mathtype_ = 7; break;
		case IDC_MAPEDIT_COMPLETE:	
			for (int x = 0; x < XSIZE; x++)
			{
				for (int y = 0; y < YSIZE; y++)
				{
					if (math_[x][y].mathType_ == MATH_START)
					{
						startFlg = true;
					}
					if (math_[x][y].mathType_ == MATH_GOAL)
					{
						goalFlg = true;
					}
				}
			}
			if(startFlg && goalFlg)	Write(); 
			if ((int)pTrans_->GetSceneState() >= 3) EndDialog(hDlg, 0);
			break;
		default: break;
		}

		return TRUE;
	}
	return FALSE;
}

void MapEditScene::Write()
{
	std::ofstream write;
	std::string savefile = "saveMath";
	savefile += std::to_string((int)pTrans_->GetSceneState());
	write.open(savefile, std::ios::out | std::ios::binary);

	//  ファイルが開けなかったときのエラー表示
	if (!write) {
		std::cout << "ファイル " << savefile << " が開けません";
		return;
	}

	for (int i = 0; i < XSIZE; i++) {
		for (int j = 0; j < YSIZE; j++)
		{
			write.write((char*)&math_[i][j].mathType_, sizeof(math_[i][j].mathType_));
			//文字列ではないデータをかきこむ
		}
	}

	write.close();  //ファイルを閉じる

	savefile = "saveConvRot";
	savefile += std::to_string((int)pTrans_->GetSceneState());
	write.open(savefile, std::ios::out | std::ios::binary);

	//  ファイルが開けなかったときのエラー表示
	if (!write) {
		std::cout << "ファイル " << savefile << " が開けません";
		return;
	}

	for (int i = 0; i < XSIZE; i++) {
		for (int j = 0; j < YSIZE; j++)
		{
			write.write((char*)&math_[i][j].converyor_rotate_, sizeof(math_[i][j].converyor_rotate_));
			//文字列ではないデータをかきこむ
		}
	}

	write.close();  //ファイルを閉じる

	
	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);
	KillMe();
}

void MapEditScene::Read()
{
	std::ifstream read;
	std::string savefile = "saveMath";
	savefile += std::to_string((int)pTrans_->GetSceneState());
	read.open(savefile, std::ios::in | std::ios::binary);
	//  ファイルを開く
	//  ios::in は読み込み専用  ios::binary はバイナリ形式

	if (!read) {
		std::cout << "ファイルが開けません";
		return;
	}
	//  ファイルが開けなかったときの対策

	//ファイルの最後まで続ける
	for (int i = 0; i < XSIZE; i++)
	{
		for (int j = 0; j < YSIZE; j++)
		{
			read.read((char*)&math_[i][j].mathType_, sizeof(math_.at(i).at(j).mathType_));
			//文字列ではないデータを読みこむ

		}
	}
	read.close();  //ファイルを閉じる

	savefile = "saveConvRot";
	savefile += std::to_string((int)pTrans_->GetSceneState());
	read.open(savefile, std::ios::in | std::ios::binary);
	//  ファイルを開く
	//  ios::in は読み込み専用  ios::binary はバイナリ形式

	if (!read) {
		std::cout << "ファイルが開けません";
		return;
	}
	//  ファイルが開けなかったときの対策

	//ファイルの最後まで続ける
	for (int i = 0; i < XSIZE; i++)
	{
		for (int j = 0; j < YSIZE; j++)
		{
			read.read((char*)&math_[i][j].converyor_rotate_, sizeof(math_.at(i).at(j).converyor_rotate_));
			//文字列ではないデータを読みこむ

		}
	}
	read.close();  //ファイルを閉じる
}
