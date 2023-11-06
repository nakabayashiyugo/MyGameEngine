#pragma once
#include "Engine/GameObject.h"

class TestScene
	:public GameObject
{
	bool isCreate_newTable_;

	int table_xsize_;
	int table_zsize_;

	XMFLOAT3 startPos_;
	XMFLOAT3 goalPos_;
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

	void SetStartPos(XMFLOAT3 _startPos) { startPos_ = _startPos; }
	void SetGoalPos(XMFLOAT3 _goalPos) { goalPos_ = _goalPos; }

	XMFLOAT3 GetStartPos() { return startPos_; }
	XMFLOAT3 GetGoalPos() { return goalPos_; }
};

