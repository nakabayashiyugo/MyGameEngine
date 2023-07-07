#include "Player.h"
#include "Engine/Fbx.h"

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), pFbx(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets\\oden2.fbx");
}

void Player::Update()
{
	transform_.rotate_.y += 0.1;
}

void Player::Draw()
{
	pFbx->Draw(this->transform_);
}

void Player::Release()
{
	SAFE_RELEASE(pFbx);
	SAFE_DELETE(pFbx);
}
