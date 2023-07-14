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

	//GameObject*  pPlayerChild = Instantiate<PlayerChild>(this);
	//GameObject*  pPlayerChild2 = Instantiate<PlayerChild>(this);

	//pPlayerChild->SetTransformPos(XMFLOAT3(2.0f, 1.0f, 0.0f));
	//pPlayerChild2->SetTransformPos(XMFLOAT3(-2.0f, 1.0f, 0.0f));
}

void Player::Update()
{
	transform_.rotate_.y += 1;

	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 0.1f;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject* pBullet = Instantiate<PlayerChild>(pParent_);
		pBullet->SetTransformPos(transform_.position_);
	}

}

void Player::Draw()
{
	pFbx->Draw(this->transform_);
}

void Player::Release()
{
	//SAFE_RELEASE(pFbx);
	//SAFE_DELETE(pFbx);
}
