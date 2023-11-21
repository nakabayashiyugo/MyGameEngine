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

	//�d��
	XMFLOAT3 gravity_;

	//�󒆂ł̃X�s�[�h����
	int air_dec_velocity_;
public:
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
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

