#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "PlayScene.h"
#include "SceneTransition.h"
#include "Stage.h"

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), velocity_(XMVectorSet(0, 0, 0, 0)), hModel_(-1),
	camRot_(0, 0, 0), player_state_(STATE_WARK), stage_state_(STATE_PLAY),
	gravity_(0, 0, 0), dec_velocity_(1)
{
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize_x();
	ZSIZE = (int)pTrans_->GetMathSize_z();
	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);

	Math_Resize(XSIZE, ZSIZE, &math_);

	PlayScene* pTest = (PlayScene*)FindObject("PlayScene");
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
				startPos_ = XMFLOAT3((float)x, 1.0f, (float)z);
			}
			if (math_[x][z].mathType_ == MATH_GOAL)
			{
				goalPos_ = XMFLOAT3((float)x, 1, (float)z);
			}

		}
	}
}

void Player::Initialize()
{
	transform_.position_ = startPos_;
	XMFLOAT3 camPos = transform_.position_;
	camPos.y = 10;
	Camera::SetPosition(camPos);

	hModel_ = Model::Load("Assets\\Player.fbx");
	assert(hModel_ >= 0);
}

void Player::Update()
{
	Stage* pStage = (Stage*)FindObject("Stage");
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	
	switch (stage_state_)
	{
	case STATE_PLAY:
		PlayUpdate();
		break;
	case STATE_GOAL:
		pTrans_->SetSceneState(0);
		break;
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::PlayUpdate()
{
	XMFLOAT3 prevPos = transform_.position_;
	PlayerOperation();

	static XMFLOAT3 table_hit_point = XMFLOAT3(0, 0, 0);
	static bool is_table_hit = false;

	XMVECTOR prev_velocity = XMVectorSet(0, 0, 0, 0);
	switch (player_state_)
	{
	case STATE_WARK:
		gravity_ = XMFLOAT3(0, 0, 0);
		transform_.position_.y = 1;
		dec_velocity_ = 1;
		break;
	case STATE_JAMP:
		prev_velocity = velocity_;
		gravity_.y = 0.2f;
		dec_velocity_ = 10;
		if (transform_.position_.y >= 1.5f)
		{
			player_state_ = STATE_FALL;
		}
		break;
	case STATE_FALL:
		gravity_.y += -0.01f;
		dec_velocity_ = 10;
		if (transform_.position_.y < 1.0f && !is_table_hit)
		{
			is_table_hit = true;
			table_hit_point = transform_.position_;
			if (Is_InSide_Table() &&
				math_[(int)(table_hit_point.x + 0.5f)][(int)(table_hit_point.z + 0.5f)].mathType_ != MATH_HOLL)
			{
				player_state_ = STATE_WARK;
				is_table_hit = false;
				return;
			}
		}
		break;
	case STATE_DEAD:
		KillMe();
	}

	//コンベアによって移動する方向
	XMVECTOR converyor_velocity = XMVectorSet(-1.0f, 0, 0, 0);
	XMFLOAT3 velo;
	if (Is_InSide_Table() && transform_.position_.y >= 0.5f)
	{
		switch (math_[(int)(transform_.position_.x + 0.5f)][(int)(transform_.position_.z + 0.5f)].mathType_)
		{
		case MATH_WALL:
			XMStoreFloat3(&velo, velocity_);
			if(velo.x != 0)		
				transform_.position_.x = prevPos.x;
			if(velo.z != 0)		
				transform_.position_.z = prevPos.z;
			break;
		case MATH_CONVEYOR:
			XMMATRIX yrot = XMMatrixRotationY(XMConvertToRadians(math_[(int)(transform_.position_.x + 0.5f)][(int)(transform_.position_.z + 0.5f)].converyor_rotate_ * -90.0f));
			converyor_velocity = XMVector3Transform(converyor_velocity, yrot);	//その回転でベクトルの向きを変える
			converyor_velocity = converyor_velocity / (float)(20 + dec_velocity_) * 0.8f;
			if(player_state_ == STATE_WARK)	velocity_ += converyor_velocity;
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
	velocity_ += XMLoadFloat3(&gravity_);
	transform_.position_ += velocity_;
}

bool Player::Is_InSide_Table()
{
	return transform_.position_.x + 0.5f >= 0 && transform_.position_.x + 0.5f < XSIZE &&
		transform_.position_.z + 0.5f >= 0 && transform_.position_.z + 0.5f < ZSIZE;
}

void Player::PlayerOperation()
{
	velocity_ = XMVectorSet(0, 0, 0, 0);

	XMVECTOR cameraBase = XMVectorSet(0, 5, -5, 0);

	//前後左右移動
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
	//どの方向も同じスピードにする
	velocity_ = XMVector4Normalize(velocity_); //正規化して全部1になる
	velocity_ /= (float)(20 + dec_velocity_); //1じゃ速すぎるから割る

	//回転
	if (Input::IsKey(DIK_RIGHT))
	{
		camRot_.y++;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		camRot_.y--;
	}

	//ジャンプ
	if (Input::IsKeyDown(DIK_SPACE) && player_state_ == STATE_WARK)
	{
		player_state_ = STATE_JAMP;
	}

	//カメラ回転
	XMMATRIX yrot = XMMatrixRotationY(XMConvertToRadians(camRot_.y));

	XMVECTOR cameraRotVec = XMVector3Transform(cameraBase, yrot);

	XMVECTOR vPos = XMVectorSet(transform_.position_.x, 1, transform_.position_.z, 0);

	Camera::SetPosition(vPos + cameraRotVec);
	Camera::SetTarget(XMFLOAT3(transform_.position_.x, 1, transform_.position_.z));

	//移動方向回転
	velocity_ = XMVector3Transform(velocity_, yrot);
}
