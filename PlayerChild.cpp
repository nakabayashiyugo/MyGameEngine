#include "PlayerChild.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

PlayerChild::PlayerChild(GameObject* parent)
	: GameObject(parent, "PlayerChild"), hModel_(-1)
{
}

PlayerChild::~PlayerChild()
{
}

void PlayerChild::Initialize()
{
	hModel_ = Model::Load("Assets\\oden2.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);
}

void PlayerChild::Update()
{
	transform_.rotate_.y++;
	transform_.position_.z += 0.5f;
	if (transform_.position_.z >= 50)
	{
		KillMe();
	}
}

void PlayerChild::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void PlayerChild::Release()
{
}
