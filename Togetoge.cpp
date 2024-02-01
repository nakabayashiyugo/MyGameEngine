#include "Togetoge.h"
#include "Engine/Model.h"

Togetoge::Togetoge(GameObject* parent) :
	GameObject(parent, "Togetoge"), hModel_(-1)
{
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