#include "PlayerChild.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"

PlayerChild::PlayerChild(GameObject* parent)
	: GameObject(parent, "PlayerChild"), pFbx(nullptr)
{
}

PlayerChild::~PlayerChild()
{
}

void PlayerChild::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets\\oden2.fbx");

	transform_.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);
}

void PlayerChild::Update()
{
	transform_.rotate_.y++;
	if (transform_.rotate_.y >= 300)
	{
		KillMe();
	}
}

void PlayerChild::Draw()
{
	pFbx->Draw(this->transform_);
}

void PlayerChild::Release()
{
	SAFE_RELEASE(pFbx);
	SAFE_DELETE(pFbx);
}
