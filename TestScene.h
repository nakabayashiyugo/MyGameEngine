#pragma once
#include "Engine/GameObject.h"
#include "StageOrigin.h"

class TestScene
	:public GameObject, StageOrigin
{
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

	void Read();

	MATHDEDAIL GetTableMath(int x, int z) { return math_.at(x).at(z); }
};

