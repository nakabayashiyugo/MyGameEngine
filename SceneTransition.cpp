#include "SceneTransition.h"
#include "MapEditScene.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"
#include "Engine/Image.h"

SceneTransition::SceneTransition(GameObject* parent)
	: GameObject(parent, "SceneTransition"), sceneState_(SCENE_MAPEDIT1), turnNum_(0),
	isClear_Player_{ false, false }, isFinished_(false), hPlayer1_(-1), hPlayer2_(-1),
	hWin_(-1), hLose_(-1)
{
	XSIZE = (rand() % 15) + 5;
	ZSIZE = (rand() % 15) + 5;

	Math_Resize(XSIZE, ZSIZE, &math_);

	for (int x = 0; x < XSIZE; x++)
	{
		for (int y = 0; y < ZSIZE; y++)
		{
			math_[x][y].mathType_ = MATH_FLOOR;
			math_[x][y].converyor_rotate_ = 0;
		}
	}
	Write();
	sceneState_ = SCENE_MAPEDIT2;
	Write();
}

void SceneTransition::Initialize()
{
	sceneState_ = SCENE_MAPEDIT1;
	hPlayer1_ = Image::Load("Assets\\Logo_Player1.png");
	assert(hPlayer1_ >= 0);
	hPlayer2_ = Image::Load("Assets\\Logo_Player2.png");
	assert(hPlayer2_ >= 0);
	hWin_ = Image::Load("Assets\\Logo_Win.png");
	assert(hWin_ >= 0);
	hLose_ = Image::Load("Assets\\Logo_Lose.png");
	assert(hLose_ >= 0);
}

void SceneTransition::Update()
{
	switch (sceneState_)
	{
	case SCENE_MAPEDIT1: turnNum_++; Instantiate<MapEditScene>(this); break;
	case SCENE_MAPEDIT2:Instantiate<MapEditScene>(this); break;
	case SCENE_STAGE1:
		pPS_[0]->Instantiate<PlayScene>(this);
		pPS_[0] = (PlayScene*)FindObject("PlayScene");
		pPS_[0]->SetPlayerNum(0);
		break;
	case SCENE_STAGE2:
		pPS_[1]->Instantiate<PlayScene>(this);
		pPS_[1] = (PlayScene*)FindObject("PlayScene");
		pPS_[1]->SetPlayerNum(1);
		break;
	case SCENE_TURNEND:
		if (isClear_Player_[0] == isClear_Player_[1])
		{
			sceneState_ = SCENE_MAPEDIT1;
			isClear_Player_[0] = isClear_Player_[1] = false;
		}
		else
		{
			isFinished_ = true;
		}
		break;
	default:
		break;
	}
}

void SceneTransition::Draw()
{
	Transform player;
	player.position_ = XMFLOAT3(0.8, 0.9, 0);
	player.scale_ = XMFLOAT3(0.2, 0.1, 1);
	switch (sceneState_)
	{
	case SCENE_MAPEDIT1_DELAY:
	case SCENE_STAGE1_DELAY:
		Image::SetTransform(hPlayer1_, player);
		Image::Draw(hPlayer1_);
		break;
	case SCENE_MAPEDIT2_DELAY:
	case SCENE_STAGE2_DELAY:
		Image::SetTransform(hPlayer2_, player);
		Image::Draw(hPlayer2_);
		break;
	}
	if (isFinished_)
	{
		player.position_ = XMFLOAT3(-0.3, 0.1, 0);
		Image::SetTransform(hPlayer1_, player);
		player.position_ = XMFLOAT3(0.3, 0.1, 0);
		Image::SetTransform(hPlayer2_, player);
		if (isClear_Player_[0] == true && isClear_Player_[1] == false)
		{
			player.position_ = XMFLOAT3(-0.3, -0.1, 0);
			Image::SetTransform(hWin_, player);
			player.position_ = XMFLOAT3(0.3, -0.1, 0);
			Image::SetTransform(hLose_, player);
		}
		else
		{
			player.position_ = XMFLOAT3(0.3, -0.3, 0);
			Image::SetTransform(hWin_, player);
			player.position_ = XMFLOAT3(-0.3, -0.3, 0);
			Image::SetTransform(hLose_, player);
		}
		Image::Draw(hPlayer1_);
		Image::Draw(hPlayer2_);
		Image::Draw(hWin_);
		Image::Draw(hLose_);
	}
}

void SceneTransition::Release()
{
}

void SceneTransition::Write()
{
	std::ofstream write;
	std::string savefile = "saveMath";
	savefile += std::to_string((int)sceneState_ + 1);
	write.open(savefile, std::ios::out | std::ios::binary);

	//  ファイルが開けなかったときのエラー表示
	if (!write) {
		std::cout << "ファイル " << savefile << " が開けません";
		return;
	}

	for (int i = 0; i < XSIZE; i++) {
		for (int j = 0; j < ZSIZE; j++)
		{
			write.write((char*)&math_[i][j].mathType_, sizeof(math_[i][j].mathType_));
			//文字列ではないデータをかきこむ
		}
	}

	write.close();  //ファイルを閉じる

	savefile = "saveConvRot";
	savefile += std::to_string((int)sceneState_ + 1);
	write.open(savefile, std::ios::out | std::ios::binary);

	//  ファイルが開けなかったときのエラー表示
	if (!write) {
		std::cout << "ファイル " << savefile << " が開けません";
		return;
	}

	for (int i = 0; i < XSIZE; i++) {
		for (int j = 0; j < ZSIZE; j++)
		{
			write.write((char*)&math_[i][j].converyor_rotate_, sizeof(math_[i][j].converyor_rotate_));
			//文字列ではないデータをかきこむ
		}
	}

	write.close();  //ファイルを閉じる
}
