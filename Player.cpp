#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "Engine/SphereCollider.h"
#include "PlayScene.h"
#include "SceneTransition.h"
#include "Stage.h"
#include "Timer.h"
#include "StageOrigin.h"

const float MODELSIZE = 0.8f;

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), 
	hModel_(-1),
	velocity_(XMVectorSet(0, 0, 0, 0)), sub_velocity_(XMVectorSet(0, 0, 0, 0)), jamp_start_velocity_(XMVectorSet(0, 0, 0, 0)),
	eyeDirection_(XMVectorSet(0, 0, 1, 0)), prevEyeDirection_(XMVectorSet(0, 0, 0, 0)),
	camRot_(0, 0, 0), 
	player_state_(STATE_WARK), 
	stage_state_(STATE_START),
	gravity_(0, 0, 0), 
	air_dec_velocity_(1),
	hurdle_Limit_(0),
	wallHitDir_(0)
{
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize_x();
	ZSIZE = (int)pTrans_->GetMathSize_z();

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
				goalPos_ = XMFLOAT3((float)x, 1.0f, (float)z);
			}
		}
	}
}

void Player::Initialize()
{
	std::string fileName = "Assets\\Player";
	fileName += std::to_string(pPlayScene_->GetPlayerNum() + 1) + ".fbx";
	hModel_ = Model::Load("Assets\\Player1.fbx");
	assert(hModel_ >= 0);
	
	pTimer_ = (Timer*)FindObject("Timer");
	pTimer_->Instantiate<Timer>(this);
	Model::SetAnimFrame(hModel_, 1, 180, 1);
}

void Player::Update()
{
	Stage* pStage = (Stage*)FindObject("Stage");
	
	switch (stage_state_)
	{
	case STATE_START:
		transform_.position_ = startPos_;
		velocity_ = sub_velocity_ = XMVectorSet(0, 0, 0, 0);
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
		pPlayScene_->SetTableChange(false);
	}
}

