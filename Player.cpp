#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "PlayScene.h"
#include "SceneTransition.h"
#include "Stage.h"

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), 
	hModel_(-1),
	velocity_(XMVectorSet(0, 0, 0, 0)), 
	sub_velocity_(XMVectorSet(0, 0, 0, 0)),
	jamp_start_velocity_(XMVectorSet(0, 0, 0, 0)),
	camRot_(0, 0, 0), 
	player_state_(STATE_WARK), 
	stage_state_(STATE_START),
	gravity_(0, 0, 0), 
	air_dec_velocity_(1),
	hurdle_Limit_(0)
{
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize_x();
	ZSIZE = (int)pTrans_->GetMathSize_z();
	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);

	Math_Resize(XSIZE, ZSIZE, &math_);

	pPlayScene_ = (PlayScene*)FindObject("PlayScene");

	SetTableMath(pPlayScene_->GetTableMath());

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
	XMFLOAT3 camPos = transform_.position_;
	camPos.y = 10;
	Camera::SetPosition(camPos);

	hModel_ = Model::Load("Assets\\Player.fbx");
	assert(hModel_ >= 0);
}

void Player::Update()
{
	Stage* pStage = (Stage*)FindObject("Stage");
	
	switch (stage_state_)
	{
	case STATE_START:
		transform_.position_ = startPos_;
		stage_state_ = STATE_PLAY;
		player_state_ = STATE_WARK;
		break;
	case STATE_PLAY:
		PlayUpdate();
		break;
	case STATE_GOAL:
		isGoal_ = true;
		break;
	}

	if (pPlayScene_->GetTableChange())
	{
		SetTableMath(pPlayScene_->GetTableMath());
		pPlayScene_->SetTableChange(true);
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

	switch (player_state_)
	{
	case STATE_WARK:
		gravity_ = XMFLOAT3(0, 0, 0);
		transform_.position_.y = 1;
		air_dec_velocity_ = 1;
		jamp_start_velocity_ = XMVectorSet(0, 0, 0, 0);
		break;
	case STATE_JAMP:
		gravity_.y = 0.2f;
		air_dec_velocity_ = 2;
		if (transform_.position_.y >= 1.5f)
		{
			player_state_ = STATE_FALL;
		}
		break;
	case STATE_FALL:
		gravity_.y += -0.01f;
		air_dec_velocity_ = 2;
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
		stage_state_ = STATE_START;
		break;
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
			converyor_velocity = converyor_velocity / (float)20 * 0.8f;
			if(player_state_ == STATE_WARK)		velocity_ += converyor_velocity;
			break;
		case MATH_TOGETOGE:
			player_state_ = STATE_DEAD;
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

	//ジャンプ
	if (Input::IsKeyDown(DIK_SPACE) && player_state_ == STATE_WARK)
	{
		player_state_ = STATE_JAMP;
		jamp_start_velocity_ = velocity_ / 2;
	}
	velocity_ += XMLoadFloat3(&gravity_);
	velocity_ += jamp_start_velocity_;
	transform_.position_ += velocity_;
}

bool Player::Is_InSide_Table()
{
	return transform_.position_.x + 0.5f >= 0 && transform_.position_.x + 0.5f < XSIZE &&
		transform_.position_.z + 0.5f >= 0 && transform_.position_.z + 0.5f < ZSIZE;
}

void Player::PlayerOperation()
{
	//velocity_ = XMVectorSet(0, 0, 0, 0);

	XMVECTOR cameraBase = XMVectorSet(0, 7, -5, 0);

	static int dec_velocity_ = 20;

	//前後左右移動
	if (Input::IsKey(DIK_W))
	{
		transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
		sub_velocity_ += XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		dec_velocity_ = 20;
	}
	if (Input::IsKey(DIK_S))
	{
		transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
		sub_velocity_ += XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
		dec_velocity_ = 30;
	}
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
		sub_velocity_ += XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
		dec_velocity_ = 30;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
		sub_velocity_ += XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		dec_velocity_ = 30;
	}	
	sub_velocity_ = XMVector4Normalize(sub_velocity_); //正規化して全部1になる
	velocity_ = sub_velocity_ / dec_velocity_ / air_dec_velocity_; 

	dec_velocity_ += 5;

	if (dec_velocity_ >= 100)
	{
		velocity_ = sub_velocity_ = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		dec_velocity_ = 20;
	}

	//回転
	if (Input::IsKey(DIK_RIGHT))
	{
		camRot_.y++;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		camRot_.y--;
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

void Player::SetTableMath(std::vector<std::vector<MATHDEDAIL>> _math)
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			math_.at(x).at(z) = _math.at(x).at(z);
		}
	}
}
