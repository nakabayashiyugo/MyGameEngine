#pragma once
#include "Engine/GameObject.h"
#include "StageOrigin.h"

class PlayScene;

enum PLAYER_STATE
{
	STATE_WARK = 0,
	STATE_JAMP,
	STATE_FALL,
	STATE_DEAD,
};

enum STAGE_STATE
{
	STATE_START = 0,
	STATE_PLAY,
	STATE_GOAL,
	STATE_FAILURE,
};

class Player
	:public GameObject, StageOrigin
{
	int hModel_;

	bool isGoal_;

	PlayScene* pPlayScene_;

	XMVECTOR sub_velocity_, velocity_, jamp_start_velocity_;

	XMFLOAT3 startPos_, goalPos_;
	XMFLOAT3 camRot_;

	PLAYER_STATE player_state_;
	STAGE_STATE stage_state_;

	//重力
	XMFLOAT3 gravity_;

	//空中でのスピード減衰
	int air_dec_velocity_;

	//障害物の置ける数
	int hurdle_Limit_;
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

	bool Is_Goal() { return isGoal_; }

	XMFLOAT3 GetPosition() { return transform_.position_; }

	void SetTableMath(std::vector<std::vector<MATHDEDAIL>> _math);
};

