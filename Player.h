#pragma once
#include "Engine/GameObject.h"
#include "StageOrigin.h"

enum PLAYER_STATE
{
	STATE_WARK = 0,
	STATE_JAMP,
	STATE_FALL,
	STATE_DEAD,
};

enum STAGE_STATE
{
	STATE_PLAY = 0,
	STATE_GOAL,
};

class Player
	:public GameObject, StageOrigin
{
	int hModel_;

	XMVECTOR sub_velocity_, velocity_, jamp_start_velocity_;

	XMFLOAT3 startPos_, goalPos_;
	XMFLOAT3 camRot_;

	PLAYER_STATE player_state_;
	STAGE_STATE stage_state_;

	//重力
	XMFLOAT3 gravity_;

	//空中でのスピード減衰
	int air_dec_velocity_;
public:
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void PlayUpdate();

	bool Is_InSide_Table();

	void PlayerOperation();

	bool is_Goal() 
	{ 
		if (stage_state_ == STATE_GOAL)
		{
			return true;
		}
		return false;
	};
};

