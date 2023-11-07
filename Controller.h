#pragma once
#include "Engine/GameObject.h"
#include "StageOrigin.h"

enum PLAYER_STATE
{
	STATE_WARK = 0,
	STATE_JAMP,
	STATE_FALL,
};

enum STAGE_STATE
{
	STATE_PLAY = 0,
	STATE_GOAL,
};

class Controller
	:public GameObject, StageOrigin
{
	XMVECTOR velocity_;

	int hModel_;

	XMFLOAT3 startPos_, goalPos_;
	XMFLOAT3 camRot_;

	PLAYER_STATE player_state_;
	STAGE_STATE stage_state_;
public:
	Controller(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void PlayUpdate();
};

