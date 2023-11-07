#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "TestScene.h"
#include "SceneTransition.h"

Controller::Controller(GameObject* parent)
	: GameObject(parent, "Controller"), velocity_(XMVectorSet(0, 0, 0, 0)), hModel_(-1)
	, camRot_(0, 0, 0), player_state_(STATE_WARK), stage_state_(STATE_PLAY)
{
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize().x;
	ZSIZE = (int)pTrans_->GetMathSize().y;
	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);
	math_.resize(XSIZE);
	for (int x = 0; x < XSIZE; x++)
	{
		math_.at(x).resize(ZSIZE);
	}
	TestScene* pTest = (TestScene*)FindObject("TestScene");
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			math_.at(x).at(z) = pTest->GetTableMath(x, z);
		}
	}
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			if (math_[x][z].mathType_ == MATH_START)
			{
				startPos_ = XMFLOAT3(x, 1, z);
			}
			if (math_[x][z].mathType_ == MATH_GOAL)
			{
				goalPos_ = XMFLOAT3(x, 1, z);
			}

		}
	}
}

void Controller::Initialize()
{
	transform_.position_ = startPos_;
	XMFLOAT3 camPos = transform_.position_;
	camPos.y = 10;
	Camera::SetPosition(camPos);

	hModel_ = Model::Load("Assets\\Player.fbx");
	assert(hModel_ >= 0);
}

void Controller::Update()
{
	switch (stage_state_)
	{
	case STATE_PLAY:
		PlayUpdate();
		break;
	case STATE_GOAL:
		KillMe();
		break;
	}
}

void Controller::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Controller::Release()
{
}

void Controller::PlayUpdate()
{
	//�d��
	static XMFLOAT3 gravity = XMFLOAT3(0, 0, 0);
	switch (player_state_)
	{
	case STATE_WARK:
		gravity = XMFLOAT3(0, 0, 0);
		transform_.position_.y = 1;
		break;
	case STATE_JAMP:
		gravity.y += 0.1f;
		if (transform_.position_.y >= 2.0f)
		{
			player_state_ = STATE_FALL;
		}
	case STATE_FALL:
		gravity.y += - 0.05f;
		if (transform_.position_.y < 1.0f)
		{
			player_state_ = STATE_WARK;
			return;
		}
		break;
	}

	XMFLOAT3 prevPos = transform_.position_;
	velocity_ = XMVectorSet(0, 0, 0, 0);
	XMVECTOR cameraBase = XMVectorSet(0, 5, -5, 0);

	if (transform_.position_.x + 0.5f >= 0 && transform_.position_.x + 0.5f < XSIZE &&
		transform_.position_.z + 0.5f >= 0 && transform_.position_.z + 0.5f < ZSIZE &&
		transform_.position_.y >= 0.5f)
	{

		switch (math_[(transform_.position_.x + 0.5f)][(transform_.position_.z + 0.5f)].mathType_)
		{
		case MATH_WALL:
			transform_.position_ = prevPos;
			break;
		case MATH_GOAL:
			stage_state_ = STATE_GOAL;
			break;
		case MATH_HOLL:
			player_state_ = STATE_FALL;
			break;
		default:break;
		}
	}
	else
	{
		player_state_ = STATE_FALL;
	}

	//�O�㍶�E�ړ�
	if (Input::IsKey(DIK_W))
	{
		transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
		velocity_ += XMVectorSet(0.0f, 0.0f, 0.1f, 0.0f);
	}
	if (Input::IsKey(DIK_S))
	{
		transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
		velocity_ += XMVectorSet(0.0f, 0.0f, -0.1f, 0.0f);
	}
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
		velocity_ += XMVectorSet(-0.1f, 0.0f, 0.0f, 0.0f);
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
		velocity_ += XMVectorSet(0.1f, 0.0f, 0.0f, 0.0f);
	}
	//�ǂ̕����������X�s�[�h�ɂ���
	velocity_ = XMVector4Normalize(velocity_); //���K�����đS��1�ɂȂ�
	velocity_ /= 20; //1���ᑬ�����邩�犄��

	//��]
	if (Input::IsKey(DIK_RIGHT))
	{
		camRot_.y++;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		camRot_.y--;
	}

	//�W�����v
	if (Input::IsKeyDown(DIK_Q))
	{
		player_state_ = STATE_JAMP;
	}

	//�J������]
	XMMATRIX yrot = XMMatrixRotationY(XMConvertToRadians(camRot_.y));

	XMVECTOR cameraRotVec = XMVector3Transform(cameraBase, yrot);

	XMVECTOR vPos = XMVectorSet(transform_.position_.x, 1, transform_.position_.z, 0);

	Camera::SetPosition(vPos + cameraRotVec);
	Camera::SetTarget(XMFLOAT3(transform_.position_.x, 1, transform_.position_.z));

	//�ړ�������]
	velocity_ = XMVector3Transform(velocity_, yrot);

	velocity_ += XMLoadFloat3(&gravity);
	transform_.position_ += velocity_;
}
