#include "Togetoge.h"
#include "Stage.h"
#include "Engine/Model.h"

Togetoge::Togetoge(GameObject* parent) :
	GameObject(parent, "Togetoge"), hModel_(-1)
{
	Stage* pStage = (Stage*)FindObject("Stage");
	transform_.position_ = pStage->GetTogetogeInitPos();
	transform_.position_.y = 1;
}

void Togetoge::Initialize()
{
	hModel_ = Model::Load("Assets\\Block_Togetoge.fbx");
	assert(hModel_ >= 0);
}

void Togetoge::Update()
{
}

void Togetoge::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Togetoge::Release()
{
}