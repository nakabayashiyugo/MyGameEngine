#pragma once
#include "Engine/GameObject.h"

class Controller
	:public GameObject
{
	XMVECTOR velocity_;

	int hModel_;
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
};

