#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "SceneTransition.h"
#include "Timer.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), table_Change_(false)
{
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize_x();
	ZSIZE = (int)pTrans_->GetMathSize_z();
	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);
	Math_Resize(XSIZE, ZSIZE, &math_);
	Read();
	
}

void PlayScene::Initialize()
{
	pStage_ = (Stage*)FindObject("Stage");
	pPlayer_ = (Player*)FindObject("Player");
	pStage_->Instantiate<Stage>(this);
	pPlayer_->Instantiate<Player>(this);
}

void PlayScene::Update()
{
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	static Timer pTimer = Timer(30);
	pStage_ = (Stage*)FindObject("Stage");
	pPlayer_ = (Player*)FindObject("Player");
	if (pPlayer_->Is_Goal())
	{
		pTrans_->SetSceneState(0);
		pPlayer_->KillMe();
		pStage_->KillMe();
		KillMe();
	}
	if (pTimer.Time_Update())
	{
		pPlayer_->KillMe();
		pStage_->KillMe();
		KillMe();
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}

void PlayScene::Read()
{
	std::ifstream read;
	read.open("saveMath1", std::ios::in | std::ios::binary);
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
		for (int j = 0; j < ZSIZE; j++)
		{
			read.read((char*)&math_[i][j].mathType_, sizeof(math_.at(i).at(j).mathType_));
			//文字列ではないデータを読みこむ

		}
	}
	read.close();  //ファイルを閉じる

	read.open("saveConvRot1", std::ios::in | std::ios::binary);
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
		for (int j = 0; j < ZSIZE; j++)
		{
			read.read((char*)&math_[i][j].converyor_rotate_, sizeof(math_.at(i).at(j).converyor_rotate_));
			//文字列ではないデータを読みこむ

		}
	}
	read.close();  //ファイルを閉じる
}

XMFLOAT3 PlayScene::GetPlayerPos()
{
	pPlayer_ = (Player*)FindObject("Player");
	return pPlayer_->GetPosition();
}
