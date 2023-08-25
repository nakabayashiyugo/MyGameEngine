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
	Camera::SetPosition(XMFLOAT3(7, 10, 3));
	
}

void Controller::Update()
{
	Camera::SetTarget(XMFLOAT3(transform_.position_));
	transform_.position_ += velocity_;
	velocity_ = XMVectorSet(0, 0, 0, 0);

	if (Input::IsKey(DIK_W))
	{
		velocity_ = XMVectorSet(0, 0, 0.1, 0);
	}
	if (Input::IsKey(DIK_S))
	{
		velocity_ = XMVectorSet(0, 0, -0.1, 0);
	}
	if (Input::IsKey(DIK_A))
	{
		velocity_ = XMVectorSet(-0.1, 0, 0, 0);
	}
	if (Input::IsKey(DIK_D))
	{
		velocity_ = XMVectorSet(0.1, 0, 0.1, 0);
	}
	
}

void Controller::Draw()
{
}

void Controller::Release()
{
}
