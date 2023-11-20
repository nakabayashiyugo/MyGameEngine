#pragma once
#include "Engine/GameObject.h"
#include "StageOrigin.h"

class Stage;
class Player;

class PlayScene
	:public GameObject, StageOrigin
{
	Stage* pStage_;
	Player* pPlayer_;
public:
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void Read();

	MATHDEDAIL GetTableMath(int x, int z) { return math_.at(x).at(z); }
};

