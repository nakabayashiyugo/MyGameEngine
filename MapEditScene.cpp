#include "MapEditScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "resource.h"
#include "SceneTransition.h"
#include "Engine/Text.h"

MapEditScene::MapEditScene(GameObject* parent)
	: GameObject(parent, "MapEditScene"), mathtype_(0), YSIZE(ZSIZE), save_Num_(2), 
	mathChangeNum_(0), hTgtgRoute_(-1)
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
	Math_Resize(XSIZE, YSIZE, &isConvRot_);

	Texture* pTexture = (Texture*)FindObject("Texture");

	if (pTrans_->GetSceneState() == SCENESTATE::SCENE_MAPEDIT1_DELAY && pTrans_->GetTurnNum() % 2 == 0)
	{
		save_Num_ += 1;
	}
	else if (pTrans_->GetSceneState() == SCENESTATE::SCENE_MAPEDIT2_DELAY && pTrans_->GetTurnNum() % 2 == 0)
	{
		save_Num_ -= 1;
	}
	else if (pTrans_->GetSceneState() == SCENESTATE::SCENE_MAPEDIT1_DELAY && pTrans_->GetTurnNum() % 2 == 1)
	{
		save_Num_ -= 1;
	}
	else
	{
		save_Num_ += 1;
	}

	Read();
}

void MapEditScene::Initialize()
{
	std::string filename[MATH_MAX] =
	{
		"Math_Floor.png",
		"Math_Wall.png",
		"MATH_Hole.png",
		"Math_Conveyor.png",
		"Math_Togetoge.png",
		"Math_PitFall.png",
		"Math_Start.png",
		"Math_Goal.png",
	};
	for (int i = 0; i < MATH_MAX; i++)
	{
		filename[i] = "Assets\\" + filename[i];
		hPict_[i] = Image::Load(filename[i]);
		assert(hPict_[i] >= 0);
	}
	//マスのサイズ調整
	for (int x = 0; x < XSIZE; x++)
	{
		for (int y = 0; y < YSIZE; y++)
		{
			math_origin_[x][y] = math_[x][y];
			math_[x][y].mathPos_.scale_ = XMFLOAT3(1.0f / Direct3D::scrWidth * MATHSIZE, 1.0f / Direct3D::scrHeight * MATHSIZE, 1);
			math_[x][y].mathPos_.position_.x = ((float)x / Direct3D::scrWidth) * MATHSIZE + ((float)(x - XSIZE) / Direct3D::scrWidth) * MATHSIZE;
			math_[x][y].mathPos_.position_.y = ((float)y / Direct3D::scrHeight) * MATHSIZE + ((float)(y - YSIZE) / Direct3D::scrHeight) * MATHSIZE;
		}
	}

	hTgtgRoute_ = Image::Load("Assets\\Togetoge_Route.png");
	assert(hTgtgRoute_ >= 0);
	//とげとげルートのサイズ調整
	tTgtgRoute_.scale_ = 
		XMFLOAT3((1.0f / Direct3D::scrWidth * MATHSIZE) * MATHSIZE, 
				(1.0f / texture_size_.y * MATHSIZE) * (MATHSIZE / 3), 1);
	pText_ = new Text();
	pText_->Initialize();
}

void MapEditScene::Update()
{
	//debug出力例
	/*std::string resStr = std::to_string(mousePosX) + '\n';
	OutputDebugString(resStr.c_str());*/

	static XMFLOAT3 selectMath;
	static XMFLOAT3 tgtgRouteMathDown = XMFLOAT3(-1, -1, 0);
	static XMFLOAT3 tgtgRouteMathUp = XMFLOAT3(-1, -1, 0);

	float mousePosX = Input::GetMousePosition().x;
	float mousePosY = Input::GetMousePosition().y;
	mousePosX -= ((math_[0][0].mathPos_.position_.x + 1.0f) * Direct3D::scrWidth / 2) - MATHSIZE / 2;
	mousePosY -= ((-(math_[XSIZE - 1][YSIZE - 1].mathPos_.position_.y) + 1.0f) * Direct3D::scrHeight / 2) - MATHSIZE / 2;

	selectMath.x = mousePosX / MATHSIZE;
	selectMath.y = mousePosY / MATHSIZE;

	if (selectMath.x < 0 || selectMath.x >= XSIZE ||
		selectMath.y < 0 || selectMath.y >= YSIZE)
	{
		selectMath = XMFLOAT3(-1, -1, 0);
	}
	/*std::string resStr = "座標 : " + std::to_string((int)selectMath.x) + ", " + std::to_string((int)selectMath.y) + '\n';
	OutputDebugString(resStr.c_str());*/

	if (selectMath.x != -1 && selectMath.y != -1)
	{
		if (mathChangeNum_ < MATH_CHANGE_NUM_LIMIT ||
			math_origin_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ == MATH_FLOOR)
		{
			switch ((MATHTYPE)mathtype_)
			{
			case MATH_START:
				if (Input::IsMouseButton(0))
				{
					if (pTrans_->GetTurnNum() == 1)
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
						math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ = MATH_START;
						math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathPos_.rotate_ = XMFLOAT3(0, 0, 0);
					}
				}
				break;
			case MATH_GOAL:
				if (Input::IsMouseButton(0))
				{
					if (pTrans_->GetTurnNum() == 1)
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
						math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ = MATH_GOAL;
						math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathPos_.rotate_ = XMFLOAT3(0, 0, 0);
					}
				}
				break;
			case MATH_CONVEYOR:
				if (Input::IsMouseButtonDown(0))
				{
					if (math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ == MATHTYPE::MATH_CONVEYOR)
					{
						isConvRot_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y] = true;
					}
					else
					{
						math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ = (MATHTYPE)mathtype_;
					}
				}
				break;
			case MATH_TOGETOGE:
				if (Input::IsMouseButtonDown(0))
				{
					if (math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ == MATHTYPE::MATH_TOGETOGE)
					{
						tgtgRouteMathDown = XMFLOAT3((int)selectMath.x, YSIZE - 1 - (int)selectMath.y, 0);
					}
					else
					{
						math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ = (MATHTYPE)mathtype_;
					}
				}
			default:
				if (Input::IsMouseButton(0))
				{
					math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathPos_.rotate_ = XMFLOAT3(0, 0, 0);
					math_[(int)selectMath.x][YSIZE - 1 - (int)selectMath.y].mathType_ = (MATHTYPE)mathtype_;
				}
				break;
			}
		}
		SetMathChangeNum();
	}
	if (tgtgRouteMathDown.x != -1 && Input::IsMuoseButtonUp(0))
	{
		tgtgRouteMathUp = XMFLOAT3(mousePosX / MATHSIZE, mousePosY / MATHSIZE, 0);


		tgtgRouteMathDown = XMFLOAT3(-1, -1, 0);
	}
}


