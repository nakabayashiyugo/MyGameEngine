#include <string>
#include <vector>
#include <array>
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Direct3D.h"
#include "PlayScene.h"
#include "SceneTransition.h"
#include "Engine/RootJob.h"
#include "Engine/Camera.h"

#include "resource.h"

Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
	for (int i = 0; i < 5; i++)
	{
		hModel_[i] = -1;
	}
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize_x();
	ZSIZE = (int)pTrans_->GetMathSize_z();
	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);
	Math_Resize(XSIZE, ZSIZE, &math_);
	pPlayScene_ = (PlayScene*)FindObject("PlayScene");
	SetTableMath(pPlayScene_->GetTableMath());
}

void Stage::Initialize()
{
	std::string modelName[MATH_MAX] =
	{
		"Block_Floor.fbx",
		"Block_Wall.fbx",
		"Block_Floor.fbx",
		"Block_Converyor.fbx",
		"Block_Togetoge.fbx",
		"Block_Floor.fbx",
		"Block_Start.fbx",
		"Block_Goal.fbx"
	};
	std::string fname_base = "Assets\\";
	//モデルデータのロード
	for (int i = 0; i < MATH_MAX; i++)
	{
		hModel_[i] = Model::Load(fname_base + modelName[i]);
		assert(hModel_[i] >= 0);
	}
}


void Stage::Update()
{
	if (pPlayScene_->GetPlayerPos().x >= 0 && pPlayScene_->GetPlayerPos().x < XSIZE &&
		pPlayScene_->GetPlayerPos().z >= 0 && pPlayScene_->GetPlayerPos().z < ZSIZE)
	{
		if (math_[pPlayScene_->GetPlayerPos().x][pPlayScene_->GetPlayerPos().z].mathType_ == MATH_PITFALL)
		{
			math_[pPlayScene_->GetPlayerPos().x][pPlayScene_->GetPlayerPos().z].mathType_ = MATH_HOLL;
			Write();
		}
	}
}

void Stage::Draw()
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			Transform mathTrans;
			mathTrans.position_ = XMFLOAT3(x, 0, z);
			switch (math_[x][z].mathType_)
			{
			case MATH_FLOOR:
				Model::SetTransform(hModel_[math_[x][z].mathType_], mathTrans);
				Model::Draw(hModel_[math_[x][z].mathType_]);
				break;
			case MATH_WALL :
				Model::SetTransform(hModel_[MATH_FLOOR], mathTrans);
				Model::Draw(hModel_[MATH_FLOOR]);
				mathTrans.position_.y = 1;
				Model::SetTransform(hModel_[math_[x][z].mathType_], mathTrans);
				Model::Draw(hModel_[math_[x][z].mathType_]);
				break;
			case MATH_CONVEYOR:
				mathTrans.rotate_.y = -(math_[x][z].converyor_rotate_ * 90);
				Model::SetTransform(hModel_[math_[x][z].mathType_], mathTrans);
				Model::Draw(hModel_[math_[x][z].mathType_]);
				break;
			case MATH_TOGETOGE:
				Model::SetTransform(hModel_[MATH_FLOOR], mathTrans);
				Model::Draw(hModel_[MATH_FLOOR]);
				mathTrans.position_.y = 1;
				Model::SetTransform(hModel_[math_[x][z].mathType_], mathTrans);
				Model::Draw(hModel_[math_[x][z].mathType_]);
				break;
			case MATH_PITFALL:
				Model::SetTransform(hModel_[math_[x][z].mathType_], mathTrans);
				Model::Draw(hModel_[math_[x][z].mathType_]);

				break;
			case MATH_START:
				Model::SetTransform(hModel_[MATH_FLOOR], mathTrans);
				Model::Draw(hModel_[MATH_FLOOR]);
				mathTrans.position_.y = 1;
				Model::SetTransform(hModel_[math_[x][z].mathType_], mathTrans);
				Model::Draw(hModel_[math_[x][z].mathType_]);
				break;
			case MATH_GOAL:
				Model::SetTransform(hModel_[MATH_FLOOR], mathTrans);
				Model::Draw(hModel_[MATH_FLOOR]);
				mathTrans.position_.y = 1;
				Model::SetTransform(hModel_[math_[x][z].mathType_], mathTrans);
				Model::Draw(hModel_[math_[x][z].mathType_]);
				break;
			}
		}
	}
	
}

void Stage::Release()
{
}

void Stage::SetBlock(int x, int z, MATHTYPE _type)
{
	math_.at(x).at(z).mathType_ = _type;
	assert(_type <= MATHTYPE::MATH_MAX);
}

void Stage::Write()
{
	std::ofstream write;
	std::string savefile = "saveMath";
	savefile += std::to_string((int)pTrans_->GetSceneState() - 6);
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
	savefile += std::to_string((int)pTrans_->GetSceneState() - 6);
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


	pPlayScene_->Read();
	pPlayScene_->SetTableChange(true);
}

void Stage::SetTableMath(std::vector<std::vector<MATHDEDAIL>> _math)
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			math_.at(x).at(z) = _math.at(x).at(z);
		}
	}
}