void Player::Draw()
{ 
	transform_.scale_ = XMFLOAT3(0.05f, 0.05f, 0.05f);
	
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::PlayUpdate()
{
	SphereCollider* pSC = new SphereCollider(MODELSIZE / 2);
	this->AddCollider(pSC);

	//TimeOver
	pTimer_ = (Timer*)FindObject("Timer");
	if (pTimer_->GetTimeUpped())
	{
		stage_state_ = STATE_FAILURE;
	}

	PlayerOperation();

	static XMFLOAT3 table_hit_point = XMFLOAT3(0, 0, 0);
	static bool is_table_hit = false;

	switch (player_state_)
	{
	case STATE_WARK:
		table_hit_point = XMFLOAT3(0, 0, 0);
		is_table_hit = false;
		gravity_ = XMFLOAT3(0, 0, 0);
		transform_.position_.y = startPos_.y;
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
		}
		if (is_table_hit)
		{
			if (SetStandMath(table_hit_point).mathType_ != (int)MATH_HOLE)
			{
				player_state_ = STATE_WARK;
				return;
			}
		}
		if (transform_.position_.y < -1.0f)
		{
			player_state_ = STATE_DEAD;
			return;
		}
		break;
	case STATE_DEAD:
		if (abs(startPos_.x - transform_.position_.x) <= 0.01f &&
			abs(startPos_.z - transform_.position_.z) <= 0.01f)
		{
			stage_state_ = STATE_START;
		}
		transform_.position_.x = transform_.position_.x + (startPos_.x - transform_.position_.x) / 10;
		transform_.position_.z = transform_.position_.z + (startPos_.z - transform_.position_.z) / 10;
		transform_.position_.y = 10;
		return;
	}

	//コンベアによって移動する方向
	XMVECTOR converyor_velocity = XMVectorSet(-1.0f, 0, 0, 0);
	standMath_ = SetStandMath(transform_.position_);
	switch (standMath_.mathType_)
	{
	case MATH_CONVEYOR:
		XMMATRIX yrot = XMMatrixRotationY(XMConvertToRadians(-standMath_.mathPos_.rotate_.z));
		converyor_velocity = XMVector3Transform(converyor_velocity, yrot);	//その回転でベクトルの向きを変える
		converyor_velocity = converyor_velocity / 16;
		if (player_state_ == STATE_WARK)		velocity_ += converyor_velocity;
		break;
	case MATH_GOAL:
		stage_state_ = STATE_GOAL;
		break;
	case MATH_HOLE:
		player_state_ = STATE_FALL;
		break;
	default:break;
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

bool Player::Is_InSide_Table(XMFLOAT3 _pos)
{
	return (_pos.x + MODELSIZE) >= 0 && (_pos.x) < XSIZE - 0.3f &&
		(_pos.z + MODELSIZE) >= 0 && (_pos.z) < ZSIZE - 0.3f;
}

void Player::PlayerOperation()
{
	XMVECTOR cameraBase = XMVectorSet(0, 7, -5, 0);

	static int dec_velocity_ = 20;

	if (player_state_ != STATE_DEAD)
	{
		//前後左右移動
		if (Input::IsKey(DIK_W))
		{
			transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
			sub_velocity_ += XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
			sub_velocity_ = XMVector4Normalize(sub_velocity_); //正規化して全部1になる
			dec_velocity_ = 20;
		}
		if (Input::IsKey(DIK_S))
		{
			transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
			sub_velocity_ += XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
			sub_velocity_ = XMVector4Normalize(sub_velocity_); //正規化して全部1になる
			dec_velocity_ = 30;
		}
		if (Input::IsKey(DIK_A))
		{
			transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
			sub_velocity_ += XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
			sub_velocity_ = XMVector4Normalize(sub_velocity_); //正規化して全部1になる
			dec_velocity_ = 30;
		}
		if (Input::IsKey(DIK_D))
		{
			transform_.rotate_.y += (camRot_.y - transform_.rotate_.y) / 10;
			sub_velocity_ += XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
			sub_velocity_ = XMVector4Normalize(sub_velocity_); //正規化して全部1になる
			dec_velocity_ = 30;
		}
		
		velocity_ = sub_velocity_ / dec_velocity_ / air_dec_velocity_;

		dec_velocity_ += 5;

		if (dec_velocity_ >= 100)
		{

			velocity_ = sub_velocity_ = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			dec_velocity_ = 20;
		}

		//カメラ回転
		XMFLOAT3 v;
		XMStoreFloat3(&v, velocity_);

		XMMATRIX playerYRot = XMMatrixRotationY(XMConvertToRadians(v));

		XMVECTOR rotateYVec = XMVector3Transform(cameraBase, yrot);

		//回転
		if (Input::IsKey(DIK_RIGHT))
		{
			camRot_.y++;
		}
		if (Input::IsKey(DIK_LEFT))
		{
			camRot_.y--;
		}
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

MATHDEDAIL Player::SetStandMath(XMFLOAT3 _pos)
{
	if (!Is_InSide_Table(_pos))
	{
		return MATHDEDAIL{ MATH_HOLE, transform_};
	}
	MATHDEDAIL ret;

	float plusX = MODELSIZE / 2, plusZ = MODELSIZE / 2;
	if (XSIZE - _pos.x < plusX)
	{
		plusX = (float)(XSIZE - _pos.x) - 0.00001f;
	}
	if (ZSIZE - _pos.z < plusZ)
	{
		plusZ = (float)(ZSIZE - _pos.z) - 0.00001f;
	}
	XMFLOAT3 centerPos = XMFLOAT3(_pos.x + plusX, _pos.y, _pos.z + plusZ);

	ret = math_[centerPos.x][centerPos.z];
	//HOLLチェック
	ret = HollCheck(_pos);

	ret = math_[centerPos.x][centerPos.z];

	//WALLチェック
	WallCheck(_pos);

	return ret;
}

MATHDEDAIL Player::HollCheck(XMFLOAT3 _pos)
{
	XMFLOAT3 rightFront = XMFLOAT3(_pos.x + MODELSIZE, _pos.y, _pos.z + MODELSIZE);
	XMFLOAT3 rightBack = XMFLOAT3(_pos.x + MODELSIZE, _pos.y, _pos.z - (1.0f - MODELSIZE));
	XMFLOAT3 leftFront = XMFLOAT3(_pos.x - (1.0f - MODELSIZE), _pos.y, _pos.z + MODELSIZE);
	XMFLOAT3 leftBack = XMFLOAT3(_pos.x - (1.0f - MODELSIZE), _pos.y, _pos.z - (1.0f - MODELSIZE));

	if (Is_InSide_Table(rightFront) &&
		math_[rightFront.x][rightFront.z].mathType_ != MATH_WALL &&
		math_[rightFront.x][rightFront.z].mathType_ != MATH_HOLE)
	{
		return math_[rightFront.x][rightFront.z];
	}
	else if (Is_InSide_Table(rightBack) &&
		math_[rightBack.x][rightBack.z].mathType_ != MATH_WALL &&
		math_[rightBack.x][rightBack.z].mathType_ != MATH_HOLE)
	{
		return math_[rightBack.x][rightBack.z];
	}
	else if (Is_InSide_Table(leftFront) &&
		math_[leftFront.x][leftFront.z].mathType_ != MATH_WALL &&
		math_[leftFront.x][leftFront.z].mathType_ != MATH_HOLE)
	{
		return math_[leftFront.x][leftFront.z];
	}
	else if (Is_InSide_Table(leftBack) &&
		math_[leftBack.x][leftBack.z].mathType_ != MATH_WALL &&
		math_[leftBack.x][leftBack.z].mathType_ != MATH_HOLE)
	{
		return math_[leftBack.x][leftBack.z];
	}
	return math_[_pos.x][_pos.z];
}

void Player::WallCheck(XMFLOAT3 _pos)
{
	bool check = false;
	XMFLOAT3 rightFront = XMFLOAT3(_pos.x + MODELSIZE, _pos.y, _pos.z + MODELSIZE);
	XMFLOAT3 rightBack = XMFLOAT3(_pos.x + MODELSIZE, _pos.y, _pos.z + (1.0f - MODELSIZE));
	XMFLOAT3 leftFront = XMFLOAT3(_pos.x + (1.0f - MODELSIZE), _pos.y, _pos.z + MODELSIZE);
	XMFLOAT3 leftBack = XMFLOAT3(_pos.x + (1.0f - MODELSIZE), _pos.y, _pos.z + (1.0f - MODELSIZE));

	if (Is_InSide_Table(rightFront) &&
		math_[rightFront.x][rightFront.z].mathType_ == MATH_WALL)
	{
		check = true;
		//前
		if (abs((float)((int)rightFront.x - rightFront.x)) > abs((float)((int)rightFront.z - rightFront.z)) ||
			math_[leftFront.x][leftFront.z].mathType_ == MATH_WALL)
		{
			transform_.position_.z = (float)(int)rightFront.z - (rightFront.z - _pos.z);
		}
		//右
		if (abs((float)((int)rightFront.x - rightFront.x)) <= abs((float)((int)rightFront.z - rightFront.z)) ||
			math_[rightBack.x][rightBack.z].mathType_ == MATH_WALL)
		{
			transform_.position_.x = (float)((int)rightFront.x) - (rightFront.x - _pos.x);
		}
	}
	if (Is_InSide_Table(rightBack) &&
		math_[rightBack.x][rightBack.z].mathType_ == MATH_WALL)
	{
		check = true;
		//後ろ
		if (abs((float)((int)rightBack.x - rightBack.x)) > abs((float)((int)(rightBack.z + 1) - rightBack.z)) ||
			math_[leftBack.x][leftBack.z].mathType_ == MATH_WALL)
		{
			transform_.position_.z = (float)(int)(rightBack.z + 1) - (rightBack.z - _pos.z);
		}
		//右
		if (abs((float)((int)rightBack.x - rightBack.x)) <= abs((float)((int)(rightBack.z + 1) - rightBack.z)) ||
			math_[rightFront.x][rightFront.z].mathType_ == MATH_WALL)
		{
			transform_.position_.x = (float)(int)rightBack.x - (rightBack.x - _pos.x);
		}
	}
	if (Is_InSide_Table(leftFront) &&
		math_[leftFront.x][leftFront.z].mathType_ == MATH_WALL)
	{
		check = true;
		//前
		if (abs((float)((int)(leftFront.x + 1) - leftFront.x)) > abs((float)((int)leftFront.z - leftFront.z)) ||
			math_[rightFront.x][rightFront.z].mathType_ == MATH_WALL)
		{
			transform_.position_.z = (float)(int)leftFront.z - (leftFront.z - _pos.z);
		}
		//左
		if (abs((float)((int)(leftFront.x + 1) - leftFront.x)) <= abs((float)((int)leftFront.z - leftFront.z)) ||
			math_[leftBack.x][leftBack.z].mathType_ == MATH_WALL)
		{
			transform_.position_.x = (float)(int)(leftFront.x + 1) - (leftFront.x - _pos.x);
		}
	}
	if (Is_InSide_Table(leftBack) &&
		math_[leftBack.x][leftBack.z].mathType_ == MATH_WALL)
	{
		check = true;
		//後ろ
		if (abs((float)((int)(leftBack.x + 1) - leftBack.x)) > abs((float)((int)(leftBack.z + 1) - leftBack.z)) ||
			math_[rightBack.x][rightBack.z].mathType_ == MATH_WALL)
		{
			transform_.position_.z = (float)(int)(leftBack.z + 1) - (leftBack.z - _pos.z);
		}
		//左
		if (abs((float)((int)(leftBack.x + 1) - leftBack.x)) <= abs((float)((int)(leftBack.z + 1) - leftBack.z)) ||
			math_[leftFront.x][leftFront.z].mathType_ == MATH_WALL)
		{
			transform_.position_.x = (float)(int)(leftBack.x + 1) - (leftBack.x - _pos.x);
		}
	}
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Togetoge")
	{
		player_state_ = STATE_DEAD;
	}
}
