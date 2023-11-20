#include "TestScene.h"
#include "Stage.h"
#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "SceneTransition.h"

TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize_x();
	ZSIZE = (int)pTrans_->GetMathSize_z();
	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);
	math_.resize(XSIZE);
	for (int x = 0; x < XSIZE; x++)
	{
		math_.at(x).resize(ZSIZE);
	}
	Read();
}

void TestScene::Initialize()
{
	pStage_ = (Stage*)FindObject("Stage");
	pCont_ = (Controller*)FindObject("Controller");
	pStage_->Instantiate<Stage>(this);
	pCont_->Instantiate<Controller>(this);
}

void TestScene::Update()
{
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}

void TestScene::Read()
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
