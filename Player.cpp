#include "Player.h"
#include "PlayerChild.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"

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

	Instantiate<PlayerChild>(this);
}

void Player::Update()
{
	transform_.rotate_.y ++;

	if (Input::IsKeyDown(DIK_SPACE))
	{
		this->KillMe();
	}
}

void Player::Draw()
{
	pFbx->Draw(this->transform_, isShaft_);
}

void Player::Release()
{
	//SAFE_RELEASE(pFbx);
	SAFE_DELETE(pFbx);
}
