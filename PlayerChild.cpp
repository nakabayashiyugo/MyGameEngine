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
	isShaft_ = false;

	pFbx = new Fbx;
	pFbx->Load("Assets\\oden2.fbx");
}

void PlayerChild::Update()
{
	transform_.position_.x = -4;
	transform_.rotate_.y++;
	transform_.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);
}

void PlayerChild::Draw()
{
	pFbx->Draw(this->transform_, isShaft_);
}

void PlayerChild::Release()
{
	SAFE_RELEASE(pFbx);
	SAFE_DELETE(pFbx);
}
