#pragma once
#include "Engine/GameObject.h"

class SceneTransition
	:public GameObject
{
	bool isFinished_;

	int math_xsize_;
	int math_ysize_;
public:
	SceneTransition(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetIsFinished(bool _isFinished) { isFinished_ = _isFinished; };

