#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

Controller::Controller(GameObject* parent)
	: GameObject(parent, "Controller"), velocity_(XMVectorSet( 0, 0, 0, 0 ))
{
}

void Controller::Initialize()
{
	transform_.position_ = XMFLOAT3(7, 1, 7);
	Camera::SetPosition(XMFLOAT3(7, 1, 7));
}

void Controller::Update()
{
	velocity_ = XMVectorSet(0, 0, 0, 0);
	XMVECTOR cameraBase = XMVectorSet(0, 0, -10, 0);

	//‘OŒã¶‰EˆÚ“®
	if (Input::IsKey(DIK_W))
	{
		velocity_ += XMVectorSet(0.0f, 0.0f, 0.1f, 0.0f);
	}
	if (Input::IsKey(DIK_S))
	{
		velocity_ += XMVectorSet(0.0f, 0.0f, -0.1f, 0.0f);
	}
	if (Input::IsKey(DIK_A))
	{
		velocity_ += XMVectorSet(-0.1f, 0.0f, 0.0f, 0.0f);
	}
	if (Input::IsKey(DIK_D))
	{
		velocity_ += XMVectorSet(0.1f, 0.0f, 0.0f, 0.0f);
	}
	//‚Ç‚Ì•ûŒü‚à“¯‚¶ƒXƒs[ƒh‚É‚·‚é
	velocity_ = XMVector4Normalize(velocity_); //³‹K‰»‚µ‚Ä‘S•”1‚É‚È‚é
	velocity_ /= 10; //1‚¶‚á‘¬‚·‚¬‚é‚©‚çŠ„‚é

	//‰ñ“]
	if (Input::IsKey(DIK_UP))
	{
		transform_.rotate_.x++;
		if (transform_.rotate_.x >= 89.0f)
		{
			transform_.rotate_.x = 89;
		}
	}
	if (Input::IsKey(DIK_DOWN))
	{
		transform_.rotate_.x--;
		if (transform_.rotate_.x <= 0.0f)
		{
			transform_.rotate_.x = 0;
		}
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y++;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y--;
	}
	//ƒJƒƒ‰‰ñ“]
	XMMATRIX xrot = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	XMMATRIX yrot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	XMMATRIX rot = xrot * yrot;

	XMVECTOR cameraRotVec = XMVector3Transform(cameraBase, rot);

	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	Camera::SetPosition(vPos + cameraRotVec);
	Camera::SetTarget(XMFLOAT3(transform_.position_));

	//ˆÚ“®•ûŒü‰ñ“]
	velocity_ = XMVector3Transform(velocity_, yrot);

	transform_.position_ += velocity_;
	
}

void Controller::Draw()
{
}

void Controller::Release()
{
}
