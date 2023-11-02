#include <string>
#include <vector>
#include <array>
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Direct3D.h"
#include "TestScene.h"
#include "SceneTransition.h"
#include "Engine/RootJob.h"

#include "resource.h"

Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
	for (int i = 0; i < 5; i++)
	{
		hModel_[i] = -1;
	}
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize().x;
	ZSIZE = (int)pTrans_->GetMathSize().y;
	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);
	table_.resize(XSIZE);
	for (int x = 0; x < XSIZE; x++)
	{
		table_.at(x).resize(ZSIZE);
	}
	Read();
}

void Stage::Initialize()
{
	std::string modelName[5] =
	{
		"Block_Floor.fbx",
		"Block_Wall.fbx",
		"Block_Floor.fbx",
		"Block_Converyor.fbx",
		"Block_Togetoge.fbx",

	};
	std::string fname_base = "Assets\\";
	//モデルデータのロード
	for (int i = 0; i < 5; i++)
	{
		hModel_[i] = Model::Load(fname_base + modelName[i]);
		assert(hModel_[i] >= 0);
	}
}


void Stage::Update()
{
	
}

void Stage::Draw()
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			Transform mathTrans;
			mathTrans.position_.x = x;
			mathTrans.position_.z = z;
			if (table_[x][z].mathType_ != MATH_CONVEYOR)
			{
				Model::SetTransform(hModel_[MATH_FLOOR], mathTrans);
				Model::Draw(hModel_[MATH_FLOOR]);
			}
			else
			{
				Model::SetTransform(hModel_[table_[x][z].mathType_], mathTrans);
				Model::Draw(hModel_[table_[x][z].mathType_]);
			}

			if (table_[x][z].mathType_ != MATH_FLOOR)
			{
				Model::SetTransform(hModel_[MATH_FLOOR], mathTrans);
				Model::Draw(hModel_[MATH_FLOOR]);
			}
		}
	}
	
}

void Stage::Release()
{
}

void Stage::SetBlock(int x, int z, MATHTYPE _type)
{
	table_.at(x).at(z).mathType_ = _type;
	assert(_type <= MATHTYPE::MATH_MAX);
}

void Stage::Read()
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
			read.read((char*)&table_[i][j].mathType_, sizeof(table_.at(i).at(j).mathType_));
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
			read.read((char*)&table_[i][j].converyor_rotate_, sizeof(table_.at(i).at(j).converyor_rotate_));
			//文字列ではないデータを読みこむ

		}
	}
	read.close();  //ファイルを閉じる
}
