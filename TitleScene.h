#pragma once
#include "Engine/GameObject.h"

class TitleScene
	:public GameObject
{
	int hStartButton_, hStaful_;

	Transform tStartButton_, tStaful_;
	XMFLOAT3 mousePos_;
public:
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};