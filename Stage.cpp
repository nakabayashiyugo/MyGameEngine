#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_(-1)
{
}

void Stage::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Assets\\BoxDefault.fbx");
	assert(hModel_ >= 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			transform_.position_ = XMFLOAT3(x, 0, z);
			Model::SetTransform(hModel_, transform_);
			Model::Draw(hModel_);
		}
	}
	
}

void Stage::Release()
{
}
