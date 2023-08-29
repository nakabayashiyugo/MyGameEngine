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
	Camera::SetPosition(XMFLOAT3(7, 16, 1));
	
}

void Controller::Update()
{
	velocity_ = XMVectorSet(0, 0, 0, 0);
	XMFLOAT3 cameraPos = XMFLOAT3(0, 15, -5);

	if (Input::IsKey(DIK_W))
	{
		velocity_ += XMVectorSet(0, 0, 0.1, 0);
	}
	if (Input::IsKey(DIK_S))
	{
		velocity_ += XMVectorSet(0, 0, -0.1, 0);
	}
	if (Input::IsKey(DIK_A))
	{
		velocity_ += XMVectorSet(-0.1, 0, 0, 0);
	}
	if (Input::IsKey(DIK_D))
	{
		velocity_ += XMVectorSet(0.1, 0, 0.0, 0);
	}

	//rotate
	static int rotNum = 0;
	if (Input::IsKey(DIK_UP))
	{
	}
	if (Input::IsKey(DIK_DOWN))
	{
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		rotNum++;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		rotNum--;
	}
	transform_.rotate_.y = rotNum;
	XMVECTOR cameraBase = XMLoadFloat3(&cameraPos);
	XMMATRIX yrot = XMMatrixRotationY(XMConvertToRadians(rotNum));
	XMVECTOR CameraRotVec = XMVector3Transform(cameraBase, yrot);
	XMFLOAT3 v;
	XMStoreFloat3(&v, CameraRotVec);

	Camera::SetPosition(XMFLOAT3(transform_.position_.x + v.x, transform_.position_.y + v.y,
		transform_.position_.z + v.z));
	Camera::SetTarget(XMFLOAT3(transform_.position_));

	velocity_ = XMVector3Transform(velocity_, yrot);

	transform_.position_ += velocity_;
	
}

void Controller::Draw()
{
}

void Controller::Release()
{
}
