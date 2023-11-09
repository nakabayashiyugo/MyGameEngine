#pragma once
#include "Engine/GameObject.h"
#include "StageOrigin.h"

class Stage;
class Controller;

class TestScene
	:public GameObject, StageOrigin
{
	Stage* pStage_;
	Controller* pCont_;
public:
	TestScene(GameObject* parent);

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