void MapEditScene::Draw()
{
	Image::SetTransform(hTgtgRoute_, tTgtgRoute_);
	Image::Draw(hTgtgRoute_);
	//pText_->Draw(1, 1, "g");
	for (int x = 0; x < XSIZE; x++)
	{
		for (int y = 0; y < YSIZE; y++)
		{
			float mathSin = abs(sin(XMConvertToRadians(math_[x][YSIZE - 1 - y].mathPos_.rotate_.z)));
			math_[x][YSIZE - 1 - y].mathPos_.scale_ = XMFLOAT3(
				1.0f / (Direct3D::scrWidth - (Direct3D::scrWidth - Direct3D::scrHeight) * mathSin) * MATHSIZE,
				1.0f / (Direct3D::scrHeight + (Direct3D::scrWidth - Direct3D::scrHeight) * mathSin) * MATHSIZE,
				1);

			if (isConvRot_[x][YSIZE - 1 - y])
			{
				math_[x][YSIZE - 1 - y].mathPos_.rotate_.z += 5;
			}
			if ((int)math_[x][YSIZE - 1 - y].mathPos_.rotate_.z % 90 == 0)
			{
				math_[x][YSIZE - 1 - y].mathPos_.rotate_.z = (int)(math_[x][YSIZE - 1 - y].mathPos_.rotate_.z / 90) * 90;
				isConvRot_[x][YSIZE - 1 - y] = false;
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
		case IDC_MAPEDIT_FLOOR:		mathtype_ = MATH_FLOOR; break;
		case IDC_MAPEDIT_WALL:		mathtype_ = MATH_WALL; break;
		case IDC_MAPEDIT_HOLL:		mathtype_ = MATH_HOLE; break;
		case IDC_MAPEDIT_CONVEYOR:	mathtype_ = MATH_CONVEYOR; break;
		case IDC_MAPEDIT_TOGETOGE:	mathtype_ = MATH_TOGETOGE; break;
		case IDC_MAPEDIT_PITFALL:	mathtype_ = MATH_PITFALL; break;
		case IDC_MAPEDIT_START:		mathtype_ = MATH_START; break;
		case IDC_MAPEDIT_GOAL:		mathtype_ = MATH_GOAL; break;
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
			if (pTrans_->GetSceneState() >= SCENESTATE::SCENE_MAPEDIT2_DELAY) EndDialog(hDlg, 0);
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
	std::string savefile = "StageSaveFile\\saveMath";
	savefile += std::to_string(save_Num_);
	write.open(savefile, std::ios::out);

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

	savefile = "StageSaveFile\\saveMathPos";
	savefile += std::to_string(save_Num_);
	write.open(savefile, std::ios::out);

	//  ファイルが開けなかったときのエラー表示
	if (!write) {
		std::cout << "ファイル " << savefile << " が開けません";
		return;
	}

	for (int i = 0; i < XSIZE; i++) {
		for (int j = 0; j < YSIZE; j++)
		{
			write.write((char*)&math_[i][j].mathPos_, sizeof(math_[i][j].mathPos_));
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
	std::string savefile = "StageSaveFile\\saveMath";
	
	savefile += std::to_string(save_Num_);
	read.open(savefile, std::ios::in);
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

	savefile = "StageSaveFile\\saveMathPos";
	savefile += std::to_string(save_Num_);
	read.open(savefile, std::ios::in);
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
			read.read((char*)&math_[i][j].mathPos_, sizeof(math_.at(i).at(j).mathPos_));
			//文字列ではないデータを読みこむ

		}
	}
	read.close();  //ファイルを閉じる
}

void MapEditScene::SetMathChangeNum()
{
	int num = 0;
	for (int x = 0; x < XSIZE; x++)
	{
		for (int y = 0; y < YSIZE; y++)
		{
			if (math_[x][y].mathType_ != math_origin_[x][y].mathType_ &&
				math_origin_[x][y].mathType_ != MATH_FLOOR)
			{
				num++;
			}
		}
	}
	mathChangeNum_ = num;
}
