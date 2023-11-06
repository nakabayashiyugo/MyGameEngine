#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "TestScene.h"

Controller::Controller(GameObject* parent)
	: GameObject(parent, "Controller"), velocity_(XMVectorSet( 0, 0, 0, 0 )), hModel_(-1)
{
}

void Controller::Initialize()
{
	TestScene* pTest = (TestScene*)FindObject("TestScene");
	transform_.position_ = pTest->GetStartPos();
	XMFLOAT3 camPos = transform_.position_;
	camPos.y = 10;
	Camera::SetPosition(camPos);

	hModel_ = Model::Load("Assets\\Player.fbx");
	assert(hModel_ >= 0);
}

void Controller::Update()
{
	velocity_ = XMVectorSet(0, 0, 0, 0);
	XMVECTOR cameraBase = XMVectorSet(0, 5, -5, 0);

	//前後左右移動
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
	//どの方向も同じスピードにする
	velocity_ = XMVector4Normalize(velocity_); //正規化して全部1になる
	velocity_ /= 20; //1じゃ速すぎるから割る

	//回転
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y++;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y--;
	}
	//カメラ回転
	XMMATRIX xrot = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	XMMATRIX yrot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	XMMATRIX rot = xrot * yrot;

	XMVECTOR cameraRotVec = XMVector3Transform(cameraBase, rot);

	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	Camera::SetPosition(vPos + cameraRotVec);
	Camera::SetTarget(XMFLOAT3(transform_.position_));

	//移動方向回転
	velocity_ = XMVector3Transform(velocity_, yrot);

	transform_.position_ += velocity_;
	
}

void Controller::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Controller::Release()
{
}
