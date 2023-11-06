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

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetStartPos(XMFLOAT3 _startPos) { startPos_ = _startPos; }
	void SetGoalPos(XMFLOAT3 _goalPos) { goalPos_ = _goalPos; }

	XMFLOAT3 GetStartPos() { return startPos_; }
	XMFLOAT3 GetGoalPos() { return goalPos_; }
};

